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

typedef int dtype;
#define HARDWARE 0
#define DEBUG    1

using namespace std;


//dtype CONV1_WEIGHT_[4*3*3*3] = {0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 3, 0, 4, 0, 0, 0, 0, 0, 0, 5, 0, 0, 6, 7, 0, 0, 0, 0, 0, 8, 0, 0, 9, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3, 0, 4, 5, 0, 0, 0, 0, 6, 0, 0, 0, 7, 8, 0, 0, 0, 0, 9, 0, 0, 0, 1, 0, 0, 0, 0};

/*dtype CONV1_WEIGHT_[4*3*3*3] = {0, 0, 0,
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
								0, 0, 0};*/ 
dtype CONV1_WEIGHT_[4*3*3*3] = {
0, 0, 0, 0, 0, 0, 0, 0, 1,
0, 1, 0, 0, 0, 0, 0, 0, 0,
0, 0, 0, 3, 0, 0, 0, 0, 4,

0, 3, 0, 0, 0, 0, 6, 7, 0,
0, 0, 0, 0, 0, 0, 0, 9, 0,
0, 1, 0, 0, 0, 0, 0, 0, 0,

0, 0, 0, 0, 0, 0, 0, 0, 0,
0, 2, 0, 0, 0, 0, 0, 0, 0,
0, 0, 0, 0, 0, 0, 0, 0, 0,

0, 0, 4, 0, 0, 0, 0, 0, 6,
0, 1, 0, 7, 0, 0, 0, 0, 0,
9, 0, 0, 0, 1, 0, 0, 0, 0};


void gen_weight(dtype* array, int g, int channel, int row, int col) {
  
  cout << "weight info\n";
  for (int i = 0; i < channel; i++) {
    for (int k = 0; k < col; k++) {
      for (int j = 0; j< row; j++) {
        for (int g_i = 0; g_i < g; g_i++) {
          if (array[g_i * channel* row * col + i * row * col + j * col +k] != 0) {
            printf("p[c++] = 0x%08x;\n", array[g_i * channel* row * col + i * row * col + j * col +k] + (g_i << 24) + (j << 16));
            
            //cout << "0x";
            //cout << "0" << hex << g_i << "0" << hex << j << "00" << "0" << hex << array[g_i * channel* row * col + i * row * col + j * col +k] << " ";
            //cout << endl;
          }
        }
      }
    }
  }
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
