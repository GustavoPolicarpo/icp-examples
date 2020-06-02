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

void execution(int run){
	
	cout << "Running " << run << "..." << '\n';
	 
	/**************************/
	
	mknod(FILERS, S_IFIFO|0640, 0);
	
	int fd;
	int pos = 0;
	char message[MESSAGE_SIZE+10];
	
	while(pos < NUMBER_MESSAGES){
		while(true){
			fd = -1;
			while(fd==-1) fd = open(FILESR, O_RDONLY);
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
		
		fd = -1;
		while(fd==-1) fd = open(FILERS, O_CREAT|O_WRONLY);
		strcpy(message, (to_string(pos)+'$').c_str());
		write(fd, message, strlen(message));
		//cout << "Sent " << message << '\n';
		close(fd);
		
		pos++;
	}
	
	
	/**************************/
	
	cout << "... done\n\n";
	
	return;
}


int main(int argc, char* argv[]) {
	
	cout << "Starting NAMED PIPE benchmark ...\n\n";
	
	for(int i=1; i<=NUMBER_EXECUTIONS; i++){
		execution(i);
		//sleep(1);
	}
	
	cout << "... done NAMED PIPE benchmark ...\n\n";

	return 0;
}
