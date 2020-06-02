#include<unistd.h>
#include<iostream>
#include<iomanip> 
#include<string.h>
#include<fstream>
#include<assert.h>
#include <fcntl.h>


#define NUMBER_EXECUTIONS 100
#define MESSAGE_SIZE 10 // should be [10, 1000, 100000]
#define NUMBER_MESSAGES 100000 // should be [100000, 1000, 10]

using namespace std;

string words[NUMBER_MESSAGES];
char writtenMessage[MESSAGE_SIZE+10], readMessage[MESSAGE_SIZE+10];

double execution(int run, int pipefds[]){
	
	clock_t start, end;
	cout << "Running " << run << "..." << '\n';
	 
	start = clock(); 
	
	int pos = 0;
	while(pos < NUMBER_MESSAGES){
		strcpy(writtenMessage, (to_string(pos)+'$'+words[pos]).c_str());
		write(pipefds[1], writtenMessage, sizeof(writtenMessage));
		read(pipefds[0], readMessage, sizeof(readMessage));
		assert(strcmp(readMessage, writtenMessage)==0);
		
		pos++;
	}
	
	
	end = clock();
	
	cout << "... done." << '\n';
	 
	double time_taken = double(end - start) / double(CLOCKS_PER_SEC); 
   	cout << "Time taken by PIPE in execution " << run << " is : " << fixed << time_taken << setprecision(8) << " sec\n\n"; 
   	
   	return time_taken;
}

void saveWords(char path[]){
	ifstream input(path);
	int i = 0;
	while(i<NUMBER_MESSAGES){
		getline(input, words[i]);
		i++;
	}
	return;
}

int main(int argc, char* argv[]) {
	
	cout << "Getting correct words ...";
	saveWords(argv[1]);
	cout << "... done\n\n";
	
	int pipefds[2];
	pipe(pipefds);
	
	fcntl(pipefds[0], F_SETPIPE_SZ, int(MESSAGE_SIZE+10));
	fcntl(pipefds[1], F_SETPIPE_SZ, int(MESSAGE_SIZE+10));
	
	cout << "Starting PIPE benchmark ...\n\n";
	
	double totalTime = 0.0;
	for(int i=1; i<=NUMBER_EXECUTIONS; i++){
		totalTime += execution(i, pipefds);
	}
	
	close(pipefds[0]);
	close(pipefds[1]);
	
	cout << "... done PIPE benchmark ...\n\n";
	cout << "Total time: " << fixed << totalTime << setprecision(8) << " sec\n";
	cout << "Average time: " << fixed << totalTime/NUMBER_EXECUTIONS << setprecision(8) << " sec\n";
	
   
	return 0;
}
