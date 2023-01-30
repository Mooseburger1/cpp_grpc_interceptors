cmake_minimum_required(VERSION 3.15)


project(interceptors)



set(CMAKE_TOOLCHAIN_FILE "/home/moose/vcpkg/scripts/buildsystems/vcpkg.cmake")
set(VCPKG_HOME "$ENV{HOME}/vcpkg")


################# Includes directories for vcpkg
################# vcpkg downloads and manages dependencies
include_directories(/home/moose/vcpkg/installed/x64-linux/include/)

link_directories(/home/moose/vcpkg/installed/x64-linux/lib/)


################# Config to compile and link .proto files
set(protobuf_MODULE_COMPATIBLE TRUE)
find_package(Protobuf REQUIRED)
message(STATUS "Using protobuf ${protobuf_VERSION}")

# Protobuf-compiler
set(_PROTOBUF_PROTOC $<TARGET_FILE:protobuf::protoc>)

find_package(gRPC CONFIG REQUIRED)
message(STATUS "Using gRPC ${gRPC_VERSION}")
set(_GRPC_GRPCPP gRPC::grpc++)
set(_GRPC_CPP_PLUGIN_EXECUTABLE $<TARGET_FILE:gRPC::grpc_cpp_plugin>)


get_filename_component(hw_proto "mathtest.proto" ABSOLUTE)
get_filename_component(hw_proto_path "${hw_proto}" PATH)

set(hw_proto_srcs "${CMAKE_CURRENT_BINARY_DIR}/mathtest.pb.cc")
set(hw_proto_hdrs "${CMAKE_CURRENT_BINARY_DIR}/mathtest.pb.h")
set(hw_grpc_srcs "${CMAKE_CURRENT_BINARY_DIR}/mathtest.grpc.pb.cc")
set(hw_grpc_hdrs "${CMAKE_CURRENT_BINARY_DIR}/mathtest.grpc.pb.h")

add_custom_command(
      OUTPUT "${hw_proto_srcs}" "${hw_proto_hdrs}" "${hw_grpc_srcs}" "${hw_grpc_hdrs}"
      COMMAND ${_PROTOBUF_PROTOC}
      ARGS --grpc_out "${CMAKE_CURRENT_BINARY_DIR}"
        --cpp_out "${CMAKE_CURRENT_BINARY_DIR}"
        -I "${hw_proto_path}"
        --plugin=protoc-gen-grpc="${_GRPC_CPP_PLUGIN_EXECUTABLE}"
        "${hw_proto}"
      DEPENDS "${hw_proto}")

################# Include generated *.pb.h files
include_directories("${CMAKE_CURRENT_BINARY_DIR}")


################# Set file name environment variables
set(serv_exe "${CMAKE_CURRENT_BINARY_DIR}/../server.cpp")
set(client_exe "${CMAKE_CURRENT_BINARY_DIR}/../client.cpp")

set(math_serv_srcs "${CMAKE_CURRENT_BINARY_DIR}/../mathservice.cpp")
set(math_serv_hdrs "${CMAKE_CURRENT_BINARY_DIR}/../mathservice.h")

set(math_client_srcs "${CMAKE_CURRENT_BINARY_DIR}/../mathclient.cpp")
set(math_client_hdrs "${CMAKE_CURRENT_BINARY_DIR}/..mathclient.h")

set(interceptor_serv_srcs "${CMAKE_CURRENT_BINARY_DIR}/../serverinterceptor.cpp")
set(interceptor_serv_hdrs "${CMAKE_CURRENT_BINARY_DIR}/../serverinterceptor.h")

################# Compile and link
add_executable(server ${serv_exe} 
  ${hw_proto_srcs}
  ${hw_grpc_srcs}
  ${math_serv_srcs}
  ${interceptor_serv_srcs})
target_link_libraries(server
  ${_REFLECTION}
  ${_GRPC_GRPCPP}
  ${_PROTOBUF_LIBPROTOBUF})

add_executable(client ${client_exe}
  ${hw_proto_srcs}
  ${hw_grpc_srcs}
  ${math_client_srcs}
  ${interceptor_serv_srcs})
target_link_libraries(client
  ${_REFLECTION}
  ${_GRPC_GRPCPP}
  ${_PROTOBUF_LIBPROTOBUF})
