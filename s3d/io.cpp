#include "io.h"

#include <iostream>
#include <fstream>
#include <string>
#include <cstring>

bool IO_readStringFromFile(const char * path, char * buffer,
                           size_t size) {
    if(path == NULL) {
        std::cerr << __FUNCTION__ << ": file path is not defined\n";
        return false;
    }
    if(buffer == NULL) {
        std::cerr << __FUNCTION__ << ": buffer is NULL\n";
        return false;
    }

    std::ifstream file(path, std::ios::in);
    if(file.fail()) {
        std::cerr << __FUNCTION__ << ": " << std::strerror(errno) << std::endl;
        return false;
    }
    unsigned int i = 0;
    std::string line;
    while (std::getline(file, line)) {
        for(char c : line) {
            if(i >= size) {
                std::cerr << __FUNCTION__ << ": buffer overflow\n";
                return false;
            }
            *(buffer + i++) = c;
        }
        if(i >= size) {
            std::cerr << __FUNCTION__ << ": buffer overflow\n";
            return false;
        }
        *(buffer + i++) = '\n';
    }
    file.close();

    if(i >= size) {
        std::cerr << __FUNCTION__ << ": buffer overflow\n";
        return false;
    }
    *(buffer + i++) = 0;

    return true;
}

bool IO_writeStringToFile(const char * path, const char * str) {
    if(path == NULL) {
        std::cerr << __FUNCTION__ << ": file path is not defined\n";
        return false;
    }
    if(str == NULL) {
        std::cerr << __FUNCTION__ << ": string is NULL\n";
        return false;
    }

    std::ofstream file(path, std::ios::out | std::ios::trunc);
    if(file.fail()) {
        std::cerr << __FUNCTION__ << ": " << std::strerror(errno) << std::endl;
        return false;
    }
    file << str;
    file.close();

    return true;
}

bool IO_appendStringToFile(const char * path, const char * str) {
    if(path == NULL) {
        std::cerr << __FUNCTION__ << ": file path is not defined\n";
        return false;
    }
    if(str == NULL) {
        std::cerr << __FUNCTION__ << ": string is NULL\n";
        return false;
    }

    std::ofstream file(path, std::ios::out | std::ios::app);
    if(file.fail()) {
        std::cerr << __FUNCTION__ << ": " << std::strerror(errno) << std::endl;
        return false;
    }
    file << str;
    file.close();

    return true;
}

bool IO_readDataFromFile(const char * path, char * buffer, size_t buffer_size) {
    if(path == NULL) {
        std::cerr << __FUNCTION__ << ": file path is not defined\n";
        return false;
    }
    if(buffer == NULL) {
        std::cerr << __FUNCTION__ << ": buffer is NULL\n";
        return false;
    }

    std::ifstream file(path, std::ios::in | std::ios::binary);
    if(file.fail()) {
        std::cerr << __FUNCTION__ << ": " << std::strerror(errno) << std::endl;
        return false;
    }
    file.read(buffer, buffer_size);
    file.close();

    return true;
}

bool IO_writeDataToFile(const char * path, const char * data, size_t data_size) {
    if(path == NULL) {
        std::cerr << __FUNCTION__ << ": file path is not defined\n";
        return false;
    }
    if(data == NULL) {
        std::cerr << __FUNCTION__ << ": data is NULL\n";
        return false;
    }

    std::ofstream file(path, std::ios::out | std::ios::binary);
    if(file.fail()) {
        std::cerr << __FUNCTION__ << ": " << std::strerror(errno) << std::endl;
        return false;
    }
    file.write(data, sizeof(char) * data_size);
    file.close();

    return true;
}

bool IO_logError(const char * str) {
    if(str == NULL) {
        std::cerr << __FUNCTION__ << ": string is NULL\n";
        return false;
    }

    std::ofstream file(DEFAULT_LOG_ERR_FILE, std::ios::out | std::ios::app);
    if(file.fail()) {
        std::cerr << __FUNCTION__ << ": " << std::strerror(errno) << std::endl;
        return false;
    }
    file << str << std::endl;
    file.close();

    return true;
}