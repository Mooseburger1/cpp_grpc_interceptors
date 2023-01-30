#include <string>
#include <iostream>

#include <grpcpp/grpcpp.h>
#include "mathservice.h"
#include "build/mathtest.grpc.pb.h"

grpc::Status MathServiceImplementation::sendRequest(
        grpc::ServerContext* context,
        const mathtest::MathRequest* request,
        mathtest::MathReply* reply) {

            int a = request -> a();
            int b = request -> b();

            std::cout << "Received request with a: " << a << " and b: " << b << std::endl;

            int result = a * b;
            reply -> set_result(result);
            
            std::cout << "Responding with " << a << " * " << b << " = " << result << std::endl; 
            return grpc::Status::OK;
        };

