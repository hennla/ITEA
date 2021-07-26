#include <iostream>
#include <cstring>
#include <stdio.h>

using namespace std;

enum AccessMode {
    READ,
    WRITE,
    READ_WRITE
};

class FileException : public exception {
public:
    FileException() {
        this->error.append("File exception: ");
        this->error.append(strerror(errno));
    }

    FileException(string error) : error(error){}

    const char *what() const noexcept { return error.c_str(); } // C++11 and higher
private:
    string error;
};

class File {
public:
    File(string fileName, AccessMode accessMode) : accessMode(accessMode) {
        string mode;
        if (accessMode == READ) {
            mode = "r";
        } else if (accessMode == WRITE) {
            mode = "w";
        } else if (accessMode == READ_WRITE) {
            mode = "r+w";
        } else {
            throw invalid_argument("invalid access mode");
        }
        file = fopen(fileName.c_str(), mode.c_str());
        if (file == nullptr) {
            throw FileException();
        }
        fseek(file, 0, SEEK_SET);
    }

    ~File() {
        if (file != nullptr) {
            fflush(file);
            fclose(file);
        }
    }

    void write(char *buffer, size_t size, long position = 0) {
        if (accessMode == READ) {
            throw FileException("File exception: File opened read only");
        }
        fseek(file, position, SEEK_SET);
        fwrite(buffer, sizeof(char), size, file);
    }

    size_t read(char *buffer, size_t size, long position = 0) {
        if (accessMode == WRITE) {
            throw FileException("File exception: File opened write only");
        }
        fseek(file, position, SEEK_SET);
        return fread(buffer, sizeof(char), size, file);
    }

private:
    FILE *file;
    AccessMode accessMode;
};

int main() {
    char * buffer = new char [10];
    try {
        File file("D:\\1C\\buffer.txt", READ_WRITE);
        file.read(buffer, 10);
        cout<<buffer<<endl;
        string writeBuffer = "write_test";
        file.write(const_cast<char *>(writeBuffer.c_str()), writeBuffer.length(), 0);
        file.read(buffer, 10, 0);
        cout<<buffer<<endl;
    }
    catch (FileException e) {
        cout << e.what() << endl;
    }
    delete buffer;
    return 0;
}
