#include "cnpy.h"
#include <complex>
#include <cstdlib>
#include <algorithm>
#include <cstring>
#include <iomanip>
#include <stdint.h>
#include <stdexcept>
#include <regex>

char cnpy::BigEndianTest() {
    int x = 1;
    return (((char *)&x)[0]) ? '<' : '>';
}

char cnpy::map_type(const std::type_info& t) {
    if(t == typeid(float) ) return 'f';
    if(t == typeid(double) ) return 'f';
    if(t == typeid(long double) ) return 'f';
    if(t == typeid(int) ) return 'i';
    if(t == typeid(char) ) return 'i';
    if(t == typeid(short) ) return 'i';
    if(t == typeid(long) ) return 'i';
    if(t == typeid(long long) ) return 'i';
    if(t == typeid(unsigned char) ) return 'u';
    if(t == typeid(unsigned short) ) return 'u';
    if(t == typeid(unsigned long) ) return 'u';
    if(t == typeid(unsigned long long) ) return 'u';
    if(t == typeid(unsigned int) ) return 'u';
    if(t == typeid(bool) ) return 'b';
    if(t == typeid(std::complex<float>) ) return 'c';
    if(t == typeid(std::complex<double>) ) return 'c';
    if(t == typeid(std::complex<long double>) ) return 'c';
    else return '?';
}

template<> std::vector<char>& cnpy::operator+=(std::vector<char>& lhs, const std::string rhs) {
    lhs.insert(lhs.end(),rhs.begin(),rhs.end());
    return lhs;
}

template<> std::vector<char>& cnpy::operator+=(std::vector<char>& lhs, const char* rhs) {
    size_t len = strlen(rhs);
    lhs.reserve(lhs.size() + len);
    for(size_t byte = 0; byte < len; byte++) {
        lhs.push_back(rhs[byte]);
    }
    return lhs;
}

// 内部工具函数：解析字符串形式的 NPY Header
void cnpy::parse_npy_header(unsigned char* buffer,size_t& word_size, std::vector<size_t>& shape, bool& fortran_order) {
    uint16_t header_len = *reinterpret_cast<uint16_t*>(buffer+8);
    std::string header(reinterpret_cast<char*>(buffer+10),header_len);

    size_t loc1, loc2;

    // fortran order - 灵活查找
    loc1 = header.find("fortran_order");
    if(loc1 != std::string::npos) {
        fortran_order = (header.find("True", loc1) != std::string::npos && header.find("True", loc1) < header.find(",", loc1));
    } else {
        fortran_order = false;
    }

    // shape - 灵活正则匹配数字，兼容你的格式
    loc1 = header.find("(");
    loc2 = header.find(")");
    if(loc1 != std::string::npos && loc2 != std::string::npos) {
        std::regex num_regex("[0-9][0-9]*");
        std::smatch sm;
        shape.clear();
        std::string str_shape = header.substr(loc1+1,loc2-loc1-1);
        while(std::regex_search(str_shape, sm, num_regex)) {
            shape.push_back(std::stoul(sm[0].str()));
            str_shape = sm.suffix().str();
        }
    }

    // descr / word size - 不再使用硬编码 +9 偏移
    loc1 = header.find("descr");
    word_size = 4; // 默认 float32
    if(loc1 != std::string::npos) {
        size_t quote_start = header.find_first_of("'\"", loc1 + 5);
        size_t quote_end = header.find_first_of("'\"", quote_start + 1);
        if(quote_start != std::string::npos && quote_end != std::string::npos) {
            std::string descr = header.substr(quote_start + 1, quote_end - quote_start - 1);
            std::regex word_regex("[0-9]+");
            std::smatch sm;
            if(std::regex_search(descr, sm, word_regex)) {
                word_size = std::stoul(sm[0].str());
            }
        }
    }
}

// 内部工具函数：解析文件流形式的 NPY Header
void cnpy::parse_npy_header(FILE* fp, size_t& word_size, std::vector<size_t>& shape, bool& fortran_order) {  
    char magic[10];
    if(fread(magic,1,10,fp) != 10) throw std::runtime_error("parse_npy_header: failed fread");
    uint16_t header_len = *reinterpret_cast<uint16_t*>(&magic[8]);
    std::vector<char> buffer(header_len);
    if(fread(buffer.data(),1,header_len,fp) != header_len) throw std::runtime_error("parse_npy_header: content read failed");
    
    std::string header(buffer.begin(), buffer.end());
    size_t loc1, loc2;

    loc1 = header.find("fortran_order");
    fortran_order = (loc1 != std::string::npos && header.find("True", loc1) != std::string::npos);

    loc1 = header.find("(");
    loc2 = header.find(")");
    if(loc1 != std::string::npos && loc2 != std::string::npos) {
        std::regex num_regex("[0-9]+");
        std::smatch sm;
        shape.clear();
        std::string str_shape = header.substr(loc1+1,loc2-loc1-1);
        while(std::regex_search(str_shape, sm, num_regex)) {
            shape.push_back(std::stoul(sm[0].str()));
            str_shape = sm.suffix().str();
        }
    }

    loc1 = header.find("descr");
    word_size = 4;
    if(loc1 != std::string::npos) {
        size_t quote_start = header.find_first_of("'\"", loc1 + 5);
        size_t quote_end = header.find_first_of("'\"", quote_start + 1);
        if(quote_start != std::string::npos && quote_end != std::string::npos) {
            std::regex word_regex("[0-9]+");
            std::smatch sm;
            std::string descr = header.substr(quote_start + 1, quote_end - quote_start - 1);
            if(std::regex_search(descr, sm, word_regex)) word_size = std::stoul(sm[0].str());
        }
    }
}

// 加载单文件 .npy
cnpy::NpyArray load_the_npy_file(FILE* fp) {
    std::vector<size_t> shape;
    size_t word_size;
    bool fortran_order;
    cnpy::parse_npy_header(fp,word_size,shape,fortran_order);
    cnpy::NpyArray arr(shape, word_size, fortran_order);
    size_t nread = fread(arr.data<char>(),1,arr.num_bytes(),fp);
    if(nread != arr.num_bytes()) throw std::runtime_error("load_the_npy_file: failed fread");
    return arr;
}

// 加载 npz 中的压缩数据
cnpy::NpyArray load_the_npz_array(FILE* fp, uint32_t compr_bytes, uint32_t uncompr_bytes) {
    std::vector<unsigned char> buffer_compr(compr_bytes);
    std::vector<unsigned char> buffer_uncompr(uncompr_bytes);
    if(fread(&buffer_compr[0],1,compr_bytes,fp) != compr_bytes) throw std::runtime_error("load_the_npz_array: failed fread");

    z_stream d_stream;
    d_stream.zalloc = Z_NULL; d_stream.zfree = Z_NULL; d_stream.opaque = Z_NULL;
    d_stream.avail_in = 0; d_stream.next_in = Z_NULL;
    inflateInit2(&d_stream, -MAX_WBITS);

    d_stream.avail_in = compr_bytes;
    d_stream.next_in = &buffer_compr[0];
    d_stream.avail_out = uncompr_bytes;
    d_stream.next_out = &buffer_uncompr[0];

    inflate(&d_stream, Z_FINISH);
    inflateEnd(&d_stream);

    std::vector<size_t> shape;
    size_t word_size;
    bool fortran_order;
    cnpy::parse_npy_header(&buffer_uncompr[0],word_size,shape,fortran_order);
    cnpy::NpyArray array(shape, word_size, fortran_order);
    size_t offset = uncompr_bytes - array.num_bytes();
    memcpy(array.data<unsigned char>(),&buffer_uncompr[0]+offset,array.num_bytes());
    return array;
}

// 加载 .npz 整体
cnpy::npz_t cnpy::npz_load(std::string fname) {
    FILE* fp = fopen(fname.c_str(),"rb");
    if(!fp) throw std::runtime_error("npz_load: Error! Unable to open file "+fname+"!");
    cnpy::npz_t arrays;  
    while(1) {
        char local_header[30];
        if(fread(local_header,1,30,fp) != 30) break;
        if(local_header[2] != 0x03 || local_header[3] != 0x04) break;

        uint16_t name_len = *(uint16_t*) &local_header[26];
        std::string varname(name_len,' ');
        fread(&varname[0],sizeof(char),name_len,fp);
        
        // 关键：如果内部文件名不带 .npy，不执行 erase，避免越界崩溃
        if(varname.size() >= 4 && varname.substr(varname.size()-4) == ".npy") {
            varname.erase(varname.end()-4,varname.end());
        }

        uint16_t extra_field_len = *(uint16_t*) &local_header[28];
        fseek(fp,extra_field_len,SEEK_CUR);

        uint16_t compr_method = *reinterpret_cast<uint16_t*>(&local_header[8]);
        uint32_t compr_bytes = *reinterpret_cast<uint32_t*>(&local_header[18]);
        uint32_t uncompr_bytes = *reinterpret_cast<uint32_t*>(&local_header[22]);

        if(compr_method == 0) { arrays[varname] = load_the_npy_file(fp); }
        else { arrays[varname] = load_the_npz_array(fp,compr_bytes,uncompr_bytes); }
    }
    fclose(fp);
    return arrays;  
}

// ... 剩下的逻辑类似，为了精简已确保上述为 npz_load 核心全集 ...