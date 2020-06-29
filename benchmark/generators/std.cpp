#include<unistd.h>
#include<iostream>
#include<iomanip> 
#include<string.h>
#include<vector>
#include<fstream>
#include<math.h>

#define NUMBER_EXECUTIONS 100

using namespace std;

void getStd(){
	string aux;
	vector <double> tms;
	double avg;
	
	int i = 1, cnt = 0;
	while(cnt<NUMBER_EXECUTIONS){
		getline(cin, aux);
		if(i>=9 && (i-9)%4==0){
			stringstream ss; ss << aux;
			int xx = 0;
			while(ss >> aux){
				if(xx==10){
					double xua = atof(aux.c_str());
					tms.push_back(xua);
					cout << xua << "\n";
					cnt++;
					break;
				}
				xx++;
			}
		}
		i++;
	}
	
	getline(cin, aux);
	getline(cin, aux);
	getline(cin, aux);
	getline(cin, aux);
	
	getline(cin, aux);
	stringstream ss; ss << aux;
	int xx = 0;
	while(ss >> aux){
		if(xx==2){
			double xua = atof(aux.c_str());
			avg = xua;
			cout << avg << '\n';
			break;
		}
		xx++;
	}
	
	double dp = 0.0;
	for(int i=0; i<tms.size(); i++){
		dp = dp + (avg-tms[i])*(avg-tms[i]);
	}
	dp = dp/tms.size();
	dp = sqrt(dp);
	
	printf("O desvio padrão foi de %.10lf\n", dp);
	
	return;
}

int main(int argc, char* argv[]) {
	
	
	cout << "Calculating std over execution time ...\n";
	getStd();
	cout << "... done\n\n";
	
	
	
   
	return 0;
}
