#include<iostream>
#include<sys/stat.h>
#include<unistd.h>
#include<fcntl.h>
#include<iomanip> 
#include<string.h>
#include<fstream>
#include<assert.h>

using namespace std;

#define FILESR "PIPE_SR"
#define FILERS "PIPE_RS"

#define NUMBER_EXECUTIONS 100
#define MESSAGE_SIZE 100000 // should be [10, 1000, 100000]
#define NUMBER_MESSAGES 10 // should be [100000, 1000, 10]

string words[NUMBER_MESSAGES];

double execution(int run){
	
	clock_t start, end;
	cout << "Running " << run << "..." << '\n';
	 
	start = clock(); 
	
	/**************************/
	
	mknod(FILESR, S_IFIFO|0640, 0);
	
	
	int fd;
	int pos = 0;
	char message[MESSAGE_SIZE+10];
	
	while(pos < NUMBER_MESSAGES){
		fd = -1;
		while(fd==-1) fd = open(FILESR, O_CREAT|O_WRONLY);
		strcpy(message, (to_string(pos)+'$'+words[pos]).c_str());
		write(fd, message, strlen(message));
		//cout << "Sent " << message << '\n';
		close(fd);

		while(true){
			fd = -1;
			while(fd==-1) fd = open(FILERS, O_RDONLY);
			int message_size = read(fd, message, sizeof(message));
			message[message_size] = '\0';
			//cout << "Receive " << message << '\n';
			char *aux = strtok(message, "$");
			if(strcmp(aux, to_string(pos).c_str())==0){
				close(fd);
				break;
			}
			close(fd);
		}	
		
		pos++;
	}
	
	/**************************/
	
	end = clock();
	
	cout << "... done." << '\n';
	 
	double time_taken = double(end - start) / double(CLOCKS_PER_SEC); 
   	cout << "Time taken by NAMED PIPE in execution " << run << " is : " << fixed << time_taken << setprecision(8) << " sec\n\n"; 
   	
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
	
	system("rm " FILESR);
	system("rm " FILERS);
	
	cout << "Getting correct words ...";
	saveWords(argv[1]);
	cout << "... done\n\n";
	
	
	cout << "Start the cliente ...\n\n";
	sleep(5);
	
	cout << "Starting NAMED PIPE benchmark ...\n\n";
	
	
	double totalTime = 0.0;
	for(int i=1; i<=NUMBER_EXECUTIONS; i++){
		totalTime += execution(i);
	}
	
	cout << "... done NAMED PIPE benchmark ...\n\n";
	cout << "Total time: " << fixed << totalTime << setprecision(8) << " sec\n";
	cout << "Average time: " << fixed << totalTime/NUMBER_EXECUTIONS << setprecision(8) << " sec\n";
	
	system("rm " FILESR);
	system("rm " FILERS);

	return 0;
}

