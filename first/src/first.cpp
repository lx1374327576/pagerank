//============================================================================
// Name        : first.cpp
// Author      : Xiang Li
// Email       : 1374327576@qq.com
// Version     : v1.0
// Time        : 2019-03-04
// Description : first attempt in C++
//============================================================================

#include <cstdio>
#include <fstream>
#include <iostream>
#include <ctime>
#include <iomanip>

#define MAXN 50005
#define MAXM 5000005
#define INPUT_FILE_NAME "WikiData.txt"
#define OUTPUT_FILE_NAME "WikiData_out.txt"
#define OUTPUT_INFORMATION_FILE_NAME "file_info.txt"
#define RESTART_COE 0.15 //the start of a new page
#define EPS 1e-8

using namespace std;

void input_from_file();

void random_calculate();

void output_to_file();

double abs(double x){if (x<0)return -x;else return x;}

string getTime();

int point[MAXN],ending[MAXM],next_side[MAXM];
int queue[MAXN];
double ans[MAXN],ans_tmp[MAXN];
int n,m;//the number of nodes and sides
double runningTime;
string start_time;

int main() {
	start_time=getTime();
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
	n=0;
	while (readFile>>a>>b){
		m++;
		next_side[m]=point[a];
		point[a]=m;
		ending[m]=b;
		if (a>n) n=a;
		if (b>n) n=b;
	}
	cout<<n<<endl;
	cout<<m<<endl;
	readFile.close();
}

void output_to_file(){
	ofstream writeFile(OUTPUT_FILE_NAME);
	for (int i=1;i<=n;i++){
		writeFile<<"node "<<i<<" expect value: "<<setiosflags(ios::fixed)<<setprecision(10)<<ans[i]<<endl;
	}
	ofstream writeFile_log(OUTPUT_INFORMATION_FILE_NAME,ios::app);
	cout<<"running time:"<<setiosflags(ios::fixed)<<setprecision(6)<<runningTime<<"s"<<endl;
	writeFile_log<<"start time:"<<start_time<<endl;
	writeFile_log<<"input_file:"<<INPUT_FILE_NAME<<endl;
	writeFile_log<<"output_file:"<<OUTPUT_FILE_NAME<<endl;
	writeFile_log<<"node:"<<n<<endl;
	writeFile_log<<"side:"<<m<<endl;
	writeFile_log<<"running time:"<<setiosflags(ios::fixed)<<setprecision(6)<<runningTime<<"s"<<endl;
	writeFile_log<<"---------------------------"<<endl;
	writeFile.close();
	writeFile_log.close();
}

string getTime(){
	time_t timep;
	time (&timep);
	char tmp[64];
	strftime(tmp, sizeof(tmp), "%Y-%m-%d %H:%M:%S",localtime(&timep) );
	return tmp;
}

void random_calculate(){
	cout<<"calculate start"<<endl;
	for (int i=1;i<=n;i++)ans[i]=1.0/n;
	int repeat_time=0;
	int flag;
	while (true){
		flag=1;
		for (int i=1;i<=n;i++)ans_tmp[i]=RESTART_COE/n;
		for (int i=1;i<=n;i++){
			int j=point[i];
			int tmp=0;
			while (j!=0){
				tmp++;
				queue[tmp]=ending[j];
				j=next_side[j];
			}
			for (int j=1;j<=tmp;j++)ans_tmp[queue[j]]+=ans[i]*(1-RESTART_COE)/tmp;
		}
		for (int i=1;i<=n;i++){
			if (abs(ans_tmp[i]-ans[i])>EPS)flag=0;
			ans[i]=ans_tmp[i];
		}
		if (flag)break;
		repeat_time++;
		cout<<repeat_time<<endl;
	}
}
