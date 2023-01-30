#include <string>

#include <grpcpp/grpcpp.h>
#include "build/mathtest.grpc.pb.h"
#include "mathclient.h"


int main(int argc, char** argv) {

    std::string address("0.0.0.0:5000");
    MathClient client(
        grpc::CreateChannel(address, 
                            grpc::InsecureChannelCredentials()
        )
    );
    
    int response;

    int a = 3;
    int b = 4;

    response = client.sendRequest(3,4);

    std::cout << "Answer received: " << a << " * " << b << " = " << response << std:: endl;

    return 0;

}