#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <iostream>


typedef int dtype;
#define DEBUG    1

using namespace std;


dtype INPUT_DATA_[3*14*14] = {7, 6, 9, 3, 1, 15, 10, 12, 9, 13, 10, 11, 2, 11, 5, 7, 8, 9, 14, 4, 11, 2, 13, 6, 11, 4, 4, 1, 12, 0, 11, 11, 2, 15, 12, 4, 12, 8, 11, 12, 2, 10, 1, 3, 5, 15, 7, 0, 9, 1, 10, 5, 10, 11, 11, 0, 10, 4, 12, 2, 11, 0, 15, 11, 3, 13, 3, 0, 8, 7, 8, 0, 9, 13, 13, 4, 12, 15, 14, 7, 10, 11, 12, 5, 13, 2, 14, 9, 8, 0, 4, 2, 10, 9, 4, 8, 10, 10, 6, 7, 14, 2, 12, 12, 10, 4, 0, 6, 0, 3, 5, 12, 7, 14, 0, 2, 0, 8, 6, 5, 4, 1, 14, 4, 12, 4, 4, 14, 11, 12, 9, 5, 5, 15, 8, 5, 9, 2, 14, 3, 4, 14, 12, 5, 9, 14, 7, 9, 3, 1, 13, 12, 6, 5, 15, 10, 15, 15, 7, 6, 3, 12, 7, 15, 8, 13, 1, 4, 7, 9, 1, 5, 6, 1, 4, 15, 5, 10, 2, 10, 12, 9, 8, 10, 12, 7, 10, 9, 13, 2, 3, 9, 12, 9, 11, 0, 3, 6, 12, 2, 4, 8, 11, 8, 7, 13, 6, 10, 14, 3, 14, 2, 4, 1, 1, 13, 12, 7, 0, 9, 14, 1, 1, 1, 14, 3, 11, 10, 10, 10, 11, 9, 1, 6, 5, 12, 12, 4, 8, 7, 4, 13, 15, 3, 14, 8, 12, 11, 4, 5, 4, 3, 5, 12, 11, 15, 2, 9, 10, 11, 13, 5, 11, 1, 10, 12, 12, 6, 1, 11, 10, 10, 5, 2, 14, 0, 5, 3, 11, 4, 12, 5, 14, 8, 8, 4, 12, 11, 3, 14, 12, 7, 13, 11, 11, 2, 7, 4, 4, 12, 11, 9, 0, 10, 6, 3, 14, 5, 8, 10, 9, 9, 6, 3, 0, 10, 10, 9, 10, 14, 12, 14, 0, 10, 2, 2, 0, 5, 10, 4, 8, 5, 8, 4, 6, 2, 0, 12, 7, 4, 5, 1, 12, 12, 6, 1, 12, 0, 12, 11, 13, 13, 15, 15, 9, 4, 6, 3, 5, 1, 7, 4, 4, 3, 14, 0, 13, 6, 8, 10, 12, 10, 6, 2, 4, 8, 10, 9, 2, 6, 10, 4, 8, 1, 14, 4, 9, 13, 5, 3, 1, 6, 3, 15, 9, 10, 6, 2, 13, 7, 1, 8, 3, 10, 5, 13, 12, 7, 14, 1, 14, 7, 10, 12, 11, 6, 15, 8, 12, 10, 5, 8, 14, 1, 9, 9, 12, 11, 8, 9, 15, 5, 1, 11, 10, 5, 14, 11, 9, 3, 11, 0, 4, 4, 1, 14, 9, 12, 15, 3, 8, 9, 8, 4, 11, 3, 5, 10, 14, 8, 8, 2, 12, 3, 6, 4, 3, 15, 2, 0, 4, 14, 15, 2, 5, 9, 9, 2, 5, 6, 4, 3, 15, 13, 3, 4, 15, 13, 13, 4, 1, 12, 9, 7, 3, 7, 9, 0, 3, 3, 4, 3, 9, 4, 1, 5, 3, 8, 4, 3, 10, 4, 11, 1, 9, 0, 2, 7, 4, 8, 9, 8, 7, 5, 5, 0, 10, 10, 15, 2, 0, 9, 2, 12, 4, 6, 10, 1, 11, 3, 15, 2, 12, 3, 4, 9, 7, 8, 13, 6, 2, 12, 5, 9, 2, 8, 5, 10, 8, 13, 2, 2, 7, 10, 11, 8, 15, 1, 9, 3, 0, 14, 14, 3, 1, 15, 9, 10, 9, 5, 1, 3, 15, 14, 5, 2, 7, 1};

dtype CONV1_WEIGHT_[4*3*3*3] = {0, 0, 0,
		                        0, 0, 0,
								0, 0, 1,

								0, 0, 0,
								0, 2, 0,
								0, 0, 0,

								0, 0, 0,
								3, 0, 0,
								0, 0, 4,


								0, 0, 0,
								5, 0, 0,
								6, 7, 0,

								0, 0, 0,
								0, 8, 0,
								0, 9, 0,

								0, 1, 0,
								0, 0, 0,
								0, 0, 0,


								0, 0, 0,
								0, 0, 0,
								0, 0, 0,

								0, 0, 0,
								0, 2, 0,
								0, 0, 0,

								0, 0, 0,
								0, 0, 0,
								0, 0, 0,

								3, 0, 4,
								5, 0, 0,
								0, 0, 6,

								0, 0, 0,
								7, 8, 0,
								0, 0, 0,

								9, 0, 0,
								0, 1, 0,
								0, 0, 0}; 

/*dtype CONV1_WEIGHT_[4*3*3*3] = {0, 0, 0,
		                        0, 0, 0,
								0, 0, 1,

								0, 0, 0,
								0, 2, 0,
								0, 0, 0,

								0, 0, 0,
								3, 0, 4,
								0, 0, 0,


								0, 0, 0,
								5, 0, 0,
								6, 7, 0,

								0, 0, 0,
								0, 8, 0,
								0, 9, 0,

								0, 1, 0,
								0, 0, 0,
								0, 0, 0,


								0, 0, 0,
								0, 0, 0,
								0, 0, 0,

								0, 0, 0,
								0, 2, 0,
								0, 0, 0,

								0, 0, 0,
								0, 0, 0,
								0, 0, 0,

								3, 0, 4,
								5, 0, 0,
								0, 0, 6,

								0, 0, 0,
								7, 8, 0,
								0, 0, 0,

								9, 0, 0,
								0, 1, 0,
								0, 0, 0};  */



void init_input_data(dtype*** input_data) {

   
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j< 16; j++) {
      for (int k = 0; k < 16; k++) {
        if (j == 0 || j == 15 || k == 0 || k == 15)
           input_data[i][j][k] = (dtype)(0);
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
          conv1_weight[i][j][k][l] = CONV1_WEIGHT_[i*3*3*3+j*3*3+k*3+l];
        }
      }
    }
  }
}

void define_4D_array(dtype ****&array, int to, int ti, int row, int col) {
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
        printf("%d\t",array[i][j][k]);
      }
      printf("\n");
    }
    printf("\n");
  }
  printf("\n");

}

void output_4D_array(dtype**** array, int g, int channel, int row, int col) {
  for (int g_i = 0; g_i < g; g_i++)
  for (int i = 0; i < channel; i++) {
    for (int j = 0; j< row; j++) {
      for (int k = 0; k < col; k++) {
        printf("%d, ", array[g_i][i][j][k]);
      }
      printf("\n");
    }
  }
  printf("\n");
}

void output_weight(dtype**** array, int g, int channel, int row, int col) {
  for (int g_i = 0; g_i < g; g_i++) {
    for (int j = 0; j< row; j++) {
      for (int i = 0; i < channel; i++) {
        for (int k = 0; k < col; k++) {
          printf("%d,", array[g_i][i][j][k]);
        }
         printf("\t");
      }
      printf("\n");
    }
    printf("\n");
  }
}


int main() {

 

  dtype ***input_data, ****conv1_weight;
  define_3D_array(input_data, 3, 16, 16);
  init_input_data(input_data);
  
  output_3D_array(input_data, 3, 16, 16);
  
  define_4D_array(conv1_weight, 4, 3, 3, 3);
  init_conv1_weight(conv1_weight);
  
  cout << "output weight 1\n";
  output_4D_array(conv1_weight, 4, 3, 3, 3);
  cout << "output weight 2\n";
  output_weight(conv1_weight, 4, 3, 3, 3);
  
  dtype*** conv1_output;
  define_3D_array(conv1_output, 4, 14, 14);
  conv(16, 16, 3, 3, 14, 14, 4, 1, input_data, conv1_weight, conv1_output);

  
  cout << "output result\n\n";
  output_3D_array(conv1_output, 4, 14, 14);
  


  
  

  return 0;
}





