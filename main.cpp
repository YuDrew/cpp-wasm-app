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

int main()
{
    EM_ASM(
        var file_selector = document.createElement('input');
        file_selector.setAttribute('type', 'file');
        file_selector.setAttribute('onchange','open_file(event)');
        file_selector.setAttribute('accept','.png,.jpeg'); // optional - limit accepted file types 
        file_selector.click();
    );

    return 0;
}

// create a function that takes in a user uploaded file and returns the file name

string getFileName(string fileName)
{
    return fileName;
}

// create a function that takes in a user uploaded file and returns the file size

int getFileSize(string fileName)
{
    return 0;
}

// create a function that opens "uploads/deals.csv" and prints the first 5 lines

void printFirstFiveLines(string fileName)
{
    return;
}