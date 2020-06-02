#include <ctime>
#include <fstream>
#include <iostream>
#include <string>
#include <iomanip>
#include <unistd.h>

#include "msgbook.pb.h"

using namespace std;

#define FILESR "FILESR"
#define FILERS "FILERS"


#define NUMBER_EXECUTIONS 100
#define MESSAGE_SIZE 10// should be [10, 1000, 100000]
#define NUMBER_MESSAGES 10000// should be [100000, 1000, 10]

string words[NUMBER_MESSAGES];

double execution(int run){
	
	GOOGLE_PROTOBUF_VERIFY_VERSION;
	
	clock_t start, end;
	cout << "Running " << run << "..." << '\n';
	 
	start = clock(); 
	
	/**************************/
	
	int pos = 0;
	while(pos < NUMBER_MESSAGES){
		icp::MsgBook msg_book;
    	icp::Msg* msg = msg_book.add_msg();
    	
    	msg->set_buf((to_string(pos)+'$'+words[pos]));
    	
        string pathSR = FILESR;
	    fstream output(pathSR.c_str(), ios::out | ios::trunc | ios::binary);
		int status = msg_book.SerializeToOstream(&output);
		if(status==0) cout << "Unable to write msg book" << '\n';
	    cout << "Sent " << (to_string(pos)+'$'+words[pos]) << '\n';
	    
	    
	    while(true){
	    	string pathRS = FILERS;
	    	fstream input(pathRS.c_str(), ios::in | ios::binary);
	    	msg_book.ParseFromIstream(&input);
	    	if(!msg_book.msg_size()) continue;
	    	
	    	const icp::Msg& msg = msg_book.msg(0);
	    	char message[MESSAGE_SIZE+10];
    	    cout << "Received " << msg.buf() << '\n';
    	    
	    	strcpy(message, (msg.buf()).c_str());
	    	char *aux = strtok(message, "$");
			if(strcmp(aux, to_string(pos).c_str())==0){
				break;
			}
	    }
	    
	    pos++;
	}
	
	google::protobuf::ShutdownProtobufLibrary();
	
	/**************************/
	
	end = clock();
	
	cout << "... done." << '\n';
	 
	double time_taken = double(end - start) / double(CLOCKS_PER_SEC); 
   	cout << "Time taken by PROTOCOL BUFFER in execution " << run << " is : " << fixed << time_taken << setprecision(8) << " sec\n\n"; 
   	
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
	sleep(3);
	
	cout << "Starting PROTOCOL BUFFER benchmark ...\n\n";
	
	
	double totalTime = 0.0;
	for(int i=1; i<=NUMBER_EXECUTIONS; i++){
		totalTime += execution(i);
	}
	
	cout << "... done PROTOCOL BUFFER benchmark ...\n\n";
	cout << "Total time: " << fixed << totalTime << setprecision(8) << " sec\n";
	cout << "Average time: " << fixed << totalTime/NUMBER_EXECUTIONS << setprecision(8) << " sec\n";
	
	system("rm " FILESR);
	system("rm " FILERS);

	return 0;
}
