#include <iostream>
#include <cstring>
#include <utility>
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

    explicit FileException(string error) : error(std::move(error)) {}

    const char *what() const noexcept { return error.c_str(); } // C++11 and higher
private:
    string error;
};

template<class T>
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
            cout<<"~File()"<<endl;
        }
    }

    void write(T *buffer, size_t size) {
        if (accessMode == READ) {
            throw FileException("File exception: File opened read only");
        }
        fseek(file, 0, SEEK_END);
        fwrite(buffer, sizeof(T), size, file);
    }

    size_t read(T *buffer, size_t size, long offset = 0) {
        if (accessMode == WRITE) {
            throw FileException("File exception: File opened write only");
        }
        if (fseek(file, offset, SEEK_SET) != 0) {
            throw FileException("File exception: File seek error");
        }
        return fread(buffer, sizeof(T), size, file);
    }

private:
    FILE *file;
    AccessMode accessMode;
};

int main() {
    char *buffer = new char[10];
    //test 1
    {
        try {
            File<char> file("D:\\1C\\buffer.txt", WRITE);
            string writeBuffer = "write_test";
            file.write(const_cast<char *>(writeBuffer.c_str()), writeBuffer.length());
            file.read(buffer, 10, 0);
        }
        catch (FileException e) {
            cout << e.what() << endl;
        }
    }
    //test 2
    {
        try {
            File<char> file("D:\\1C\\buffer.txt", READ);
            file.write(buffer, 10);
            int count = file.read(buffer, 10, 0);
            if (count > 0) {
                cout << buffer << endl;
            }
        }
        catch (FileException e) {
            cout << e.what() << endl;
        }
    }
    {
        try {
            File<char> file("D:\\1C\\buffer.txt", READ_WRITE);
            int count = file.read(buffer, 11, 0);
            if (count > 0) {
                cout << buffer << endl;
            }
            string writeBuffer = "read_write_test";
            file.write(const_cast<char *>(writeBuffer.c_str()), writeBuffer.length());
        }
        catch (FileException e) {
            cout << e.what() << endl;
        }
    }
    delete[] buffer;
    return 0;
}
