#pragma once

#include <chrono>
#include <unordered_map>

#include <grpc++/grpc++.h>

#include "../fib.grpc.pb.h"
#include "../fib.pb.h"
#include "Fibonacci.hpp"

using grpc::ServerContext;
using grpc::Status;

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

private:
  std::unordered_map<uint64_t, uint64_t> cache;
  std::unordered_map<uint64_t, uint64_t> counter;
};
