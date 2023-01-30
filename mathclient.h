#ifndef MATHCLIENT_H
#define MATHCLIENT_H

#include <grpcpp/grpcpp.h>
#include "build/mathtest.grpc.pb.h"

class MathClient {
private:
    std::unique_ptr<mathtest::MathTest::Stub> stub_;

public:
    MathClient(std::shared_ptr<grpc::Channel> channel) : stub_(mathtest::MathTest::NewStub(channel)){}

    int sendRequest(int a, int b);


};

#endif