git clone --recursive https://github.com/grpc/grpc
cd grpc
git checkout de613e3a9eccee556a512d1deeb556a69f0fc04b
cd ..

mkdir build_dir
cd build_dir

cmake .. -DCMAKE_BUILD_TYPE=Release -D_gRPC_CARES_LIBRARIES=cares
cmake --build .  -j10 --config Release

cd ..

