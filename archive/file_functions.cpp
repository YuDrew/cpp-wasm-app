#include <emscripten.h>
#include <emscripten/bind.h>
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

extern "C" {
    EMSCRIPTEN_KEEPALIVE int load_file(uint8_t *buffer, size_t size) {
        // Load a file - this functionn is called from javascript when the file upload is activated
        std::cout << "load_file triggered, buffer " << &buffer << " size" << size << std::endl;

        // do whatever you need with the file contents

        return 1;
    }
}

string changeFileName(string fileName)
{
    return fileName + "_changed.csv";
}

int getNumLines(string fileName)
{
    ifstream myfile;
    myfile.open(fileName);
    string line;
    int i = 0;
    while (getline(myfile, line))
    {
        i++;
    }
    return i;
}

EMSCRIPTEN_BINDINGS(file_functions) {
    emscripten::function("changeFileName", &changeFileName);
    emscripten::function("getNumLines", &getNumLines);
}

EM_ASM(
  var file_selector = document.createElement('input');
  file_selector.setAttribute('type', 'file');
  file_selector.setAttribute('onchange','open_file(event)');
  file_selector.setAttribute('accept','.png,.jpeg'); // optional - limit accepted file types 
  file_selector.click();
);