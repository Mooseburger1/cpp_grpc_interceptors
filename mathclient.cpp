#include <string>

#include "mathclient.h"
#include "build/mathtest.grpc.pb.h"
#include <grpcpp/grpcpp.h>

int MathClient::sendRequest(int a, int b) {
    mathtest::MathRequest request;
    
    request.set_a(a);
    request.set_b(b);

    mathtest::MathReply reply;

    grpc::ClientContext context;

    grpc::Status status = stub_->sendRequest(&context, request, &reply);

    if(status.ok()) {
        return reply.result();
    }

    std::cout << status.error_code() << ": " << status.error_message() << std::endl;
    return -1;
    
}