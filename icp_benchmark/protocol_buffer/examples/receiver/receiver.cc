#include <ctime>
#include <fstream>
#include <iostream>
#include <string>
#include <unistd.h>

#include "msgbook.pb.h"

using namespace std;

#define FILESR "FILESR"
#define FILERS "FILERS"

#define NUMBER_EXECUTIONS 100
#define MESSAGE_SIZE 10 // should be [10, 1000, 100000]
#define NUMBER_MESSAGES 100000 // should be [100000, 1000, 10]

string words[NUMBER_MESSAGES];

void execution(int run){
	
	cout << "Running " << run << "..." << '\n';
	 
	/**************************/
	
	GOOGLE_PROTOBUF_VERIFY_VERSION;
	
	int pos = 0;
	while(pos < NUMBER_MESSAGES){
		while(true){
			icp::MsgBook msg_book;
	    	string pathSR = FILESR;
	    	
	    	fstream input(pathSR.c_str(), ios::in | ios::binary);
	    	int status = msg_book.ParseFromIstream(&input);
	    	sleep(1);
	    	if(status==0) cout << ("Unable to read msg book") << '\n';
	    	if(!msg_book.msg_size()) continue;
	    	cout << "hehehe\n";
	    	
	    	const icp::Msg& msg = msg_book.msg(0);
	    	char message[MESSAGE_SIZE+10];
	    	cout << "Received " << msg.buf() << '\n';
	    	
	    	strcpy(message, (msg.buf()).c_str());
	    	char *aux = strtok(message, "$");
			if(strcmp(aux, to_string(pos).c_str())==0){
				break;
			}
	    }
	    
		icp::MsgBook msg_book;
    	icp::Msg* msg = msg_book.add_msg();
    	msg->set_buf((to_string(pos)+'$'));
    	
    	cout << "Sent " << (to_string(pos)+'$') << '\n';
    	
	    string pathRS = FILERS;
        
	    fstream output(pathRS.c_str(), ios::out | ios::trunc | ios::binary);
	    msg_book.SerializeToOstream(&output);
	    
	    
	    
	    pos++;
	}
	
	google::protobuf::ShutdownProtobufLibrary();
	
	/**************************/
	
	cout << "... done." << '\n';
	
	return;
	 
}

int main(int argc, char* argv[]) {
	
	
	cout << "Starting PROTOCOL BUFFER benchmark ...\n\n";
	
	for(int i=1; i<=NUMBER_EXECUTIONS; i++){
		execution(i);
	}
	
	cout << "... done PROTOCOL BUFFER benchmark ...\n\n";
	
	return 0;
}
