#include <omp.h>
#include <ctime>
#include <vector>
#include <iostream>
#include<random>
#include <Eigen/Dense>
#include "example_eigen.h"
//#include <unistd.h> // for sleep
#include <chrono>
#include <thread>
#include <stdlib.h>
#include <time.h>

using Eigen::MatrixXd;
using Eigen::VectorXd;

std::vector<int> pll_looper(){
int limit=50;
std::vector<int> vi(limit);
#pragma omp parallel for
for (int i=0; i<limit; i++)
	{
	vi.push_back(i*i);
	}
return vi;
}

std::vector<VectorXd> run_linalgebra(){
// Thanks https://stackoverflow.com/questions/21292881/matrixxfrandom-always-returning-same-matrices
// for pointing out how to change random seed each time. 
std::srand((unsigned int) time(0));
MatrixXd arraygeom(5,3);
arraygeom = MatrixXd::Random(5,3);
std::vector<VectorXd> solutions(2);
VectorXd row1 = arraygeom.block(0,0,1,3).transpose();
arraygeom.rowwise() -= row1.transpose();
VectorXd d = VectorXd::Random(4);

solutions = spiesberger_wahlberg_solution(arraygeom, d);
//std::this_thread::sleep_for(std::chrono::milliseconds(1));
return solutions;	
}


std::vector<std::vector<VectorXd>> pll_linalgebra(){
int num_runs = 20000;
std::vector<std::vector<VectorXd>> many_solutions(num_runs);

#pragma omp parallel for
for (int i=0; i<num_runs; i++){
	many_solutions[i] = run_linalgebra();
	run_linalgebra();
	run_linalgebra();
	run_linalgebra();
	}
return many_solutions;
}



int main(){
std::vector<int> vi;
vi = pll_looper();
std::vector<VectorXd> q;
std::vector<std::vector<VectorXd>> many;
	
std::cout << "Miaow" << std::endl;
q = run_linalgebra();

time_t my_time = time(NULL);
printf("%s", ctime(&my_time));
std::cout << "Bow" << std::endl;
many = pll_linalgebra();

time_t my_time2 = time(NULL);
printf("%s", ctime(&my_time2));	

return 0;
}


