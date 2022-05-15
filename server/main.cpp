#include <chrono>
#include <iostream>
#include <memory>
#include <string>
#include <unordered_map>

#include <grpcpp/grpcpp.h>

#include "../fib.grpc.pb.h"
#include "../fib.pb.h"
#include "Fibonacci.hpp"

using grpc::Server;
using grpc::ServerBuilder;
using grpc::ServerContext;
using grpc::Status;

std::unordered_map<uint64_t, uint64_t> cache;
std::unordered_map<uint64_t, uint64_t> counter;

class FibServiceImpl final : public Fib::Service {
  Status get(ServerContext *context, const Request *request,
             Response *reply) override {
    auto value{request->val()};
    if (value > 93) { // 64 bit unsigned int max
      return Status::CANCELLED;
    }
    Fibonacci fibonacci;

    if (cache.find(value) == cache.end()) {
      cache[value] = fibonacci.getNumber(value);
    }
    reply->set_fib(cache[value]);
    reply->set_timestamp(
        std::chrono::duration_cast<std::chrono::seconds>(
            std::chrono::system_clock::now().time_since_epoch())
            .count());
    reply->set_count(++counter[value]);
    return Status::OK;
  }
};

void RunServer() {
  std::string server_address("0.0.0.0:50051");
  FibServiceImpl service{};

  ServerBuilder builder;
  builder.AddListeningPort(server_address, grpc::InsecureServerCredentials());
  builder.RegisterService(&service);
  std::unique_ptr<Server> server(builder.BuildAndStart());
  std::cout << "Server listening on " << server_address << std::endl;
  server->Wait();
}

int main(int argc, char **argv) {
  RunServer();
  return 0;
}
