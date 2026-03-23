import struct
import csv

def parse_to_csv(bin_path, csv_path):
    marker = b'@BIN@'
    records = []
    
    try:
        with open(bin_path, 'rb') as f:
            content = f.read()
    except FileNotFoundError:
        print(f"找不到文件: {bin_path}")
        return

    pos = content.find(marker)
    if pos == -1:
        print("错误：未在文件中找到 @BIN@ 标志")
        return

    record_id = 1
    last_end_ptr = 0

    while pos != -1:
        # 1. 提取描述符 (从上次结束到本次 @BIN@ 结束)
        descriptor_bytes = content[last_end_ptr : pos + len(marker)]
        descriptor_str = "".join(chr(b) if 32 <= b <= 126 else ' ' for b in descriptor_bytes).strip()
        
        float_start_ptr = pos + len(marker)
        current_ptr = float_start_ptr
        all_floats = []
        
        # 2. 连续读取大端序 float，直到超出范围 [-100, 100]
        while current_ptr + 4 <= len(content):
            chunk = content[current_ptr : current_ptr + 4]
            val = struct.unpack('<f', chunk)[0] # 端序
            
            if -100.0 <= val <= 100.0:
                all_floats.append(round(val, 6)) # 保留6位小数方便阅读
                current_ptr += 4
            else:
                break
        
        # 3. 准备展示的 float 数据
        count = len(all_floats)
        if count <= 10:
            # 如果总数不足10个，直接显示全部
            head_floats = all_floats
            tail_floats = []
        else:
            head_floats = all_floats[:5]
            tail_floats = all_floats[-5:]

        # 4. 整理记录
        records.append([
            record_id,
            descriptor_str,
            count,
            float_start_ptr,
            ", ".join(map(str, head_floats)),
            ", ".join(map(str, tail_floats)) if tail_floats else "N/A (Total < 10)"
        ])
        
        # 5. 更新指针寻找下一个 @BIN@
        last_end_ptr = current_ptr
        pos = content.find(marker, last_end_ptr)
        record_id += 1

    # 6. 写入 CSV
    headers = ["ID", "Descriptor", "ParamCount", "StartOffset", "First_5_Floats", "Last_5_Floats"]
    try:
        with open(csv_path, 'w', newline='', encoding='utf-8-sig') as f:
            writer = csv.writer(f)
            writer.writerow(headers)
            writer.writerows(records)
        print(f"解析完成！共发现 {len(records)} 组数据。")
        print(f"CSV 文件已生成: {csv_path}")
    except PermissionError:
        print(f"错误：请关闭正在运行的 {csv_path} 后重试。")

# --- 运行 ---
parse_to_csv('b5c192nbt-s13156480-d2171154.bin', 'result_summary.csv')
