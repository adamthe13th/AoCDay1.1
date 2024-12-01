#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <algorithm>
#include <cassert>
#include <chrono>
#include <set>
#include <immintrin.h>
void sortVector(std::vector<int>& vec) {
    std::sort(vec.begin(), vec.end());
}
int intrinsicDiff(int* data1, int* data2) {
    int sum=0;
    int temp[4] = {0,0,0,0};
    __m128i sumi ;
    for (size_t i=0; i + 4 <= 1000; i += 4) {
        __m128i v1 = _mm_load_si128(reinterpret_cast<const __m128i*>(&data1[i]));  // Load 4 ints
        __m128i v2 = _mm_load_si128(reinterpret_cast<const __m128i*>(&data2[i]));  // Load 4 ints

        __m128i diff = _mm_sub_epi32(v1, v2); // Compute the differences

        
        diff = _mm_abs_epi32(diff);  // absolute difference
        sumi = _mm_add_epi32(sumi, diff);
        // Horizontal sum (SIMD)
        
    }
    _mm_store_si128(reinterpret_cast<__m128i*>(temp), sumi);

    sum += temp[0] + temp[1] + temp[2] + temp[3];
    return sum;
}
int seqDiff(int* data1, int* data2) {
    int sum=0;
    for (size_t i =0; i<1000; i++)
    {
        sum+= abs(data1[i] - data2[i]);
    }
    return sum;
}
void Actualwork(int choice) {
    std::ifstream file("../day1input");
    std::string line;
    int data1[1000];
    int data2[1000];
    int counter =0;
    while (std::getline(file, line)) {
        std::istringstream iss(line);
        int num1, num2;
        if (iss >> num1 >> num2) {
            data1[counter] = num1;
            data2[counter] = num2;
            counter++;
        }
            //else {std::cout<< "parsing failed!"<<std::endl;}
    }
    
    //assert(data1.size()==data2.size());
    std::sort(data1, data1+1000);
    std::sort(data2, data2+1000);
    size_t sum = choice==1? intrinsicDiff(data1, data2) : seqDiff(data1, data2);
    
    //std::cout<<"Ditance is: ---------" << sum << std::endl;
}


int main(int argc, char* argv[]) {
    auto start = std::chrono::high_resolution_clock::now();
    
    //benchmarking above --------------------------------------------------------------------------




    for(int i =0; i<10000 ; i++){
        Actualwork(1);
    }



    //benchmarking result-----------------------------------------------------------------------------

    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start);
    std::cout << "Time taken using SIMD: " << duration.count()/10000 << " NanoSeconds" << std::endl;

    start = std::chrono::high_resolution_clock::now();
    
    //benchmarking above --------------------------------------------------------------------------




    for(int i =0; i<10000 ; i++){
        Actualwork(1);
    }



    //benchmarking result-----------------------------------------------------------------------------

    end = std::chrono::high_resolution_clock::now();
    duration = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start);
    std::cout << "Time taken using Sequential: " << duration.count()/10000 << " NanoSeconds" << std::endl;
    
    return 0;
}