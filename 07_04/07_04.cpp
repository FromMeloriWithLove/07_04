#include <iostream>
#include <string>
#include <fstream>

using namespace std;

class FileWorker {
    FileWorker() {}
    FileWorker(const FileWorker&) = delete;
    FileWorker& operator=(const FileWorker&) = delete;
public:
    static FileWorker& getInstance() {
        static FileWorker instance;
        return instance;
    }

    bool createFile(const string& filePath) const {
        ofstream file(filePath);
        if (file.is_open()) {
            file.close();
            return true;
        }
        return false;
    }

    bool renameFile(const string& oldPath, const string& newPath) const {
        if (rename(oldPath.c_str(), newPath.c_str()) == 0) {
            return true;
        }
        return false;
    }

    bool deleteFile(const string& filePath) const {
        if (std::remove(filePath.c_str()) == 0) {
            return true;
        }
        return false;
    }

    bool fileExists(const string& filePath) const {
        ifstream file(filePath);
        return file.good();
    }
};

int main() {
    FileWorker& fileWorker = FileWorker::getInstance();
    string filePath = "example.txt";
    if (fileWorker.createFile(filePath)) {
        cout << "File created\n";
        if (fileWorker.fileExists(filePath)) {
            cout << "File is working\n";
            string newFilePath = "new_example.txt";
            if (fileWorker.renameFile(filePath, newFilePath)) {
                cout << "File renamed\n";
                if (fileWorker.deleteFile(newFilePath)) {
                    cout << "File deleted\n";
                }
                return 0;
            }

        }
    }
}