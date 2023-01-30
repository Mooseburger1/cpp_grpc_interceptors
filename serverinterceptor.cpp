#include <grpcpp/grpcpp.h>
#include "serverinterceptor.h"

namespace grpc{
    void MyCustomInterceptor::Intercept(experimental::InterceptorBatchMethods* methods) {
    if (methods->QueryInterceptionHookPoint(
            experimental::InterceptionHookPoints::PRE_SEND_INITIAL_METADATA)) {
                std::cout << "PRE_SEND_INITIAL_METADATA From Interceptor" << std::endl;
    } else if (methods->QueryInterceptionHookPoint(
                   experimental::InterceptionHookPoints::
                       POST_RECV_INITIAL_METADATA)) {
      std::cout << "POST_RECV_INITIAL_METADATA From Interceptor" << std::endl;
    } else if (methods->QueryInterceptionHookPoint(
                   experimental::InterceptionHookPoints::PRE_SEND_CANCEL)) {
      std::cout << "PRE_SEND_CANCEL From Interceptor" << std::endl;
    }
    methods->Proceed();
  };

  experimental::Interceptor* MyInterceptorFactory::CreateClientInterceptor(experimental::ClientRpcInfo* info) { return new MyCustomInterceptor();}
  experimental::Interceptor* MyInterceptorFactory::CreateServerInterceptor(experimental::ServerRpcInfo* info) { return new MyCustomInterceptor();}
}