#include <string>
#include <iostream>
#include <vector>

#include <grpcpp/grpcpp.h>
#include "build/mathtest.grpc.pb.h"
#include "mathservice.h"
#include "serverinterceptor.h"


int main(int argc, char** argv) {
    std::string address("0.0.0.0:5000");
    MathServiceImplementation service;

    grpc::ServerBuilder builder;

    builder.AddListeningPort(address, grpc::InsecureServerCredentials());
    builder.RegisterService(&service);

//////////////// section for interceptors ////////////////////////////////////
    std::vector<std::unique_ptr<grpc::experimental::ServerInterceptorFactoryInterface>> creators;
    creators.push_back(std::make_unique<grpc::MyInterceptorFactory>());

    builder.experimental().SetInterceptorCreators(std::move(creators));
//////////////////////////////////////////////////////////////////////////////

    std::unique_ptr<grpc::Server> server(builder.BuildAndStart());
    std::cout << "Server listening on port: " << address << std::endl;

    server -> Wait();

    return 0;
}

