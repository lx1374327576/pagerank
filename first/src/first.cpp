//============================================================================
// Name        : first.cpp
// Author      : Xiang Li
// Email       : 1374327576@qq.com
// Version     : v1.0
// Time        : 2019-03-04
// Description : first attempt in C++
//============================================================================

#include<cstdio>
#include<fstream>
#include<iostream>
#include<ctime>
#define MAXN 50005
#define MAXM 5000005
#define INPUT_FILE_NAME "WikiData.txt"
#define OUTPUT_FILE_NAME "WikiData_out.txt"
#define OUTPUT_INFORMATION_FINE_NAME "WikiData_out_info.txt"

using namespace std;

void input_from_file();

void random_calculate();

void output_to_file();

int point[MAXN],ending[MAXM],next[MAXM];
int ans[MAXN];
int n,m;//the number of nodes and sides
double runningTime;

int main() {
	input_from_file();
	clock_t startTime, endTime;
	startTime=clock();
	random_calculate();//answer is saved in the array ans
	endTime=clock();
	runningTime=(endTime-startTime)*1.0/CLOCKS_PER_SEC;
	output_to_file();
	return 0;
}

void input_from_file(){
	ifstream readFile(INPUT_FILE_NAME);
	if (readFile.fail()){
		cout<<"打开文件错误"<<endl;
		system("pause");
		exit(0);
	}
	int a,b;
	m=0;
	while (readFile>>a>>b){
		m++;
		ending[m]=point[a];
		point[a]=m;
		ending[m]=b;
	}
	cout<<m<<endl;
	readFile.close();
}

void output_to_file(){

}

void random_calculate(){

}
