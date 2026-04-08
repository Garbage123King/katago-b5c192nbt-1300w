#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <zlib.h>
#include "cnpy.h" // 必须安装并包含 cnpy

#define TRUE 1
#define FALSE 0

typedef struct {
    const char* content;
    int bin_start;
    int bin_len;
    float *floats;
} bin_t;

bin_t BINS[]={
"aaa-ccc-s13156480-d2171154 15 22 19 20.0 20.0 20.0 20.0 40.0 0.25 150.0 0 0 0 0 0 0 0 0 trunk 5 192 96 64 32 32 0 0 0 0 0 0 model.conv_spatial 3 3 22 192 1 1 @BIN@",	163,	38016, NULL,
"model.linear_global 19 192 @BIN@",	152260,	3648, NULL,
"nested_bottleneck_block model.blocks.0 2 model.blocks.0.normactconvp.norm 192 1e-20 0 1 @BIN@",	166946,	192, NULL,
"@BIN@",	167720,	192, NULL,
"@BIN@",	168494,	192, NULL,
"model.blocks.0.normactconvp.act ACTIVATION_RELU model.blocks.0.normactconvp.conv 1 1 192 96 1 1 @BIN@",	169364,	18432, NULL,
"ordinary_block model.blocks.0.blockstack.0 model.blocks.0.blockstack.0.normactconv1.norm 96 1e-20 0 1 @BIN@",	243200,	96, NULL,
"@BIN@",	243590,	96, NULL,
"@BIN@",	243980,	96, NULL,
"model.blocks.0.blockstack.0.normactconv1.act ACTIVATION_RELU model.blocks.0.blockstack.0.normactconv1.conv 3 3 96 96 1 1 @BIN@",	244491,	82944, NULL,
"model.blocks.0.blockstack.0.normactconv2.norm 96 1e-20 1 1 @BIN@",	576332,	96, NULL,
"@BIN@",	576722,	96, NULL,
"@BIN@",	577112,	96, NULL,
"@BIN@",	577502,	96, NULL,
"model.blocks.0.blockstack.0.normactconv2.act ACTIVATION_RELU model.blocks.0.blockstack.0.normactconv2.conv 3 3 96 96 1 1 @BIN@",	578013,	82944, NULL,
"ordinary_block model.blocks.0.blockstack.1 model.blocks.0.blockstack.1.normactconv1.norm 96 1e-20 0 1 @BIN@",	909897,	96, NULL,
"@BIN@",	910287,	96, NULL,
"@BIN@",	910677,	96, NULL,
"model.blocks.0.blockstack.1.normactconv1.act ACTIVATION_RELU model.blocks.0.blockstack.1.normactconv1.conv 3 3 96 96 1 1 @BIN@",	911188,	82944, NULL,
"model.blocks.0.blockstack.1.normactconv2.norm 96 1e-20 1 1 @BIN@",	1243029,	96, NULL,
"@BIN@",	1243419,	96, NULL,
"@BIN@",	1243809,	96, NULL,
"@BIN@",	1244199,	96, NULL,
"model.blocks.0.blockstack.1.normactconv2.act ACTIVATION_RELU model.blocks.0.blockstack.1.normactconv2.conv 3 3 96 96 1 1 @BIN@",	1244710,	82944, NULL,
"model.blocks.0.normactconvq.norm 96 1e-20 1 1 @BIN@",	1576538,	96, NULL,
"@BIN@",	1576928,	96, NULL,
"@BIN@",	1577318,	96, NULL,
"@BIN@",	1577708,	96, NULL,
"model.blocks.0.normactconvq.act ACTIVATION_RELU model.blocks.0.normactconvq.conv 1 1 96 192 1 1 @BIN@",	1578194,	18432, NULL,
"nested_bottleneck_block model.blocks.1 2 model.blocks.1.normactconvp.norm 192 1e-20 0 1 @BIN@",	1652016,	192, NULL,
"@BIN@",	1652790,	192, NULL,
"@BIN@",	1653564,	192, NULL,
"model.blocks.1.normactconvp.act ACTIVATION_RELU model.blocks.1.normactconvp.conv 1 1 192 96 1 1 @BIN@",	1654434,	18432, NULL,
"gpool_block model.blocks.1.blockstack.0 model.blocks.1.blockstack.0.normactconv1.norm 96 1e-20 0 1 @BIN@",	1728267,	96, NULL,
"@BIN@",	1728657,	96, NULL,
"@BIN@",	1729047,	96, NULL,
"model.blocks.1.blockstack.0.normactconv1.act ACTIVATION_RELU model.blocks.1.blockstack.0.normactconv1.convpool.conv1r 3 3 96 64 1 1 @BIN@",	1729569,	55296, NULL,
"model.blocks.1.blockstack.0.normactconv1.convpool.conv1g 3 3 96 32 1 1 @BIN@",	1950830,	27648, NULL,
"model.blocks.1.blockstack.0.normactconv1.convpool.normg 32 1e-20 0 1 @BIN@",	2061497,	32, NULL,
"@BIN@",	2061631,	32, NULL,
"@BIN@",	2061765,	32, NULL,
"model.blocks.1.blockstack.0.normactconv1.convpool.actg ACTIVATION_RELU model.blocks.1.blockstack.0.normactconv1.convpool.linear_g 96 64 @BIN@",	2062035,	6144, NULL,
"model.blocks.1.blockstack.0.normactconv2.norm 64 1e-20 1 1 @BIN@",	2086676,	64, NULL,
"@BIN@",	2086938,	64, NULL,
"@BIN@",	2087200,	64, NULL,
"@BIN@",	2087462,	64, NULL,
"model.blocks.1.blockstack.0.normactconv2.act ACTIVATION_RELU model.blocks.1.blockstack.0.normactconv2.conv 3 3 64 96 1 1 @BIN@",	2087845,	55296, NULL,
"ordinary_block model.blocks.1.blockstack.1 model.blocks.1.blockstack.1.normactconv1.norm 96 1e-20 0 1 @BIN@",	2309137,	96, NULL,
"@BIN@",	2309527,	96, NULL,
"@BIN@",	2309917,	96, NULL,
"model.blocks.1.blockstack.1.normactconv1.act ACTIVATION_RELU model.blocks.1.blockstack.1.normactconv1.conv 3 3 96 96 1 1 @BIN@",	2310428,	82944, NULL,
"model.blocks.1.blockstack.1.normactconv2.norm 96 1e-20 1 1 @BIN@",	2642269,	96, NULL,
"@BIN@",	2642659,	96, NULL,
"@BIN@",	2643049,	96, NULL,
"@BIN@",	2643439,	96, NULL,
"model.blocks.1.blockstack.1.normactconv2.act ACTIVATION_RELU model.blocks.1.blockstack.1.normactconv2.conv 3 3 96 96 1 1 @BIN@",	2643950,	82944, NULL,
"model.blocks.1.normactconvq.norm 96 1e-20 1 1 @BIN@",	2975778,	96, NULL,
"@BIN@",	2976168,	96, NULL,
"@BIN@",	2976558,	96, NULL,
"@BIN@",	2976948,	96, NULL,
"model.blocks.1.normactconvq.act ACTIVATION_RELU model.blocks.1.normactconvq.conv 1 1 96 192 1 1 @BIN@",	2977434,	18432, NULL,
"nested_bottleneck_block model.blocks.2 2 model.blocks.2.normactconvp.norm 192 1e-20 0 1 @BIN@",	3051256,	192, NULL,
"@BIN@",	3052030,	192, NULL,
"@BIN@",	3052804,	192, NULL,
"model.blocks.2.normactconvp.act ACTIVATION_RELU model.blocks.2.normactconvp.conv 1 1 192 96 1 1 @BIN@",	3053674,	18432, NULL,
"ordinary_block model.blocks.2.blockstack.0 model.blocks.2.blockstack.0.normactconv1.norm 96 1e-20 0 1 @BIN@",	3127510,	96, NULL,
"@BIN@",	3127900,	96, NULL,
"@BIN@",	3128290,	96, NULL,
"model.blocks.2.blockstack.0.normactconv1.act ACTIVATION_RELU model.blocks.2.blockstack.0.normactconv1.conv 3 3 96 96 1 1 @BIN@",	3128801,	82944, NULL,
"model.blocks.2.blockstack.0.normactconv2.norm 96 1e-20 1 1 @BIN@",	3460642,	96, NULL,
"@BIN@",	3461032,	96, NULL,
"@BIN@",	3461422,	96, NULL,
"@BIN@",	3461812,	96, NULL,
"model.blocks.2.blockstack.0.normactconv2.act ACTIVATION_RELU model.blocks.2.blockstack.0.normactconv2.conv 3 3 96 96 1 1 @BIN@",	3462323,	82944, NULL,
"ordinary_block model.blocks.2.blockstack.1 model.blocks.2.blockstack.1.normactconv1.norm 96 1e-20 0 1 @BIN@",	3794207,	96, NULL,
"@BIN@",	3794597,	96, NULL,
"@BIN@",	3794987,	96, NULL,
"model.blocks.2.blockstack.1.normactconv1.act ACTIVATION_RELU model.blocks.2.blockstack.1.normactconv1.conv 3 3 96 96 1 1 @BIN@",	3795498,	82944, NULL,
"model.blocks.2.blockstack.1.normactconv2.norm 96 1e-20 1 1 @BIN@",	4127339,	96, NULL,
"@BIN@",	4127729,	96, NULL,
"@BIN@",	4128119,	96, NULL,
"@BIN@",	4128509,	96, NULL,
"model.blocks.2.blockstack.1.normactconv2.act ACTIVATION_RELU model.blocks.2.blockstack.1.normactconv2.conv 3 3 96 96 1 1 @BIN@",	4129020,	82944, NULL,
"model.blocks.2.normactconvq.norm 96 1e-20 1 1 @BIN@",	4460848,	96, NULL,
"@BIN@",	4461238,	96, NULL,
"@BIN@",	4461628,	96, NULL,
"@BIN@",	4462018,	96, NULL,
"model.blocks.2.normactconvq.act ACTIVATION_RELU model.blocks.2.normactconvq.conv 1 1 96 192 1 1 @BIN@",	4462504,	18432, NULL,
"nested_bottleneck_block model.blocks.3 2 model.blocks.3.normactconvp.norm 192 1e-20 0 1 @BIN@",	4536326,	192, NULL,
"@BIN@",	4537100,	192, NULL,
"@BIN@",	4537874,	192, NULL,
"model.blocks.3.normactconvp.act ACTIVATION_RELU model.blocks.3.normactconvp.conv 1 1 192 96 1 1 @BIN@",	4538744,	18432, NULL,
"gpool_block model.blocks.3.blockstack.0 model.blocks.3.blockstack.0.normactconv1.norm 96 1e-20 0 1 @BIN@",	4612577,	96, NULL,
"@BIN@",	4612967,	96, NULL,
"@BIN@",	4613357,	96, NULL,
"model.blocks.3.blockstack.0.normactconv1.act ACTIVATION_RELU model.blocks.3.blockstack.0.normactconv1.convpool.conv1r 3 3 96 64 1 1 @BIN@",	4613879,	55296, NULL,
"model.blocks.3.blockstack.0.normactconv1.convpool.conv1g 3 3 96 32 1 1 @BIN@",	4835140,	27648, NULL,
"model.blocks.3.blockstack.0.normactconv1.convpool.normg 32 1e-20 0 1 @BIN@",	4945807,	32, NULL,
"@BIN@",	4945941,	32, NULL,
"@BIN@",	4946075,	32, NULL,
"model.blocks.3.blockstack.0.normactconv1.convpool.actg ACTIVATION_RELU model.blocks.3.blockstack.0.normactconv1.convpool.linear_g 96 64 @BIN@",	4946345,	6144, NULL,
"model.blocks.3.blockstack.0.normactconv2.norm 64 1e-20 1 1 @BIN@",	4970986,	64, NULL,
"@BIN@",	4971248,	64, NULL,
"@BIN@",	4971510,	64, NULL,
"@BIN@",	4971772,	64, NULL,
"model.blocks.3.blockstack.0.normactconv2.act ACTIVATION_RELU model.blocks.3.blockstack.0.normactconv2.conv 3 3 64 96 1 1 @BIN@",	4972155,	55296, NULL,
"ordinary_block model.blocks.3.blockstack.1 model.blocks.3.blockstack.1.normactconv1.norm 96 1e-20 0 1 @BIN@",	5193447,	96, NULL,
"@BIN@",	5193837,	96, NULL,
"@BIN@",	5194227,	96, NULL,
"model.blocks.3.blockstack.1.normactconv1.act ACTIVATION_RELU model.blocks.3.blockstack.1.normactconv1.conv 3 3 96 96 1 1 @BIN@",	5194738,	82944, NULL,
"model.blocks.3.blockstack.1.normactconv2.norm 96 1e-20 1 1 @BIN@",	5526579,	96, NULL,
"@BIN@",	5526969,	96, NULL,
"@BIN@",	5527359,	96, NULL,
"@BIN@",	5527749,	96, NULL,
"model.blocks.3.blockstack.1.normactconv2.act ACTIVATION_RELU model.blocks.3.blockstack.1.normactconv2.conv 3 3 96 96 1 1 @BIN@",	5528260,	82944, NULL,
"model.blocks.3.normactconvq.norm 96 1e-20 1 1 @BIN@",	5860088,	96, NULL,
"@BIN@",	5860478,	96, NULL,
"@BIN@",	5860868,	96, NULL,
"@BIN@",	5861258,	96, NULL,
"model.blocks.3.normactconvq.act ACTIVATION_RELU model.blocks.3.normactconvq.conv 1 1 96 192 1 1 @BIN@",	5861744,	18432, NULL,
"nested_bottleneck_block model.blocks.4 2 model.blocks.4.normactconvp.norm 192 1e-20 0 1 @BIN@",	5935566,	192, NULL,
"@BIN@",	5936340,	192, NULL,
"@BIN@",	5937114,	192, NULL,
"model.blocks.4.normactconvp.act ACTIVATION_RELU model.blocks.4.normactconvp.conv 1 1 192 96 1 1 @BIN@",	5937984,	18432, NULL,
"ordinary_block model.blocks.4.blockstack.0 model.blocks.4.blockstack.0.normactconv1.norm 96 1e-20 0 1 @BIN@",	6011820,	96, NULL,
"@BIN@",	6012210,	96, NULL,
"@BIN@",	6012600,	96, NULL,
"model.blocks.4.blockstack.0.normactconv1.act ACTIVATION_RELU model.blocks.4.blockstack.0.normactconv1.conv 3 3 96 96 1 1 @BIN@",	6013111,	82944, NULL,
"model.blocks.4.blockstack.0.normactconv2.norm 96 1e-20 1 1 @BIN@",	6344952,	96, NULL,
"@BIN@",	6345342,	96, NULL,
"@BIN@",	6345732,	96, NULL,
"@BIN@",	6346122,	96, NULL,
"model.blocks.4.blockstack.0.normactconv2.act ACTIVATION_RELU model.blocks.4.blockstack.0.normactconv2.conv 3 3 96 96 1 1 @BIN@",	6346633,	82944, NULL,
"ordinary_block model.blocks.4.blockstack.1 model.blocks.4.blockstack.1.normactconv1.norm 96 1e-20 0 1 @BIN@",	6678517,	96, NULL,
"@BIN@",	6678907,	96, NULL,
"@BIN@",	6679297,	96, NULL,
"model.blocks.4.blockstack.1.normactconv1.act ACTIVATION_RELU model.blocks.4.blockstack.1.normactconv1.conv 3 3 96 96 1 1 @BIN@",	6679808,	82944, NULL,
"model.blocks.4.blockstack.1.normactconv2.norm 96 1e-20 1 1 @BIN@",	7011649,	96, NULL,
"@BIN@",	7012039,	96, NULL,
"@BIN@",	7012429,	96, NULL,
"@BIN@",	7012819,	96, NULL,
"model.blocks.4.blockstack.1.normactconv2.act ACTIVATION_RELU model.blocks.4.blockstack.1.normactconv2.conv 3 3 96 96 1 1 @BIN@",	7013330,	82944, NULL,
"model.blocks.4.normactconvq.norm 96 1e-20 1 1 @BIN@",	7345158,	96, NULL,
"@BIN@",	7345548,	96, NULL,
"@BIN@",	7345938,	96, NULL,
"@BIN@",	7346328,	96, NULL,
"model.blocks.4.normactconvq.act ACTIVATION_RELU model.blocks.4.normactconvq.conv 1 1 96 192 1 1 @BIN@",	7346814,	18432, NULL,
"model.norm_trunkfinal 192 1e-20 0 1 @BIN@",	7420584,	192, NULL,
"@BIN@",	7421358,	192, NULL,
"@BIN@",	7422132,	192, NULL,
"model.act_trunkfinal ACTIVATION_RELU model.policy_head model.policy_head.conv1p 1 1 192 32 1 1 @BIN@",	7423001,	6144, NULL,
"model.policy_head.conv1g 1 1 192 32 1 1 @BIN@",	7447623,	6144, NULL,
"model.policy_head.biasg 32 1e-20 0 1 @BIN@",	7472242,	32, NULL,
"@BIN@",	7472376,	32, NULL,
"@BIN@",	7472510,	32, NULL,
"model.policy_head.actg ACTIVATION_RELU model.policy_head.linear_g 96 32 @BIN@",	7472716,	3072, NULL,
"model.policy_head.bias2 32 1e-20 0 1 @BIN@",	7485047,	32, NULL,
"@BIN@",	7485181,	32, NULL,
"@BIN@",	7485315,	32, NULL,
"model.policy_head.act2 ACTIVATION_RELU model.policy_head.conv2p 1 1 32 2 1 1 @BIN@",	7485526,	64, NULL,
"model.policy_head.linear_pass 96 32 @BIN@",	7485824,	3072, NULL,
"model.policy_head.linear_pass_bias 32 @BIN@",	7498156,	32, NULL,
"model.policy_head.act_pass ACTIVATION_RELU model.policy_head.linear_pass2 32 2 @BIN@",	7498369,	64, NULL,
"model.value_head model.value_head.conv1 1 1 192 32 1 1 @BIN@",	7498686,	6144, NULL,
"model.value_head.bias1 32 1e-20 0 1 @BIN@",	7523304,	32, NULL,
"@BIN@",	7523438,	32, NULL,
"@BIN@",	7523572,	32, NULL,
"model.value_head.act1 ACTIVATION_RELU model.value_head.linear2 96 80 @BIN@",	7523775,	7680, NULL,
"model.value_head.bias2 80 @BIN@",	7554527,	80, NULL,
"model.value_head.act2 ACTIVATION_RELU model.value_head.linear_valuehead 80 3 @BIN@",	7554930,	240, NULL,
"model.value_head.bias_valuehead 3 @BIN@",	7555930,	3, NULL,
"model.value_head.linear_miscvaluehead 80 6 @BIN@",	7555991,	480, NULL,
"model.value_head.bias_miscvaluehead 6 @BIN@",	7557955,	6, NULL,
"model.value_head.conv_ownership 1 1 32 1 1 1 @BIN@",	7558030,	32, NULL,

};

long get_file_size(FILE *fp) {
    long cur = ftell(fp);          // 记录当前位置
    fseek(fp, 0, SEEK_END);        // 跳到文件末尾
    long size = ftell(fp);         // 获得文件大小（字节）
    fseek(fp, cur, SEEK_SET);      // 恢复文件指针位置
    return size;
}

int float_cmp(const void* a, const void* b) {
    float fa = *(const float*)a;
    float fb = *(const float*)b;
    if (fa < fb) return -1;
    else if (fa > fb) return 1;
    else return 0;
}

float focus(float (*input)[3][3], int input_channel, float (*kernel)[3][3])
{
  float s = 0.0f;
  for(int i =0; i<input_channel; i++)
  {
    for(int j=0; j<3; j++)
    {
      for(int k=0; k<3; k++)
      {
        if(input[i][j][k] > 1000000.0f || kernel[i][j][k] > 1000000.0f)
        {
          printf("warning! big number");
        }
        s += input[i][j][k] * kernel[i][j][k];
      }
    }
  }
  return s;
}

void fries(float (*input_padded)[21][21], int input_channel, float (*output)[3][3], int x, int y)
{
  for(int i=0; i<input_channel; i++)
  {
    for(int j=0; j<3; j++)
    {
      for(int k=0; k<3; k++)
      {
        output[i][j][k] = input_padded[i][x+j][y+k];
        if(output[i][j][k] > 1000000.0f)
        {
          printf("warning! big number");
        }
      }
    }
  }

}

void slip3x3(const float (*input)[19][19], int input_channel, float output_a_plane[19][19], float (*kernel)[3][3])
{
  // padding
  float (*input_padded)[19+1+1][19+1+1] = NULL;
  input_padded  = (float (*)[21][21])malloc(sizeof(float[19+1+1][19+1+1]) * input_channel);
  if (input_padded == NULL) { printf("malloc failed\n"); exit(1);}
  for(int i=0; i<input_channel; i++)
  {
    for(int j=0; j<19+1+1; j++)
    {
      for(int k=0; k<19+1+1; k++)
      {
        if(j==0 || k ==0 || j== 19+1 || k == 19+1)
          input_padded[i][j][k] = 0;
        else
          input_padded[i][j][k] = input[i][j-1][k-1];
      }
    }
  }
  // conv
  for(int i=0; i<19; i++)
  {
    for(int j=0; j<19; j++)
    {
      float (*fry)[3][3];
      fry = (float (*)[3][3])malloc(sizeof(float[3][3]) * input_channel);
      if (fry == NULL) { printf("malloc failed\n"); exit(1);}
      fries(input_padded, input_channel, fry, i, j);
      output_a_plane[i][j] = focus(fry, input_channel, kernel);
      free(fry);
    }
  }
  free(input_padded);
}

// for example: input[22][19][19], output[96][19][19], kernel[96][22][3][3]
void conv3x3(const float (*input)[19][19], int input_channel, float (*output)[19][19], int output_channel, float (*kernel)[3][3])
{
  for (int I=0; I < output_channel; I++)
  {
    float (*cannon)[3][3] = kernel + I * input_channel; /*for example: cannon[22][3][3]*/
    slip3x3(input, input_channel, output[I], cannon);
  }
}

float err3(float *mat1, const float *mat2, int x, int y, int z, float *maxdiff, int *oi, int *oj, int *ok)
{
  float s = 0.0f;
  float max_diff = -999.0f;
  for (int i=0; i<x; i++)
    for (int j=0; j<y; j++)
      for (int k=0; k<z; k++)
      {
        int idx = i * y * z + j * z + k;
        float a = mat1[idx] - mat2[idx];
        float diff;
        if(a > 0)
          diff = a;
        else
          diff = -a;

        if(diff > 0.001)
        {
          printf("error: diff too big!! %d, (%d, %d): output: %f, standard: %f, diff: %f\n", i, j, k, mat1[idx], mat2[idx], diff);
          exit(EXIT_FAILURE);
        }

        s += diff;
        if(diff > max_diff)
        {
          max_diff=diff;
          *oi = i;
          *oj = j;
          *ok = k;
        }
        if(s>1000000.0f)
        {
          printf("warning! big number");
        }
      }
  *maxdiff = max_diff;
  return s;
}

void conv1x1(const float *input, int input_channel, float *output, int output_channel, int square_side, float *kernel)
{
  for (int I=0; I < output_channel; I++)
  {
    for(int i=0; i<square_side; i++)
      for(int j=0; j<square_side; j++)
      {
        float s = 0.0f;
        for (int k=0; k < input_channel; k++)
        {
          s+=input[k*square_side*square_side + i*square_side + j]*kernel[I*input_channel + k];
        }
        output[I*square_side*square_side + i*square_side + j] = s;
      }
  }
}

void add_broadcast(const float (*input)[19][19], float (*output)[19][19], float *adder, int channel)
{
  for (int i = 0; i < channel; i++) {
    for (int j = 0; j < 19; ++j) {
      for (int k = 0; k < 19; ++k) {
        output[i][j][k] = input[i][j][k] + adder[i];
        }
      }
  }
}

void norm(const float (*input)[19][19], float (*output)[19][19], int channel, float *scale, float *bias, int board_size)
{
    for (int i = 0; i < channel; i++) {
      for (int j = 0; j < 19; ++j) {
        for (int k = 0; k < 19; ++k) {
          float x = input[i][j][k] * scale[i] + bias[i];
          if(j >= board_size || k >= board_size)
          {
            // out of board, mask filter
            output[i][j][k] = 0.0f;
          }
          else
          {
            output[i][j][k] = (x > 0.0f) ? x : 0.0f;
          }
        }
      }
    }
}
void add96(const float input[96][19][19], float output[96][19][19], float adder[96][19][19])
{
  for (int i = 0; i < 96; i++) {
    for (int j = 0; j < 19; ++j) {
      for (int k = 0; k < 19; ++k) {
          output[i][j][k] = input[i][j][k] + adder[i][j][k];
        }
      }
  }
}
void add192(const float input[192][19][19], float output[192][19][19], float adder[192][19][19])
{
  for (int i = 0; i < 192; i++) {
    for (int j = 0; j < 19; ++j) {
      for (int k = 0; k < 19; ++k) {
          output[i][j][k] = input[i][j][k] + adder[i][j][k];
        }
      }
  }
}
void ordi(int board_size, float input[96][19][19], float output[96][19][19], float scale0[96], float bias0[96], float kernel1[96][96][3][3], float scale1[96], float bias1[96], float kernel2[96][96][3][3])
{
    float maxdiff;
    int erri, errj, errk;

    float output0[96][19][19];

    norm(input, output0, 96, scale0, bias0, board_size);
    
    float output1[96][19][19];

    conv3x3(output0, 96, output1, 96, (float (*)[3][3])kernel1);
    
    float output2[96][19][19];

    norm(output1, output2, 96, scale1, bias1, board_size);

    float output3[96][19][19];

    conv3x3(output2, 96, output3, 96, (float (*)[3][3])kernel2);

    add96(input, output, output3);
}
void rowsG(float input[32][19][19], float output[96], int isValueHead, int board_size)
{
  float div = (float)(board_size * board_size);
  float sqrtdiv = (float)board_size;
  for(int I = 0; I<32; I++)
  {
    float s = 0.0f;
    float max = -1.0f;
    for(int i=0; i<19; i++)
      for(int j=0; j<19; j++)
      {
        float x = input[I][i][j];
        s += x;
        // katago原文
        // Init to -1.0 above and + mask - 1.0 is because it will effectively make all padded space into -1.0
        // which is lower than the lowest value that any current activation function will produce.
        // so the max over all valid spaces will the same as the mask over all spaces including padding
        // We're relying on all padded space being equal to 0 because this gpool only ever follows a BN+Activate with a mask.
        float maskVal = i<board_size && j<board_size? 1.0f : 0.0f;
        float temp = x + (maskVal - 1.0f);
        max = temp > max ? temp : max;
      }
        
    float mean = s / div;
    output[0 + I] = mean;
    output[32 + I] = mean * (sqrtdiv - 14.0f) * 0.1f;
    output[64 + I] = isValueHead? mean * ((sqrtdiv - 14.0f) * (sqrtdiv - 14.0f) * 0.01f - 0.1f) : max;
  }
}
void gpool(int board_size, float input[96][19][19], float output[96][19][19], float scale0[96], float bias0[96], float kernel0[64][96][3][3], float kernel1[32][96][3][3], float scale1[32], float bias1[32], float nn[64][96], float scale2[64], float bias2[64], float kernel2[96][64][3][3])
{
    float maxdiff;
    int erri, errj, errk;

    float output0[96][19][19];

    norm(input, output0, 96, scale0, bias0, board_size);

    //从这开始分为了两支，先是regular支

    float output1[64][19][19];

    conv3x3(output0, 96, output1, 64, (float (*)[3][3])kernel0);

    // g分支

    float output2[32][19][19];

    conv3x3(output0, 96, output2, 32, (float (*)[3][3])kernel1);

    float output3[32][19][19];

    norm(output2, output3, 32, scale1, bias1, board_size);
    
    float output4[96];
    rowsG(output3, output4, FALSE, board_size);

    float output5[64];
    conv1x1((float*)output4, 96, (float*)output5, 64, 1, (float*)nn);

    float output6[64][19][19];
    add_broadcast(output1, output6, output5, 64);

    // 汇聚后再来一次normconv
    // BINS[29]全是0，跳过
    // BINS[30]跳过

    float output7[64][19][19];

    norm(output6, output7, 64, scale2, bias2, board_size);

    float output8[96][19][19];

    conv3x3(output7, 64, output8, 96, (float (*)[3][3])kernel2);

    add96(input, output, output8);

}
void OO(float input[192][19][19], float output[192][19][19], int start_index)
{
    
    float output3[192][19][19];
    float scale0[192];
    float bias0[192];
    int n=0;

    for(int i=0; i < 192; i++)
    {
        scale0[i] = BINS[start_index].floats[n];
        bias0[i] = BINS[start_index+1].floats[n];
        n++;
    }
    norm(input, output3, 192, scale0, bias0, 19);
    float output4[96][19][19];
    float kernel1[96][192][1][1];

    n = 0;
    for(int l=0; l < 1; l++)       // W 先变
        for(int k=0; k < 1; k++)   // H 后变
            for(int j=0; j < 192; j++)  
                for(int i=0; i < 96; i++) 
                {
                    kernel1[i][j][k][l] = BINS[start_index+2].floats[n++];
                }
    conv1x1((float*)output3, 192, (float*)output4, 96, 19, (float*)kernel1);

    /*  加载 block[0] - ORDI-I 的4组参数 */

    float scale1[96];
    float bias1[96];
    n=0;

    for(int i=0; i < 96; i++)
    {
        scale1[i] = BINS[start_index+4].floats[n];
        bias1[i] = BINS[start_index+5].floats[n];
        n++;
    }
    float kernel2[96][96][3][3];

    n = 0;
    for(int l=0; l < 3; l++)       // W 先变
        for(int k=0; k < 3; k++)   // H 后变
            for(int j=0; j < 96; j++)  
                for(int i=0; i < 96; i++) 
                {
                    kernel2[i][j][k][l] = BINS[start_index+6].floats[n++];
                }
            
    float scale2[96];
    float bias2[96];
    n=0;

    for(int i=0; i < 96; i++)
    {
        scale2[i] = BINS[start_index+9].floats[n];
        bias2[i] = BINS[start_index+10].floats[n];
        n++;
    }
    float kernel3[96][96][3][3];

    n = 0;
    for(int l=0; l < 3; l++)       // W 先变
        for(int k=0; k < 3; k++)   // H 后变
            for(int j=0; j < 96; j++)  
                for(int i=0; i < 96; i++) 
                {
                    kernel3[i][j][k][l] = BINS[start_index+11].floats[n++];
                }

    /* 加载 block[0] - ORDI-I 的4组参数 结束 */

    float output5[96][19][19];
    ordi(19, output4, output5, scale1, bias1, kernel2, scale2, bias2, kernel3);

    /*  加载 block[0] - ORDI-II 的4组参数 */

    float scale3[96];
    float bias3[96];
    n=0;

    for(int i=0; i < 96; i++)
    {
        scale3[i] = BINS[start_index+13].floats[n];
        bias3[i] = BINS[start_index+14].floats[n];
        n++;
    }
    float kernel4[96][96][3][3];

    n = 0;
    for(int l=0; l < 3; l++)       // W 先变
        for(int k=0; k < 3; k++)   // H 后变
            for(int j=0; j < 96; j++)  
                for(int i=0; i < 96; i++) 
                {
                    kernel4[i][j][k][l] = BINS[start_index+15].floats[n++];
                }
            
    float scale4[96];
    float bias4[96];
    n=0;

    for(int i=0; i < 96; i++)
    {
        scale4[i] = BINS[start_index+18].floats[n];
        bias4[i] = BINS[start_index+19].floats[n];
        n++;
    }
    float kernel5[96][96][3][3];

    n = 0;
    for(int l=0; l < 3; l++)       // W 先变
        for(int k=0; k < 3; k++)   // H 后变
            for(int j=0; j < 96; j++)  
                for(int i=0; i < 96; i++) 
                {
                    kernel5[i][j][k][l] = BINS[start_index+20].floats[n++];
                }

    /* 加载 block[0] - ORDI-II 的4组参数 结束 */

    float output6[96][19][19];
    ordi(19, output5, output6, scale3, bias3, kernel4, scale4, bias4, kernel5);

    float output7[96][19][19];
    float scale5[96];
    float bias5[96];
    n=0;

    for(int i=0; i < 96; i++)
    {
        scale5[i] = BINS[start_index+23].floats[n];
        bias5[i] = BINS[start_index+24].floats[n];
        n++;
    }
    norm(output6, output7, 96, scale5, bias5, 19);
    float output8[192][19][19];
    float kernel6[192][96][1][1];

    n = 0;
    for(int l=0; l < 1; l++)       // W 先变
        for(int k=0; k < 1; k++)   // H 后变
            for(int j=0; j < 96; j++)  
                for(int i=0; i < 192; i++) 
                {
                    kernel6[i][j][k][l] = BINS[start_index+25].floats[n++];
                }
    conv1x1((float*)output7, 96, (float*)output8, 192, 19, (float*)kernel6);

    add192(input, output, output8);

}


void GO(float input[192][19][19], float output[192][19][19], int start_index)
{
    
    float output3[192][19][19];
    float scale[192];
    float bias[192];
    int n=0;

    for(int i=0; i < 192; i++)
    {
        scale[i] = BINS[start_index].floats[n];
        bias[i] = BINS[start_index+1].floats[n];
        n++;
    }
    norm(input, output3, 192, scale, bias, 19);
    float output4[96][19][19];
    float kernel[96][192][1][1];

    n = 0;
    for(int l=0; l < 1; l++)       // W 先变
        for(int k=0; k < 1; k++)   // H 后变
            for(int j=0; j < 192; j++)  
                for(int i=0; i < 96; i++) 
                {
                    kernel[i][j][k][l] = BINS[start_index+2].floats[n++];
                }
    conv1x1((float*)output3, 192, (float*)output4, 96, 19, (float*)kernel);

    /*  加载 Global 的参数 */

    float scale0[96];
    float bias0[96];
    float kernel0[64][96][3][3];
    float kernel1[32][96][3][3];
    float scale1[32];
    float bias1[32];
    float nn[64][96];
    float scale2[64];
    float bias2[64];
    float kernel2[96][64][3][3];
    n=0;

    for(int i=0; i < 96; i++)
    {
      scale0[i] = BINS[start_index+4].floats[n];
      bias0[i] = BINS[start_index+5].floats[n];
      n++;
    }

    n=0;
    for(int l=0; l <3; l++)
        for(int k=0; k <3; k++)
            for(int j=0; j <96; j++)
                for(int i=0; i <64; i++)
                {
                    kernel0[i][j][k][l] = BINS[start_index+6].floats[n++];
                }

    n=0;
    for(int l=0; l <3; l++)
        for(int k=0; k <3; k++)
            for(int j=0; j <96; j++)
            for(int i=0; i <32; i++)
            {
                kernel1[i][j][k][l] = BINS[start_index+7].floats[n++];
            }

    n=0;

    for(int i=0; i < 32; i++)
    {
      scale1[i] = BINS[start_index+9].floats[n];
      bias1[i] = BINS[start_index+10].floats[n];
      n++;
    }

    n=0;

    for(int j=0; j < 96; j++)
      for(int i=0; i < 64; i++)
      {
        nn[i][j] = BINS[start_index+11].floats[n];
        n++;
      }

    n=0;

    for(int i=0; i < 64; i++)
    {
      scale2[i] = BINS[start_index+14].floats[n];
      bias2[i] = BINS[start_index+15].floats[n];
      n++;
    }

    n=0;
    for(int l=0; l <3; l++)
        for(int k=0; k <3; k++)
            for(int j=0; j <64; j++)
            for(int i=0; i <96; i++)
            {
                kernel2[i][j][k][l] = BINS[start_index+16].floats[n++];
            }

    /* 加载 Global 的4组参数 结束 */

    float output5[96][19][19];
    gpool(19, output4, output5, scale0, bias0, kernel0, kernel1, scale1, bias1, nn, scale2, bias2, kernel2);

    /*  加载 block[0] - ORDI-II 的4组参数 */

    float scale3[96];
    float bias3[96];
    n=0;

    for(int i=0; i < 96; i++)
    {
        scale3[i] = BINS[start_index+18].floats[n];
        bias3[i] = BINS[start_index+19].floats[n];
        n++;
    }
    float kernel4[96][96][3][3];

    n = 0;
    for(int l=0; l < 3; l++)       // W 先变
        for(int k=0; k < 3; k++)   // H 后变
            for(int j=0; j < 96; j++)  
                for(int i=0; i < 96; i++) 
                {
                    kernel4[i][j][k][l] = BINS[start_index+20].floats[n++];
                }
            
    float scale4[96];
    float bias4[96];
    n=0;

    for(int i=0; i < 96; i++)
    {
        scale4[i] = BINS[start_index+23].floats[n];
        bias4[i] = BINS[start_index+24].floats[n];
        n++;
    }
    float kernel5[96][96][3][3];

    n = 0;
    for(int l=0; l < 3; l++)       // W 先变
        for(int k=0; k < 3; k++)   // H 后变
            for(int j=0; j < 96; j++)  
                for(int i=0; i < 96; i++) 
                {
                    kernel5[i][j][k][l] = BINS[start_index+25].floats[n++];
                }

    /* 加载 block[0] - ORDI-II 的4组参数 结束 */

    float output6[96][19][19];
    ordi(19, output5, output6, scale3, bias3, kernel4, scale4, bias4, kernel5);

    float output7[96][19][19];
    float scale5[96];
    float bias5[96];
    n=0;

    for(int i=0; i < 96; i++)
    {
        scale5[i] = BINS[start_index+28].floats[n];
        bias5[i] = BINS[start_index+29].floats[n];
        n++;
    }
    norm(output6, output7, 96, scale5, bias5, 19);
    float output8[192][19][19];
    float kernel6[192][96][1][1];

    n = 0;
    for(int l=0; l < 1; l++)       // W 先变
        for(int k=0; k < 1; k++)   // H 后变
            for(int j=0; j < 96; j++)  
                for(int i=0; i < 192; i++) 
                {
                    kernel6[i][j][k][l] = BINS[start_index+30].floats[n++];
                }
    conv1x1((float*)output7, 96, (float*)output8, 192, 19, (float*)kernel6);

    add192(input, output, output8);

}

float err1(float *mat1, const float *mat2, int x, float *maxdiff, int *oi)
{
  float s = 0.0f;
  float max_diff = -999.0f;
  for (int i=0; i<x; i++)
  {
    float a = mat1[i] - mat2[i];
    float diff;
    if(a > 0)
      diff = a;
    else
      diff = -a;
  
    if(diff > 0.001)
    {
      printf("err1 error: diff too big!! i=%d: output: %f, suppose: %f\n", i, mat1[i], mat2[i]);
      exit(EXIT_FAILURE);
    }
  
    s += diff;
    if(diff > max_diff)
    {
      max_diff=diff;
      *oi = i;
    }
    if(s>1000000.0f)
    {
      printf("warning! big number");
    }
  }
  *maxdiff = max_diff;
  return s;
}

int main() {
    const char *gzfile = "b5c192nbt-s13156480-d2171154.bin.gz";
    const char *binfile = "b5c192nbt-s13156480-d2171154.bin";

    /* 1. 打开 gzip 文件 */
    gzFile in = gzopen(gzfile, "rb");
    if (!in) {
        fprintf(stderr, "无法打开 %s\n", gzfile);
        return 1;
    }

    /* 2. 打开输出文件 */
    FILE *out = fopen(binfile, "wb");
    if (!out) {
        fprintf(stderr, "无法创建 %s\n", binfile);
        gzclose(in);
        return 1;
    }

    /* 3. 解压写入 model3e4.bin */
    char buffer[4096];
    int bytes;
    while ((bytes = gzread(in, buffer, sizeof(buffer))) > 0) {
        fwrite(buffer, 1, bytes, out);
    }

    gzclose(in);
    fclose(out);

    printf("unzip finished: %s\n", binfile);

    // 4. 打开解压出的 .bin 文件，按 float32 读取 
    FILE *fp = fopen(binfile, "rb");
    if (!fp) {
        fprintf(stderr, "无法打开 %s\n", binfile);
        return 1;
    }

    size_t total_floats = 0;
    float total_min = 99999;
    float total_max = -99999;

    long size = get_file_size(fp);

    int N = sizeof(BINS)/sizeof(bin_t);

    /* 读取 BIN 的 float */
    for (int i = 0; i < N; i++) {
        bin_t *b = &BINS[i];

        int float_count = b->bin_len;
        float *data = (float*)malloc(sizeof(float) * float_count);
        if(!data) { fprintf(stderr, "内存分配失败\n"); return 1; }

        /* 读取该区间 */
        fseek(fp, b->bin_start, SEEK_SET);
        fread(data, sizeof(float), float_count, fp);

        // 计算平均值
        double sum = 0;
        float min = data[0];
        float max = data[0];
        
        for(int j=0; j<float_count; j++) {
            float v = data[j];
            sum += v;
            if(v < min) min = v;
            if(v > max) max = v;
        }
        double mean = sum / float_count;

        printf("BIN %d: content=%s, floats=%d, min=%.6f, max=%.6f, mean=%.6f\n",
                i, b->content, float_count, min, max, mean);
        total_floats += float_count;
        if(min < total_min) total_min = min;
        if(max > total_max) total_max = max;
        b->floats = data;
    }

    printf("========\ntotal float amount: %zu, total min:%.6f, total max:%.6f\n", total_floats, total_min, total_max);
    fclose(fp);

    // 1. 使用 cnpy 读取 .npz 输入数据
    // 假设 npz 中 input 的 key 是 "input"
    cnpy::npz_t input_npz = cnpy::npz_load("0_network_input.npz");
    cnpy::NpyArray arr_in = input_npz["input"]; // 请确保 key 正确
    float (*input)[19][19] = (float (*)[19][19])arr_in.data<float>();

    // 2. 读取预期输出（用于对比验证）
    cnpy::npz_t output_npz = cnpy::npz_load("1_initial_conv_output.npz");
    cnpy::NpyArray arr_out0 = output_npz["trunkScratch"];
    float (*expected_output)[19][19] = (float (*)[19][19])arr_out0.data<float>();

    printf("NPZ Loaded: Input size %zu, Output0 size %zu\n", arr_in.num_vals, arr_out0.num_vals);

    int n = 0;
    
    float output0[192][19][19];
    float kernel0[192][22][3][3];

    n = 0;
    for(int l=0; l < 3; l++)       // W 先变
        for(int k=0; k < 3; k++)   // H 后变
            for(int j=0; j < 22; j++)  
                for(int i=0; i < 192; i++) 
                {
                    kernel0[i][j][k][l] = BINS[0].floats[n++];
                }

    conv3x3(input, 22, output0, 192, (float (*)[3][3])kernel0);

    float maxdiff;
    int erri, errj, errk;

    printf("sumdiff: %f\n", err3((float*)output0, (const float*)expected_output, 192, 19, 19, &maxdiff, &erri, &errj, &errk));
    printf("maxdiff: %f, %d, %d, %d\n", maxdiff, erri, errj, errk);

    const float inputGlobal[19] = {
    /* [0] */   0,                 /*上一步是PASS （对手下的）*/
    /* [1] */   0,                 /*上上步是PASS （当前玩家下的）*/
    /* [2] */   0,                 /*倒数第3步是PASS （对手下的）*/
    /* [3] */   0,                 /*倒数第4步是PASS （当前玩家下的）*/
    /* [4] */   0,                 /*倒数第5步是PASS （对手下的）*/
    /* [5] */   -0.325,             /*当前玩家被让多少目，除以20.0进行归一化，让对方则为负*/
    /* [6] */   0,                 /*劫争规则，日韩/中国*/
    /* [7] */   0,                 /*劫争规则，日韩/中国*/
    /* [8] */   0,                 /*是否允许自杀*/
    /* [9] */   0,                 /*计分规则 数子/数地*/
    /* [10] */  0,                 /*征税规则*/
    /* [11] */  0,                 /*征税规则*/
    /* [12] */  0,                 /*阶段（序盘/中盘/收官）*/
    /* [13] */  0,                 /*阶段（序盘/中盘/收官）*/
    /* [14] */  0,                 /*PASS是否结束当前阶段*/
    /* [15] */  0,                 /*标记是否有让子优势*/
    /* [16] */  0,                 /*具体优势值*/
    /* [17] */  0,                 /*是否有button（日本规则的特殊标记）*/
    /* [18] */  0.5               /* “一个三角波特征，用于帮助网络理解贴目与棋盘大小的奇偶性关系” */
    };

    float output1[192];
    float linear0[192][19];
    n=0;

    for(int j=0; j <19; j++)
      for(int i=0; i < 192; i++)
      {
        linear0[i][j] = BINS[1].floats[n++];
      }

    conv1x1((float*)inputGlobal, 19, (float*)output1, 192, 1, (float*)linear0);

    float output2[192][19][19];
    add_broadcast(output0, output2, output1, 192);

    output_npz = cnpy::npz_load("2_add_nc_bias_first_output.npz");
    arr_out0 = output_npz["trunkScratch"];
    expected_output = (float (*)[19][19])arr_out0.data<float>();


    printf("sumdiff: %f\n", err3((float*)output2, (const float*)expected_output, 192, 19, 19, &maxdiff, &erri, &errj, &errk));
    printf("maxdiff: %f, %d, %d, %d\n", maxdiff, erri, errj, errk);

    float output3[192][19][19];
    float output4[192][19][19];
    float output5[192][19][19];
    float output6[192][19][19];
    float output7[192][19][19];
    OO(output2, output3, 3);
    GO(output3, output4, 30);
    OO(output4, output5, 62);
    GO(output5, output6, 89);
    OO(output6, output7, 121);


    float scale_final[192];
    float bias_final[192];
    float output9[192][19][19];
    n=0;

    for(int i=0; i < 192; i++)
    {
      scale_final[i] = BINS[148].floats[n];
      bias_final[i] = BINS[149].floats[n];
      n++;
    }

    norm(output7, output9, 192, scale_final, bias_final, 19);

    output_npz = cnpy::npz_load("66_network_output.npz");
    arr_out0 = output_npz["trunk_output"];
    expected_output = (float (*)[19][19])arr_out0.data<float>();


    printf("sumdiff: %f\n", err3((float*)output9, (const float*)expected_output, 192, 19, 19, &maxdiff, &erri, &errj, &errk));
    printf("maxdiff: %f, %d, %d, %d\n", maxdiff, erri, errj, errk);

    /* 头 */

    float policy[2][19][19];
     float pass[2];
      float value[3];
      float scorevalue[6];
     float ownership[19][19];
     int board_size=19;
    /* 以下开始各种头，policy, pass, value, scorevalue, ownership一共5个头 */

    /*分支1备用*/
    float kernel15[32][192];

    n=0;

    for(int j=0; j <192; j++)
      for(int i=0; i <32; i++)
      {
        kernel15[i][j] = BINS[150].floats[n++];
      }

    float output10[32][19][19];
    conv1x1((float*)output9, 192, (float*)output10, 32, 19, (float*)kernel15);

    
    output_npz = cnpy::npz_load("68_policyhead_p1conv_output.npz");
    arr_out0 = output_npz["p1Out"];
    expected_output = (float (*)[19][19])arr_out0.data<float>();


    printf("sumdiff: %f\n", err3((float*)output10, (const float*)expected_output, 32, 19, 19, &maxdiff, &erri, &errj, &errk));
    printf("maxdiff: %f, %d, %d, %d\n", maxdiff, erri, errj, errk);

    /*分支2*/

    float kernel16[32][192];

    n=0;

    for(int j=0; j <192; j++)
      for(int i=0; i <32; i++)
      {
        kernel16[i][j] = BINS[151].floats[n++];
      }

    float output11[32][19][19];
    conv1x1((float*)output9, 192, (float*)output11, 32, 19, (float*)kernel16);

    float scale15[32];
    float bias15[32];
    float output12[32][19][19];
    n=0;

    for(int i=0; i < 32; i++)
    {
      scale15[i] = BINS[153].floats[n];
      bias15[i] = BINS[154].floats[n];
      n++;
    }

    norm(output11, output12, 32, scale15, bias15, board_size);

    float output13[96];
    rowsG(output12, output13, FALSE, board_size);


    // 从这起开始分两个头，policy和pass

    float nn2[32][96];
    n=0;

    for(int j=0; j < 96; j++)
      for(int i=0; i < 32; i++)
      {
        nn2[i][j] = BINS[155].floats[n];
        n++;
      }

    float output14[32];
    conv1x1((float*)output13, 96, (float*)output14, 32, 1, (float*)nn2);

    float output15[32][19][19];
    add_broadcast(output10, output15, output14, 32);

    // 汇聚后再来一次normconv

    float scale16[32];
    float bias16[32];
    n=0;

    for(int i=0; i < 32; i++)
    {
      scale16[i] = BINS[157].floats[n];
      bias16[i] = BINS[158].floats[n];
      n++;
    }
    float output16[32][19][19];

    norm(output15, output16, 32, scale16, bias16, board_size);

    float kernel17[2][32];

    n=0;

    for(int j=0; j <32; j++)
      for(int i=0; i <2; i++)
      {
        kernel17[i][j] = BINS[159].floats[n++];
      }

    conv1x1((float*)output16, 32, (float*)policy, 2, 19, (float*)kernel17);


    printf("check if policy is right\n");
    output_npz = cnpy::npz_load("75_policyhead_policy_output.npz");
    arr_out0 = output_npz["policy"];
    expected_output = (float (*)[19][19])arr_out0.data<float>();


    printf("sumdiff: %f\n", err3((float*)policy, (const float*)expected_output, 2, 19, 19, &maxdiff, &erri, &errj, &errk));
    printf("maxdiff: %f, %d, %d, %d\n", maxdiff, erri, errj, errk);


    float nn3[32][96];
    n=0;

    for(int j=0; j < 96; j++)
      for(int i=0; i < 32; i++)
      {
        nn3[i][j] = BINS[160].floats[n];
        n++;
      }

    float output18[32];
    conv1x1((float*)output13, 96, (float*)output18, 32, 1, (float*)nn3);

    float adder0[32];
    n=0;
    for(int i=0; i < 32; i++)
    {
      adder0[i] = BINS[161].floats[n];
      n++;
    }
    float output19[32];
    // 加Bias
    for(int i=0; i < 32; i++)
    {
      output19[i] = output18[i] + adder0[i];
    }
    // 纯relu
    for(int i=0; i < 32; i++)
    {
      output19[i] = output19[i] > 0 ? output19[i] : 0.0f;
    }
    //norm
    float mult[2][32];
    n=0;

    for(int j=0; j < 32; j++)
      for(int i=0; i < 2; i++)
      {
        mult[i][j] = BINS[162].floats[n];
        n++;
      }
    
    for(int I=0; I < 2; I++)
    {
      float s = 0.0f;
      for(int i=0; i < 32; i++)
      {
        s += mult[I][i] * output19[i];
      }
      pass[I] = s;
    }

    printf("check if pass is right\n");
    output_npz = cnpy::npz_load("79_policyhead_policy_pass_output.npz");
    arr_out0 = output_npz["policyPass"];
    float *expected_output_1dim = (float *)arr_out0.data<float>();

    printf("sumdiff: %f\n", err1((float*)pass, (const float*)expected_output_1dim, 2, &maxdiff, &erri));
    printf("maxdiff: %f, %d\n", maxdiff, erri);

    /* Value 头*/
    //先Conv
    float kernel18[32][192];

    n=0;

    for(int j=0; j <192; j++)
      for(int i=0; i <32; i++)
      {
        kernel18[i][j] = BINS[163].floats[n++];
      }

    float output21[32][19][19];
    conv1x1((float*)output9, 192, (float*)output21, 32, 19, (float*)kernel18);

    //norm
    float scale17[32];
    float bias17[32];
    float output22[32][19][19];
    n=0;

    for(int i=0; i < 32; i++)
    {
      scale17[i] = BINS[165].floats[n];
      bias17[i] = BINS[166].floats[n];
      n++;
    }

    norm(output21, output22, 32, scale17, bias17, board_size);

    //ownership在此分出

    float output23[96];
    rowsG(output22, output23, TRUE, board_size);

    //mult
    float nn4[80][96];
    n=0;

    for(int j=0; j < 96; j++)
      for(int i=0; i < 80; i++) /* 这里是80不是64*/
      {
        nn4[i][j] = BINS[167].floats[n];
        n++;
      }

    float output24[80];
    conv1x1((float*)output23, 96, (float*)output24, 80, 1, (float*)nn4);

    float adder1[80];
    n=0;
    for(int i=0; i < 80; i++)
    {
      adder1[i] = BINS[168].floats[n];
      n++;
    }
    float output25[80];
    // 加Bias
    for(int i=0; i < 80; i++)
    {
      output25[i] = output24[i] + adder1[i];
    }
    // 纯relu
    for(int i=0; i < 80; i++)
    {
      output25[i] = output25[i] > 0 ? output25[i] : 0.0f;
    }

    //分出分支value和scorevalue

    /* value分支 */
    // mult
    float nn5[3][80];
    n=0;

    for(int j=0; j < 80; j++)
      for(int i=0; i < 3; i++)
      {
        nn5[i][j] = BINS[169].floats[n];
        n++;
      }

    float output26[3];
    conv1x1((float*)output25, 80, (float*)output26, 3, 1, (float*)nn5);

    float adder2[3];
    n=0;
    for(int i=0; i < 3; i++)
    {
      adder2[i] = BINS[170].floats[n];
      n++;
    }

    // 加Bias
    for(int i=0; i < 3; i++)
    {
      value[i] = output26[i] + adder2[i];
    }

    printf("check if value is right\n");
    output_npz = cnpy::npz_load("87_valuehead_value_output.npz");
    arr_out0 = output_npz["value"];
    float* expected_value = (float*)arr_out0.data<float>();


    printf("sumdiff: %f\n", err1((float*)value, (const float*)expected_value, 3, &maxdiff, &erri));
    printf("maxdiff: %f, %d\n", maxdiff, erri);

    /* scorevalue分支 */
    float nn6[6][80];
    n=0;

    for(int j=0; j < 80; j++)
      for(int i=0; i < 6; i++)
      {
        nn6[i][j] = BINS[171].floats[n];
        n++;
      }
    
    float output28[6];
    conv1x1((float*)output25, 80, (float*)output28, 6, 1, (float*)nn6);

    float adder3[6];
    n=0;
    for(int i=0; i < 6; i++)
    {
      adder3[i] = BINS[172].floats[n];
      n++;
    }
    // 加Bias
    for(int i=0; i < 6; i++)
    {
      scorevalue[i] = output28[i] + adder3[i];
    }

    printf("check if scorevalue is right\n");
    output_npz = cnpy::npz_load("88_valuehead_scorevalue_output.npz");
    arr_out0 = output_npz["scoreValue"];
    float* expected_scorevalue = (float*)arr_out0.data<float>();


    printf("sumdiff: %f\n", err1((float*)scorevalue, (const float*)expected_scorevalue, 6, &maxdiff, &erri));
    printf("maxdiff: %f, %d\n", maxdiff, erri);


    //conv

    // ownership
    float kernel19[32];

    n=0;

    for(int i=0; i <32; i++)
    {
      kernel19[i] = BINS[173].floats[n++];
    }

    conv1x1((float*)output22, 32, (float*)ownership, 1, 19, (float*)kernel19);

    printf("check if ownership is right\n");
    output_npz = cnpy::npz_load("89_valuehead_ownership_output.npz");
    arr_out0 = output_npz["ownership"];
    expected_output = (float (*)[19][19])arr_out0.data<float>();


    printf("sumdiff: %f\n", err3((float*)ownership, (const float*)expected_output, 1, 19, 19, &maxdiff, &erri, &errj, &errk));
    printf("maxdiff: %f, %d, %d, %d\n", maxdiff, erri, errj, errk);


    return 0;
}