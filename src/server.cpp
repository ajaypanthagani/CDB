// #include <grpcpp/grpcpp.h>

// #include "src/proto/dbms.grpc.pb.h"
// #include "src/proto/dbms.pb.h"

// using grpc::Server;
// using grpc::ServerBuilder;
// using grpc::ServerContext;
// using grpc::Status;
// using dbms::DeleteRequest;
// using dbms::DeleteResponse;

// class CDBImpl final : dbms::CDB::Service {
//     Status Delete(ServerContext* context, const DeleteRequest* deleteRequest, DeleteResponse* deleteResponse) override {
//         return Status::OK;
//     }
// };

// void RunServer() {
//   std::string server_address("0.0.0.0:50051");
//   CDBImpl service;

//   ServerBuilder builder;
//   builder.AddListeningPort(server_address, grpc::InsecureServerCredentials());
//   builder.RegisterService(&service);
//   std::unique_ptr<Server> server(builder.BuildAndStart());
//   std::cout << "Server listening on " << server_address << std::endl;

//   server->Wait();
// }
