# CPP WASM APP
Important Files:
- `proposal.md`: App proposal.
## Current Status
This project is currently in progress. 
The goal for the first checkpoint is to create a basic WASM application that can
- Allow Users to Upload Files
- Translate the File into an Apache Arrow DataFrame
- Perform a basic transformation on the DataFrame
- Write the DataFrame to a File for the User to save.

That is all!

## Handy Tops for Using WASM
- Test C++ Code: `g++ filename.cpp`
- Test your app: `emcc main.cpp -o test.html --emrun -sFORCE_FILESYSTEM`
- Run your app: `emrun test.html`
- `emcc file_functions.cpp -o file_functions_wasm.js -sEXPORTED_RUNTIME_METHODS=[ccall] --emrun --bind `
- `emrun index.html --no_emrun_detect`


