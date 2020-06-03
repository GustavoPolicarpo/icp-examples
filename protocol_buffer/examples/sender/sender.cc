#include <ctime>
#include <fstream>
#include <iostream>
#include <string>

#include "msgbook.pb.h"

using namespace std;

#define FILE "MYFILE"

void error(std::string message){
	std::cout << message << '\n';
	exit(1);
}

int main(void) {

    GOOGLE_PROTOBUF_VERIFY_VERSION;
	
	string message;
	int type;
	int status;
	
    for(;;){
    	icp::MsgBook msg_book;
    	
    	cout << "Write the message (\"end\" to finish): "; std::cin >> message;
    	
    	if(message=="end"){
    		type = -1;
    	}else{
	    	cout << "Write the type (must be an integer): "; std::cin >> type;
	    	cin.ignore();
	    }
    
    	printf("Sent string: \"%s\" and string length is %d and type is %d\n", message.c_str(), message.size(), (int)type);
    	
    	icp::Msg* msg = msg_book.add_msg();
    	
    	msg->set_buf(message);
    	msg->set_type(type);
	    
	    string path = FILE;
        
	    fstream output(path.c_str(), ios::out | ios::trunc | ios::binary);
	    status = msg_book.SerializeToOstream(&output);
	    if(status==0) error("Unable to write msg book");
	    
	    if(message=="end") break;
    }
    
	google::protobuf::ShutdownProtobufLibrary();

    return 0;
}
