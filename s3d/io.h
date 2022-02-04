/***************************************************************************
 *
 *  File:       io.h
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

#ifndef IO_H
#define IO_H

#include "api.h"

#include <stdbool.h>
#include <stdlib.h>
#include <string>
#include <vector>


#define DEFAULT_LOG_ERR_FILE "error.txt"

/**
 * @brief IO_readStringFromFile
 * @param path
 * @param buffer
 * @param size
 * @return
 */
bool S3D_EXPORT IO_readStringFromFile(const char * path, std::vector<std::string> & lines);

/**
 * @brief IO_writeStringToFile
 * @param path
 * @param buffer
 * @return
 */
bool S3D_EXPORT IO_writeStringToFile(const char * path, const char * str);

/**
 * @brief IO_appendStringToFile
 * @param path
 * @param buffer
 * @return
 */
bool S3D_EXPORT IO_appendStringToFile(const char * path, const char * str);

/**
 * @brief IO_readDataFromFile
 * @param path
 * @param data
 * @param buffer_size
 * @return
 */
bool S3D_EXPORT IO_readDataFromFile(const char * path, char * data, size_t buffer_size);

/**
 * @brief IO_writeDataToFile
 * @param path
 * @param data
 * @param buffer_size
 * @return
 */
bool S3D_EXPORT IO_writeDataToFile(const char * path, const char * data, size_t data_size);

/**
 * @brief IO_writeDataToFile
 * @param path
 * @param data
 * @return
 */
bool S3D_EXPORT IO_logError(const char * str);


#endif // IO_H
