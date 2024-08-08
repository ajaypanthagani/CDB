cmake_minimum_required(VERSION 3.28.3)
project(cdb VERSION 1.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Include directories
include_directories(include)

# Find Boost libraries
find_package(Boost REQUIRED COMPONENTS filesystem system)

# Find Protobuf package
find_package(absl REQUIRED)
find_package(Protobuf 3.21 REQUIRED)
find_package(gRPC REQUIRED)

# Collect all source files including generated protobuf files
file(GLOB_RECURSE SOURCES "src/*.cpp" ${PROTO_SRCS} ${PROTO_HDRS})

# Add the executable
add_executable(cdb ${SOURCES})

# Get all .proto files under src/proto/
file(GLOB PROTO_FILES "src/proto/*.proto")

target_link_libraries(cdb PUBLIC protobuf::libprotobuf gRPC::grpc++)

# Automatically generate protobuf C++ files
protobuf_generate(
    TARGET cdb 
    PROTOS ${PROTO_FILES})
protobuf_generate(
    TARGET cdb
    LANGUAGE grpc 
    GENERATE_EXTENSIONS .grpc.pb.h .grpc.pb.cc
    PLUGIN "protoc-gen-grpc=\$<TARGET_FILE:gRPC::grpc_cpp_plugin>"
    PROTOS ${PROTO_FILES})

# Include the directory where protobuf generates files
include_directories(${CMAKE_CURRENT_BINARY_DIR})

# Link Boost libraries
target_link_libraries(cdb PRIVATE Boost::filesystem Boost::system)

# Link Protobuf library
target_link_libraries(cdb PRIVATE ${Protobuf_LIBRARIES} absl::log_internal_message absl::log_internal_check_op)
