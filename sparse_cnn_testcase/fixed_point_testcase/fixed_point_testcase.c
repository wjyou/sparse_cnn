
//#define HARDWARE_PLATFORM

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <malloc.h>

#ifdef HARDWARE_PLATFORM
#include "platform.h"
#include "xil_io.h"
#include "xparameters.h"
#include "sleep.h"
#include "xil_cache.h"
#endif

typedef float dtype;
#define HARDWARE 0
#define DEBUG    1



dtype CONV1_WEIGHT_[4*3*3*3] = {0.0f};

dtype INPUT_DATA_[3*14*14] = {0.0f};

void init_input_data(dtype*** input_data) {

  for (int i = 0; i < 3; i++) {
    for (int j = 0; j< 14; j++) {
      for (int k = 0; k < 14; k++) {
        dtype r = (dtype) (rand()) / (dtype) (RAND_MAX);
        INPUT_DATA_[i*14*14+ j*14+ k] = r;
      }
    }
  }

  for (int i = 0; i < 3; i++) {
    for (int j = 0; j< 16; j++) {
      for (int k = 0; k < 16; k++) {
        if (j == 0 || j == 15 || k == 0 || k == 15)
           input_data[i][j][k] = (dtype)(0);
        //input_data[i][j+1][k+1] = dtype(INPUT_DATA_[i*14*14+ j*14+ k]); ///dtype(255.0);
      }
    }
  }
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j< 14; j++) {
      for (int k = 0; k < 14; k++) {
        input_data[i][j+1][k+1] = (dtype)(INPUT_DATA_[i*14*14+ j*14+ k]); ///dtype(255.0);
      }
    }
  }

}


void init_conv1_weight(dtype ****conv1_weight) {

  for (int i = 0; i < 4; i++) {
    for (int j = 0; j< 3; j++) {
      for (int k = 0; k < 3; k++) {
        for (int l = 0; l < 3;l++) {
          if (rand() % 10 < 5)
            CONV1_WEIGHT_[i*3*3*3+j*3*3+k*3+l] = (dtype)(0);
          else
            CONV1_WEIGHT_[i*3*3*3+j*3*3+k*3+l] = (dtype) (rand()) / (dtype) (RAND_MAX);
        }
      }
    }
  }


  for (int i = 0; i < 4; i++) {
    for (int j = 0; j< 3; j++) {
      for (int k = 0; k < 3; k++) {
        for (int l = 0; l < 3;l++) {
          conv1_weight[i][j][k][l] = CONV1_WEIGHT_[i*3*3*3+j*3*3+k*3+l];
        }
      }
    }
  }
}

void define_4D_array(dtype **** &array, int to, int ti, int row, int col) {
  array = (dtype ****) malloc(sizeof(dtype***) * to);
  for (int i = 0; i < to; i++) {
    array[i] = (dtype ***) malloc(sizeof(dtype**) * ti);
    for (int j = 0; j< ti; j++) {
      array[i][j] = (dtype **) malloc(sizeof(dtype*) * row);
      for (int k = 0; k < row; k++) {
      	array[i][j][k] = (dtype *) malloc(sizeof(dtype) * col);
      }
    }
  }
}
void define_3D_array(dtype*** &array, int channel, int row, int col) {
  array = (dtype ***) malloc(sizeof(dtype**) * channel);
  
  for (int i = 0; i < channel; i++) {
    array[i] = (dtype **) malloc(sizeof(dtype*) * row);
    for (int j = 0; j< row; j++) {
      array[i][j] = (dtype *) malloc(sizeof(dtype) * col);
    }
  }

}

void conv(int input_R, int input_C, int input_N,
           int weight_K, int output_R, int output_C, int output_N,
           int S,
           //float* input_data, float* weight, float* bias, float* output) {
           dtype*** input_data, dtype**** weight, /*float* bias,*/ dtype*** output) {
  for (int row = 0; row < output_R; row++) {
    for (int col = 0; col < output_C; col++) {
      for (int to = 0; to < output_N; to++) {
        for (int ti = 0; ti < input_N; ti++) {
          for (int i = 0; i < weight_K; i++) {
            for (int j = 0; j< weight_K; j++) {
               output[to][row][col] += weight[to][ti][i][j] * input_data[ti][S*row+i][S*col+j];
               //output[to*output_R*output_C + row*output_C + col] +=
               //  weight[to*input_N*weight_K*weight_K+ ti*weight_K*weight_K+i*weight_K+j] *
               //  input_data[ti*input_R*input_C + (S*row+i)*input_C + S*col+ j];
            }
          }
        }
        //output[to*output_R*output_C + row*output_C + col] += bias[to];
        //output[to][row][col] += bias[to];
      }
    }
  }
}
void output_3D_array(dtype*** array, int channel, int row, int col) {
  for (int i = 0; i < channel; i++) {
    for (int j = 0; j< row; j++) {
      for (int k = 0; k < col; k++) {
        printf("%f ",array[i][j][k]);
      }
      printf("\n");
    }
    printf("\n");
  }
}

void output_4D_array(dtype**** array, int g, int channel, int row, int col) {
  for (int g_i = 0; g_i < g; g_i++)
  for (int i = 0; i < channel; i++) {
    for (int j = 0; j< row; j++) {
      for (int k = 0; k < col; k++) {
        printf("%f ", array[g_i][i][j][k]);
      }
      printf("\n");
    }
    printf("\n");
  }
}

void output_weight(dtype**** array, int g, int channel, int row, int col) {
  for (int g_i = 0; g_i < g; g_i++) {
    for (int j = 0; j< row; j++) {
      for (int i = 0; i < channel; i++) {
        for (int k = 0; k < col; k++) {
          printf("%f\t", array[g_i][i][j][k]);
        }
         printf("\n");
      }
      printf("\n");
    }
    printf("\n");
  }
}
/*
void count_loc_info(dtype**** array, int g, int channel, int row, int col) {

  for (int i = 0; i < channel; i++) {
    for (int j = 0; j< row; j++) {
      for (int k = 0; k < col; k++) {
        int count = 0;
        for (int g_i = 0; g_i < g; g_i++) {
          if (array[g_i][i][j][k] != 0)
            count++;
        }
        printf("%d  ", count);
      }
      printf("\n");
    }
    printf("\n");
  }

  for (int i = 0; i < channel; i++) {
    for (int j = 0; j< row; j++) {
      for (int k = 0; k < col; k++) {
        for (int g_i = 0; g_i < g; g_i++) {
          if (array[g_i][i][j][k] != 0)
            cout <<  array[g_i][i][j][k] << " ";
        }
      }
    }
  }
  cout << endl;
} */
/*
void gen_weight(dtype**** array, int g, int channel, int row, int col) {
  for (int i = 0; i < channel; i++) {
    for (int k = 0; k < col; k++) {
      for (int j = 0; j< row; j++) {
        for (int g_i = 0; g_i < g; g_i++) {
          if (array[g_i][i][j][k] != 0) {
            cout << "0x";
            cout << "0" << hex << g_i << "0" << hex << j << "00" << "0" << hex << array[g_i][i][j][k] << " ";
            cout << endl;
          }
        }
      }
    }
  }
}*/

void hardware_weight_init(dtype**** array, int* WEIGHT, int g, int channel, int row, int col) {
  int c = 0;
  if (DEBUG) {
    printf("output weight\n");
  }
  for (int i = 0; i < channel; i++) {
    for (int k = 0; k < col; k++) {
      for (int j = 0; j< row; j++) {
        for (int g_i = 0; g_i < g; g_i++) {
          if (array[g_i][i][j][k] != (dtype)(0)) {
            WEIGHT[c] = (g_i << 24)  +   (j << 16)   + (0x0000FFFF & (int)(array[g_i][i][j][k] * pow(2, 10)));
            if (DEBUG) {
              printf("%x\n", WEIGHT[c]);
            	//cout << hex << WEIGHT[c] << "\n";
            }
            c++;
          }
        }
      }
    }
  }
  if (DEBUG) {}
    //cout << "num of weight = " << dec << c << endl;
}


void hardware_weight_loc_init(dtype**** array, int* WEIGHT_LOC, int g, int channel, int row, int col) {

  if (DEBUG) {
    printf("output weight loc \n");
  }
  int c = 0;
  for (int i = 0; i < channel; i++) {
    for (int k = 0; k < col; k++) {

      WEIGHT_LOC[c] = 0;
      for (int j = 0; j< row; j++) {
        int count = 0;
        for (int g_i = 0; g_i < g; g_i++) {
          if (array[g_i][i][j][k] != (dtype)(0))
            count++;
        }
        WEIGHT_LOC[c] += (count << (4*(2 - j)));
      }
      if (DEBUG) {
          printf("%x\n", WEIGHT_LOC[c]);
    	  //cout << hex << WEIGHT_LOC[c] << endl;
      }
      c++;

    }
  }

}


int main() {

  //dtype input_data
  dtype ***input_data, ****conv1_weight;
  define_3D_array(input_data, 3, 16, 16);
  init_input_data(input_data);

  output_3D_array(input_data, 3, 16, 16);

  define_4D_array(conv1_weight, 4, 3, 3, 3);
  init_conv1_weight(conv1_weight);

  output_4D_array(conv1_weight, 4, 3, 3, 3);
  output_weight(conv1_weight, 4, 3, 3, 3);
  //gen_weight(conv1_weight, 4, 3, 3, 3);
  //cout << " gen_weigth_loc end\n";
  //count_loc_info(conv1_weight, 4, 3, 3, 3);

  dtype*** conv1_output;
  define_3D_array(conv1_output, 4, 14, 14);
  conv(16, 16, 3, 3, 14, 14, 4, 1, input_data, conv1_weight, conv1_output);

  if (DEBUG) {
    printf("output golden result\n");
    output_3D_array(conv1_output, 4, 14, 14);
  }




#ifdef HARDWARE_PLATFORM
    init_platform();
#endif
    printf("start\n");

    printf("stage 1, init input data, weight, and weight loc_info\n");

    int* INPUT;
    if (HARDWARE)
      INPUT = (int *)0x00200000;
    else
      INPUT = (int*)malloc(sizeof(int) *3*14*7);
    int  c = 0;
    for (int j = 0; j < 14; j++) {
      for (int i = 0; i < 3; i++) {
        for (int k = 0; k < 14; k = k + 2) {
          INPUT[c++] = (int)((int)(INPUT_DATA_[i*14*14+j*14+k] * pow(2, 10)) * pow(2, 16)) + (int)(INPUT_DATA_[i*14*14+j*14+k+1] * pow(2, 10));
        }
      }
    }
    if (DEBUG) {
      printf("debug input data \n");
      int a = 0x0000FFFF;
      int b = 0xFFFF0000;
      for (int i = 0; i < 3*14*7; i++) {
        float x2 = (float)(INPUT[i] & a)/ pow(2, 10);
        float x1 = (float)((INPUT[i] & b) >> 16) / pow(2, 10);
        printf("%x\t%f\t%f\t", INPUT[i], x1, x2);
        if(i % 7 == 6) printf("\n");
      }
    }
    int * WEIGHT;
    if (HARDWARE)
       WEIGHT = (int*)0x00300000;
    else
       WEIGHT = (int*)malloc(sizeof(int) *4*3*3*3);
    hardware_weight_init(conv1_weight, WEIGHT, 4, 3, 3, 3);

    int *WEIGHT_LOC;
    if (HARDWARE)
       WEIGHT_LOC = (int*)0x00400000;
    else
       WEIGHT_LOC = (int*)malloc(sizeof(int) *3*3);
    hardware_weight_loc_init(conv1_weight, WEIGHT_LOC, 4, 3, 3, 3);

    printf("stage 2, start transfer and compute\n");
#ifdef HARDWARE_PLATFORM
      Xil_Out32(0x4000000C, 0);
      Xil_Out32(0x40000000, 1);   // reset = 1   slv_reg0 == 1
      Xil_Out32(0x40000000, 0);   // reset = 0
      Xil_Out32(0x4000000C, 4);  // start = 1, slv_reg3 == 4
      sleep(5);
#endif
    printf("stage 3, get result data\n");
#ifdef HARDWARE_PLATFORM
    int RESULT[4*14*14] = {0};
    int* p = (int *)0x00500000;
    int q = 0;
    for (int j = 0; j < 14; j++) {
      for (int k = 0; k < 14; k++) {
        int a = 0x0000FFFF;
        int b = 0xFFFF0000;
        int x2 = p[q] & a;
        int x1 = (p[q] & b) >> 16;

        RESULT[0*14*14+j*14+k] = x2;
        RESULT[1*14*14+j*14+k] = x1;
        x2 = p[q+1] & a;
        x1 = (p[q+1] & b) >> 16;
        RESULT[2*14*14+j*14+k] = x2;
        RESULT[3*14*14+j*14+k] = x1;

        q = q+2;
      }
    }

    for (int i = 0; i < 4; i++) {
      for (int j = 0; j < 14; j++) {
        for (int k = 0; k < 14; k++) {
          printf("err = %f\t", RESULT[i*14*14+j*14+k] - conv1_output[i][j][k]);

          //printf("%d\t", RESULT[i*14*14+j*14+k]);
        }
        printf("\n");
      }
      printf("\n");
    }


#endif


    printf("done\n");



  return 0;
}



