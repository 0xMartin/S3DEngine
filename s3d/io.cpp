/***************************************************************************
 *
 *  File:       io.cpp
 *  Date:       20.07.2021
 *
 *  Github:     https://github.com/0xMartin
 *  Email:      martin.krcma1@gmail.com
 *
 *  Copyright (C) 2022 Martin Krcma
 *
 *  Permission is hereby granted, free of charge, to any person
 *  obtaining a copy of this software and associated documentation
 *  files (the "Software"), to deal in the Software without
 *  restriction, including without limitation the rights to use,
 *  copy, modify, merge, publish, distribute, sublicense, and/or sell
 *  copies of the Software, and to permit persons to whom the
 *  Software is furnished to do so, subject to the following
 *  conditions:
 *
 *  The above copyright notice and this permission notice shall be
 *  included in all copies or substantial portions of the Software.
 *
 *  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 *  EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
 *  OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 *  NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
 *  HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
 *  WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 *  FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 *  OTHER DEALINGS IN THE SOFTWARE.
 *
 ***************************************************************************/

#include "io.h"

#include <iostream>
#include <fstream>
#include <cstring>

bool IO_readStringFromFile(const char * path, std::vector<std::string> & lines) {
    if(path == NULL) {
        std::cerr << __FUNCTION__ << ": file path is not defined\n";
        return false;
    }

    std::ifstream file(path, std::ios::in);
    if(file.fail()) {
        std::cerr << __FUNCTION__ << ": " << std::strerror(errno) << std::endl;
        return false;
    }
    std::string line;
    while (std::getline(file, line)) {
        lines.push_back(line);
    }
    file.close();

    return true;
}

bool IO_writeStringToFile(const char * path, const char * str) {
    if(path == NULL) {
        std::cerr << __FUNCTION__ << ": file path is not defined\n";
        return false;
    }
    if(str == NULL) {
        std::cerr << __FUNCTION__ << ": string is NULL [" << path << "]\n";
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
        std::cerr << __FUNCTION__ << ": string is NULL [" << path << "]\n";
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
        std::cerr << __FUNCTION__ << ": buffer is NULL [" << path << "]\n";
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
        std::cerr << __FUNCTION__ << ": data is NULL [" << path << "]\n";
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
