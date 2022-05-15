git clone --recursive https://github.com/grpc/grpc

mkdir build_dir
cd build_dir

cmake .. -DCMAKE_BUILD_TYPE=Release  -D_gRPC_CARES_LIBRARIES=cares
cmake --build .  --config Release

cd ..

