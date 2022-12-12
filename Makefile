check-emscripten: 
	@emcc --version || (echo "Emscripten not found, aborting build"; exit 1)

build: check-emscripten
	@echo "Building"
	emcc -Wall -std=c++20 -g main.cpp -o app.html

run-local: 
	@echo "Running locally"
	g++-12 -Wall -std=c++20 -g main.cpp -o app
	./app