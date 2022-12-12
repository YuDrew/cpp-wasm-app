check-emscripten: 
	@emcc --version || (echo "Emscripten not found, setting up emscripten";
	cd ~/Dev/sdk/emsdk &&
	./emsdk install latest &&
	./emsdk activate latest &&
	source ./emsdk_env.sh)

build: check-emscripten
	@echo "Building"
	cd ~/Dev/cpp-wasm-app &&
	emcc -Wall -std=c++20 -g main.cpp -o app.html

local: 
	@echo "Running locally"
	g++-12 -Wall -std=c++20 -g main.cpp -o app
	./app