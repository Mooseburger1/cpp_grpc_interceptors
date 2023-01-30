#ifndef MATHSERVICE_H
#define MATHSERVICE_H

#include "build/mathtest.grpc.pb.h"

class MathServiceImplementation final : public mathtest::MathTest::Service
{
public:
    grpc::Status sendRequest(grpc::ServerContext* context,
                             const mathtest::MathRequest* request,
                             mathtest::MathReply* reply) override;

};

#endif