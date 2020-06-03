#include <fstream>
#include <iostream>
#include <string>

#include "msgbook.pb.h"

using namespace std;

#define FILE "MYFILE"

inline bool exists_file (const std::string& name) {
    ifstream f(name.c_str());
    return f.good();
}

void error(std::string message){
	std::cout << message << '\n';
	exit(1);
}

int main(void) {

    GOOGLE_PROTOBUF_VERIFY_VERSION;

	string message;
	int type;
	int status;
	
	while(42){
		string path = FILE;
		if(!exists_file(path)) continue;
		
		icp::MsgBook msg_book;
		
		fstream input(path.c_str(), std::ofstream::in);
		status = msg_book.ParseFromIstream(&input);
		if(status==0) error("Unable to read msg book");
		
		if(!msg_book.msg_size()) continue;
		const icp::Msg& msg = msg_book.msg(0);

		printf("Received string: \"%s\" and string length is %d and type is %d\n", (msg.buf()).c_str(), (int)(msg.buf()).size(), (int)msg.type());
		
		system("rm " FILE);
		
		if(msg.buf()=="end") break;
	}
	
	google::protobuf::ShutdownProtobufLibrary();


    return 0;
}
