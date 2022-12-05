check-emscripten: 
	@emcc --version || (echo "Emscripten not found, aborting build"; exit 1)

build: check-emscripten
