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


void gen_weight(dtype* array, int g, int channel, int row, int col) {
  
  cout << "weight info\n";
  int num = 0;
  for (int i = 0; i < channel; i++) {
    for (int k = 0; k < col; k++) {
      for (int j = 0; j< row; j++) {
        for (int g_i = 0; g_i < g; g_i++) {
          if (array[g_i * channel* row * col + i * row * col + j * col +k] != 0) {
            num++;
            printf("p[c++] = 0x%08x;\n", static_cast<int>(array[g_i * channel* row * col + i * row * col + j * col +k] * pow(2, 10) + 0.5) + (g_i << 24) + (j << 16));
            
            //cout << "0x";
            //cout << "0" << hex << g_i << "0" << hex << j << "00" << "0" << hex << array[g_i * channel* row * col + i * row * col + j * col +k] << " ";
            //cout << endl;
          }
        }
      }
    }
  }
  cout << "weight num = " << num << endl;
  
}


void gen_weight_loc(dtype* array, int g, int channel, int row, int col) {
  
  cout << "weight loc info\n";
  for (int i = 0; i < channel; i++) {
    for (int k = 0; k < col; k++) {
      cout << "p[c++] = 0x00000";
      for (int j = 0; j< row; j++) {
        int count = 0;
        for (int g_i = 0; g_i < g; g_i++) {
          if (array[g_i * channel* row * col + i * row * col + j * col +k]!= 0)
            count++;
        }
        cout << hex << count ;
      }
      cout << ";" << endl;
    }
  }
  
 
}



int main() {

  gen_weight(CONV1_WEIGHT_, 4, 3, 3, 3);
  gen_weight_loc(CONV1_WEIGHT_, 4, 3, 3, 3);



  return 0;
}
