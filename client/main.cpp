
#include "../fib.grpc.pb.h"
#include "../types.hpp"
#include <grpc++/grpc++.h>
#include <iostream>
#include <memory>
#include <optional>
#include <string>

using grpc::Channel;
using grpc::ClientContext;
using grpc::Status;

class Client {
public:
  Client(std::shared_ptr<Channel> channel) : stub_(Fib::NewStub(channel)) {}
  // Assambles the client's payload, sends it and presents the response back
  // from the server.
  std::optional<ServiceResponse> getFibonacciNumber(uint64_t val) {
    // Data we are sending to the server.
    Request request;
    request.set_val(val);
    // Container for the data we expect from the server.
    Response reply;
    // Context for the client. It could be used to convey extra information to
    // the server and/or tweak certain RPC behaviors.
    ClientContext context;
    // The actual RPC.
    Status status = stub_->get(&context, request, &reply);
    // Act upon its status.
    if (status.ok()) {
      ServiceResponse response{reply.fib(), reply.timestamp(), reply.count()};
      return std::optional<ServiceResponse>(response);
    } else {
      std::cout << status.error_code() << ": " << status.error_message()
                << std::endl;
      return std::nullopt;
    }
  }

private:
  std::unique_ptr<Fib::Stub> stub_;
};

int main(int argc, char **argv) {
  if (argc == 1) {
    std::cout << "Usage: " << argv[0] << " <value>" << std::endl;
    return 0;
  }
  Client client(grpc::CreateChannel("localhost:50051",
                                    grpc::InsecureChannelCredentials()));
  uint64_t value{(uint64_t)std::atoi(argv[1])};
  auto reply = client.getFibonacciNumber(value);

  if (!reply) {
    std::cout << "Error occured. Check input value" << std::endl;
    return 0;
  }

  std::cout << "{\"fib\"=" << reply->fib
            << ", \"timestamp\"=" << reply->timestamp
            << ", \"count\"=" << reply->count << "}" << std::endl;

  return 0;
}