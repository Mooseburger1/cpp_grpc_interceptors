#include <grpcpp/channel.h>
#include <grpcpp/client_context.h>
#include <grpcpp/create_channel.h>
#include <grpcpp/generic/generic_stub.h>
#include <grpcpp/impl/codegen/proto_utils.h>
#include <grpcpp/server.h>
#include <grpcpp/server_builder.h>
#include <grpcpp/server_context.h>
#include <grpcpp/support/server_interceptor.h>


namespace grpc {

class MyCustomInterceptor : public experimental::Interceptor {
public:
    MyCustomInterceptor() {}
    void Intercept(experimental::InterceptorBatchMethods* methods) override;
};

class MyInterceptorFactory : public experimental::ClientInterceptorFactoryInterface, public experimental::ServerInterceptorFactoryInterface {
public:
    experimental::Interceptor* CreateClientInterceptor(experimental::ClientRpcInfo* info) override;
    experimental::Interceptor* CreateServerInterceptor(experimental::ServerRpcInfo* info) override;
};

} // namespace grpc