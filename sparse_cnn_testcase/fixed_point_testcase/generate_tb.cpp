#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <malloc.h>
#include <iostream>

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

using namespace std;


dtype INPUT_DATA_[3*14*14] = {0.219136, 0.477551, 0.949820, 0.466169, 0.884318, 0.967277, 0.183765, 0.458039, 0.780224, 0.766448, 0.904782, 0.257585, 0.761612, 0.963505,
		0.331846, 0.402379, 0.560785, 0.554448, 0.622167, 0.191028, 0.477961, 0.360105, 0.653880, 0.916523, 0.210692, 0.606542, 0.865434, 0.109778,
		0.373556, 0.199003, 0.646520, 0.592692, 0.676554, 0.596341, 0.058860, 0.560872, 0.563617, 0.242626, 0.018911, 0.343841, 0.009073, 0.923692,
		0.601427, 0.770686, 0.887197, 0.933273, 0.173065, 0.447982, 0.487721, 0.795231, 0.639009, 0.965682, 0.155336, 0.292889, 0.882204, 0.366028,
		0.899431, 0.747638, 0.475806, 0.272987, 0.946640, 0.122326, 0.865679, 0.623194, 0.718666, 0.924540, 0.184066, 0.282284, 0.167165, 0.202977,
		0.626125, 0.176239, 0.126669, 0.227552, 0.946925, 0.013866, 0.160824, 0.119989, 0.461848, 0.648545, 0.915221, 0.100857, 0.614227, 0.070557,
		0.393746, 0.496431, 0.436585, 0.293177, 0.244069, 0.912391, 0.566164, 0.190709, 0.034716, 0.431844, 0.813904, 0.753383, 0.356383, 0.997970,
		0.035666, 0.523548, 0.200947, 0.661792, 0.699787, 0.327616, 0.889343, 0.646712, 0.341482, 0.050168, 0.766701, 0.803330, 0.698713, 0.681922,
		0.904187, 0.312940, 0.752479, 0.297933, 0.809371, 0.189064, 0.591111, 0.053439, 0.101454, 0.157275, 0.244149, 0.136171, 0.589119, 0.058052,
		0.889553, 0.945502, 0.056022, 0.925220, 0.469050, 0.256969, 0.587011, 0.168837, 0.584585, 0.476355, 0.815549, 0.926068, 0.526523, 0.582250,
		0.729398, 0.225236, 0.264172, 0.633585, 0.538175, 0.016651, 0.931518, 0.347546, 0.205714, 0.522629, 0.400985, 0.307168, 0.679904, 0.645134,
		0.443339, 0.269022, 0.703186, 0.332892, 0.214524, 0.759208, 0.258112, 0.683574, 0.016177, 0.845123, 0.852411, 0.600763, 0.321478, 0.667960,
		0.526830, 0.848000, 0.250210, 0.256228, 0.073236, 0.514382, 0.889813, 0.611411, 0.531033, 0.821331, 0.958957, 0.736747, 0.343959, 0.359942,
		0.043915, 0.023863, 0.005076, 0.487254, 0.292886, 0.708262, 0.820146, 0.507410, 0.467471, 0.078258, 0.190984, 0.483648, 0.923381, 0.043395,
		0.084411, 0.244858, 0.711355, 0.611241, 0.092858, 0.961565, 0.867469, 0.166094, 0.475947, 0.757282, 0.777505, 0.006980, 0.578613, 0.736462,
		0.743727, 0.922572, 0.096404, 0.787642, 0.946435, 0.101480, 0.274897, 0.239321, 0.809743, 0.095043, 0.746730, 0.277214, 0.173301, 0.937714,
		0.760862, 0.096681, 0.981109, 0.845273, 0.341540, 0.692463, 0.456514, 0.434398, 0.654029, 0.323983, 0.600492, 0.129976, 0.081265, 0.377997,
		0.136956, 0.659878, 0.114459, 0.880683, 0.582450, 0.210863, 0.668326, 0.528885, 0.312343, 0.943222, 0.768206, 0.122086, 0.038265, 0.514936,
		0.399300, 0.211565, 0.452650, 0.160162, 0.308247, 0.433758, 0.005435, 0.649787, 0.126222, 0.461949, 0.084185, 0.780250, 0.785932, 0.684677,
		0.910227, 0.867197, 0.062674, 0.047183, 0.527075, 0.177133, 0.927866, 0.109525, 0.387996, 0.596191, 0.638409, 0.700340, 0.539413, 0.406615,
		0.822426, 0.577678, 0.921551, 0.221726, 0.789244, 0.374201, 0.381888, 0.097491, 0.807959, 0.387323, 0.747277, 0.934181, 0.849272, 0.831462,
		0.714432, 0.635204, 0.516139, 0.624658, 0.502401, 0.578813, 0.671841, 0.029476, 0.755946, 0.599707, 0.139001, 0.143942, 0.195898, 0.777410,
		0.844281, 0.735311, 0.184025, 0.666707, 0.312990, 0.105576, 0.888433, 0.102233, 0.479777, 0.270321, 0.199724, 0.287736, 0.657643, 0.947001,
		0.221918, 0.506915, 0.778463, 0.936349, 0.142119, 0.294601, 0.561007, 0.644520, 0.873414, 0.232848, 0.673996, 0.629359, 0.832555, 0.812997,
		0.773301, 0.028453, 0.590407, 0.617582, 0.763764, 0.774432, 0.284289, 0.076753, 0.880009, 0.172722, 0.178987, 0.359786, 0.443043, 0.378710,
		0.647522, 0.100686, 0.325711, 0.869440, 0.607600, 0.104174, 0.805789, 0.749719, 0.398775, 0.366796, 0.394239, 0.272189, 0.599644, 0.068235,
		0.901549, 0.432199, 0.881232, 0.674850, 0.460652, 0.471639, 0.292432, 0.224415, 0.246071, 0.576721, 0.301169, 0.126080, 0.749443, 0.480155,
		0.485866, 0.192486, 0.858866, 0.133388, 0.293171, 0.184577, 0.002828, 0.900772, 0.288752, 0.808617, 0.650491, 0.687527, 0.175413, 0.044729,
		0.959716, 0.775058, 0.112964, 0.861265, 0.207257, 0.994196, 0.536115, 0.667908, 0.465835, 0.828546, 0.892324, 0.711906, 0.405267, 0.193493,
		0.837986, 0.154711, 0.673648, 0.323852, 0.347196, 0.532514, 0.457240, 0.640368, 0.717092, 0.460067, 0.541140, 0.005843, 0.268684, 0.191630,
		0.693370, 0.444097, 0.236360, 0.653087, 0.219155, 0.349324, 0.514352, 0.426412, 0.343520, 0.050466, 0.094320, 0.809355, 0.879013, 0.986644,
		0.521261, 0.284280, 0.180136, 0.359247, 0.438990, 0.853785, 0.683098, 0.786187, 0.386299, 0.140338, 0.426555, 0.103390, 0.600405, 0.967694,
		0.109233, 0.869090, 0.159324, 0.802604, 0.313187, 0.395684, 0.455690, 0.532342, 0.745008, 0.970042, 0.958753, 0.088528, 0.020508, 0.053073,
		0.897883, 0.899521, 0.039717, 0.419144, 0.183801, 0.219853, 0.778391, 0.622791, 0.073638, 0.461489, 0.408978, 0.459936, 0.601827, 0.835533,
		0.563327, 0.202232, 0.803227, 0.672560, 0.071322, 0.962551, 0.475164, 0.384509, 0.358235, 0.930854, 0.916851, 0.103244, 0.900896, 0.875604,
		0.191772, 0.921405, 0.928678, 0.089655, 0.820926, 0.968395, 0.508799, 0.004727, 0.188248, 0.287189, 0.627518, 0.261886, 0.748678, 0.036496,
		0.721822, 0.350505, 0.872028, 0.285149, 0.552738, 0.675255, 0.957709, 0.624060, 0.637806, 0.432873, 0.008569, 0.996042, 0.363727, 0.925420,
		0.099285, 0.264624, 0.801024, 0.291057, 0.186029, 0.729702, 0.380712, 0.006954, 0.698096, 0.889511, 0.011681, 0.886344, 0.176700, 0.639199,
		0.148230, 0.925379, 0.675694, 0.870053, 0.275884, 0.547723, 0.155202, 0.828622, 0.222978, 0.112911, 0.452681, 0.860784, 0.545784, 0.461250,
		0.856826, 0.909512, 0.386669, 0.956111, 0.174136, 0.187693, 0.247168, 0.360164, 0.917395, 0.627880, 0.367118, 0.615491, 0.517391, 0.378799,
		0.501835, 0.694091, 0.017998, 0.650066, 0.619470, 0.693692, 0.520118, 0.895354, 0.241415, 0.675320, 0.723975, 0.464393, 0.788231, 0.176656,
		0.325177, 0.334016, 0.637906, 0.182003, 0.243528, 0.024575, 0.138114, 0.417663, 0.212269, 0.385282, 0.777828, 0.129663, 0.013161, 0.144946};

dtype CONV1_WEIGHT_[4*3*3*3] = {0.530552, 0.000000, 0.000000,
		0.541743, 0.000000, 0.000000,
		0.000000, 0.000000, 0.476850,
		0.463442, 0.880725, 0.266420,
		0.000000, 0.000000, 0.000000,
		0.000000, 0.586537, 0.000000,
		0.000000, 0.653760, 0.000000,
		0.798706, 0.000000, 0.000000,
		0.000000, 0.740175, 0.000000,
		0.584288, 0.950885, 0.000000,
		0.043379, 0.000000, 0.000000,
		0.000000, 0.000000, 0.138845,
		0.000000, 0.597113, 0.000000,
		0.473045, 0.000000, 0.000000,
		0.167241, 0.925511, 0.291431,
		0.000000, 0.000000, 0.000000,
		0.727276, 0.211786, 0.000000,
		0.788265, 0.000000, 0.000000,
		0.000000, 0.154141, 0.000000,
		0.859441, 0.000000, 0.867321,
		0.000000, 0.000000, 0.932716,
		0.557291, 0.906964, 0.000000,
		0.154927, 0.031653, 0.035039,
		0.478869, 0.587197, 0.000000,
		0.000000, 0.573122, 0.000000,
		0.663252, 0.000000, 0.000000,
		0.246476, 0.127743, 0.584998,
		0.082577, 0.769074, 0.256489,
		0.000000, 0.564252, 0.000000,
		0.599291, 0.000000, 0.312491,
		0.157555, 0.349562, 0.000000,
		0.000000, 0.000000, 0.692488,
		0.000000, 0.000000, 0.340321,
		0.000000, 0.925318, 0.000000,
		0.067608, 0.112205, 0.106272,
		0.888348, 0.000000, 0.000000};

void init_input_data(dtype*** input_data) {

   printf("start\n");
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j< 14; j++) {
      for (int k = 0; k < 14; k++) {
        dtype r = (dtype) (rand()) / (dtype) (RAND_MAX);
        INPUT_DATA_[i*14*14+ j*14+ k] = r;
        printf("%f, ", r);
      }
      printf("\n");
    }
  }
  printf("\nend\n");

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
          conv1_weight[i][j][k][l] = CONV1_WEIGHT_[i*3*3*3+j*3*3+k*3+l];
        }
      }
    }
  }
}
/*
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

}*/

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
        printf("%f, ",array[i][j][k]);
      }
      printf("\n");
    }
    //printf("\n");
    //printf("\n");
  }
  printf("\n");

}

void output_4D_array(dtype**** array, int g, int channel, int row, int col) {
  for (int g_i = 0; g_i < g; g_i++)
  for (int i = 0; i < channel; i++) {
    for (int j = 0; j< row; j++) {
      for (int k = 0; k < col; k++) {
        printf("%f, ", array[g_i][i][j][k]);
      }
      printf("\n");
    }
    //printf("\n");
  }
  printf("\n");
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
              //printf("%x\n", WEIGHT[c]);
              printf("#10 weight_data <= 32'h");
              printf("%08x;\n",WEIGHT[c]);
              printf("weight_ram_w_addr <= %d;\n", c);
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
          printf("");
          printf("%08x\n", WEIGHT_LOC[c]);
    	  //cout << hex << WEIGHT_LOC[c] << endl;
      }
      c++;

    }
  }

}


int main() {

  //dtype input_data
  dtype ***input_data, ****conv1_weight;
  //define_3D_array(input_data, 3, 16, 16);
  int to = 4, ti = 3, row = 3, col = 3;
  conv1_weight= (dtype ****) malloc(sizeof(dtype***) * to);
   for (int i = 0; i < to; i++) {
     conv1_weight[i] = (dtype ***) malloc(sizeof(dtype**) * ti);
     for (int j = 0; j< ti; j++) {
       conv1_weight[i][j] = (dtype **) malloc(sizeof(dtype*) * row);
       for (int k = 0; k < row; k++) {
       	conv1_weight[i][j][k] = (dtype *) malloc(sizeof(dtype) * col);
       }
     }
   }

   int channel = 3;
   row = 16;
   col = 16;
   input_data = (dtype ***) malloc(sizeof(dtype**) * channel);
    for (int i = 0; i < channel; i++) {
      input_data[i] = (dtype **) malloc(sizeof(dtype*) * row);
      for (int j = 0; j< row; j++) {
        input_data[i][j] = (dtype *) malloc(sizeof(dtype) * col);
      }
    }


  init_input_data(input_data);

  output_3D_array(input_data, 3, 16, 16);

 // define_4D_array(conv1_weight, 4, 3, 3, 3);
  init_conv1_weight(conv1_weight);

  printf("weight start\n");
  output_4D_array(conv1_weight, 4, 3, 3, 3);
  printf("weight end\n");
  output_weight(conv1_weight, 4, 3, 3, 3);
  //gen_weight(conv1_weight, 4, 3, 3, 3);
  //cout << " gen_weigth_loc end\n";
  //count_loc_info(conv1_weight, 4, 3, 3, 3);

  dtype*** conv1_output;
  //define_3D_array(conv1_output, 4, 14, 14);
  channel = 4;
   row = 14;
   col = 14;
   conv1_output = (dtype ***) malloc(sizeof(dtype**) * channel);
    for (int i = 0; i < channel; i++) {
      conv1_output[i] = (dtype **) malloc(sizeof(dtype*) * row);
      for (int j = 0; j< row; j++) {
        conv1_output[i][j] = (dtype *) malloc(sizeof(dtype) * col);
      }
    }

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
   
    for (int i = 0; i < 3*14; i++) { 
      cout << "#10 input_data <= 224'h";
      for (int j = 0; j < 7; j++) {
		 printf("%08x", INPUT[i*7+j]);   
                 //cout << hex  << INPUT[i*7 +j];
	    }
	    cout << ";\n";
	    cout << "input_data_ram_w_addr <= " << dec << i << ";\n";
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
      Xil_Out32(0x4000000C, 5);  // start = 1, slv_reg3 == 4
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