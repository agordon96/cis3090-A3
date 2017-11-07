//Aaron Gordon 0884023
#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

int *vectorA, **vectorB, *vectorC;
int numThreads;
int size;

double multiply_matrix() {
  int i, j;
  double start, end;
  
  srand(time(NULL));
  for(i = 0; i < size; i++) {
    vectorA[i] = rand() % 10;
    for(j = 0; j < size; j++) {
      vectorB[i][j] = rand() % 10;
    }
  }
  
  omp_set_num_threads(numThreads);
  start = omp_get_wtime();
  #pragma omp parallel
  {
    int x, y;
    #pragma omp for
    for(x = 0; x < size; x++) {
      int sum = 0;
      for(y = 0; y < size; y++) {
        sum += (vectorA[y] * vectorB[x][y]);
      }
      
      vectorC[x] = sum;
    }
  }
  end = omp_get_wtime();
  
  return end - start;
}

int main(int argc, char* argv[]) {
  int i;
  int isG;
  
  if((argc != 3 && argc != 2) || (argc == 2 && strcmp(argv[1], "-g") != 0)) {
    fprintf(stderr, "Arguments: ./a3 [# of threads] [vector/matrix size] or ./a3 -g.\n");
    exit(0);
  }
  
  if(argc == 3) {
    numThreads = strtol(argv[1], NULL, 10);
    if(numThreads < 1) {
      fprintf(stderr, "strtol failed. Number of threads must be a whole number greater than 0.\n");
      exit(0);
    }
    
    size = strtol(argv[2], NULL, 10);
    if(size < 1) {
      fprintf(stderr, "strtol failed. Size must be a whole number greater than 0.\n");
      exit(0);
    }
    
    isG = 0;
  } else {
    size = 20000;
    isG = 1;
  }
  
  vectorA = (int*)malloc(sizeof(int) * size);
  vectorB = (int**)malloc(sizeof(int*) * size);
  vectorC = (int*)malloc(sizeof(int) * size);
  
  for(i = 0; i < size; i++) {
    vectorB[i] = (int*)malloc(sizeof(int) * size);
  }
  
  if(isG) {
    printf("Size\tThreads\n--\t1\t2\t4\n");
    
    size = 100;
    printf("100\t");
    for(numThreads = 1; numThreads < 5; numThreads = numThreads * 2) {
      printf("%.5f\t", multiply_matrix());
    }
    printf("\n");
    
    size = 1000;
    printf("1000\t");
    for(numThreads = 1; numThreads < 5; numThreads = numThreads * 2) {
      printf("%.5f\t", multiply_matrix());
    }
    printf("\n");
    
    size = 10000;
    printf("10000\t");
    for(numThreads = 1; numThreads < 5; numThreads = numThreads * 2) {
      printf("%.5f\t", multiply_matrix());
    }
    printf("\n");
    
    size = 20000;
    printf("20000\t");
    for(numThreads = 1; numThreads < 5; numThreads = numThreads * 2) {
      printf("%.5f\t", multiply_matrix());
    }
    printf("\n");
  } else {
    printf("Time taken for %d size matrix multiplication with %d threads: %.5f\n", size, numThreads, multiply_matrix());
  }
  
  for(i = 0; i < size; i++) {
    free(vectorB[i]);
  }
  
  free(vectorA);
  free(vectorB);
  free(vectorC);

  return 0; 
}