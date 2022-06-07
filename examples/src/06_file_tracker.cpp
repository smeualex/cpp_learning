#include "headers.h"

#include <cstdio>
#include <cstdlib>

using FileCloser = std::function<void(std::FILE*)>;
using FilePtr =  std::unique_ptr<FILE, FileCloser>;

struct FileTracker {
    static int NumOpenFiles;

    static void close(std::FILE* fp) {
        if(fp) {
            cout << " > Closing file" << endl;
            NumOpenFiles--;
            std::fclose(fp);
        }
    }

    static auto open(const char* filename, const char* mode) {
        
        cout << " > Opening file: " << filename << "; mode: " << mode << endl;
        // Create unique_ptr of FILE*. Try to open the file!
        auto f = std::unique_ptr<std::FILE, FileCloser>(std::fopen(filename, mode), &FileTracker::close);

        // if not NULL -> the file is open
        if(f) {
            NumOpenFiles++;
        }

        return f;
    }
};

int FileTracker::NumOpenFiles = 0;


void test_openFiles() {
     
    {   //Block
        auto fh = FileTracker::open("test.txt", "w");
        if(fh) {
            std::fputs("Hello World!", fh.get());
        }   
        std::cout << "Opened files: " << FileTracker::NumOpenFiles << "\n"; //1
    }   //End Block. File Closed.

    std::cout << "Opened files: " << FileTracker::NumOpenFiles << "\n"; //0

    std::cout << "Opening 10 files with the variable in the loop. We should see them being close each time the loop advances" << endl;

    for(int i = 1; i <= 10; i++) {
        std::string fileName = "test_" + std::to_string(i) + ".txt"; 
        FilePtr tmp = FileTracker::open(fileName.c_str(), "w");
        std::cout << "Opened files: " << FileTracker::NumOpenFiles << "\n";
        if(tmp) {
            std::fputs("Ana are mere:) ", tmp.get());
        }
    }


    std::cout << "Opened files: " << FileTracker::NumOpenFiles << "\n";
}

// our main stuff go here :)
void do_stuff() {
    test_openFiles();
}

int main(int argc, char** argv) {
    cout << "---------------------------------------------------------" << endl;
    cout << "start" << endl;

    do_stuff();

    cout << "end" << endl;
    cout << "---------------------------------------------------------" << endl;
    return 0;
}