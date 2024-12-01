#include <sstream>
#include <fstream>
#include <algorithm>
#include <iostream>
#include <chrono>
int naive(int* data1, int* data2);
void actualWork() {
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
    }
    std::cout<< "left to right is: -----------------" << naive(data1, data2)<< std::endl;
}
int main(int argc, char* argv[]) {
    auto start = std::chrono::high_resolution_clock::now();
    
    //benchmarking above --------------------------------------------------------------------------




    for(int i =0; i<1000 ; i++){
        actualWork();
    }



    //benchmarking result-----------------------------------------------------------------------------

    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    std::cout << "Time taken-----------------------: " << duration.count()/1000 << " MicroSeconds" << std::endl;
    return 0;
}
int naive(int* data1, int* data2) {
    int simSum=0;
    for(int i = 0; i < 1000; i++) {
        simSum+= data1[i] * std::count(data2, data2+1000, data1[i]);
    }
    return simSum;
}