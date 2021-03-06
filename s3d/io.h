/******************************************************************************
 * S3D Engine
 *
 * @file       io.h
 * @brief      XXXX Function
 *
 * @author     Martin Krcma
 * @date       2021/07/20
 *****************************************************************************/

#ifndef IO_H
#define IO_H

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
bool IO_readStringFromFile(const char * path, std::vector<std::string> & lines);

/**
 * @brief IO_writeStringToFile
 * @param path
 * @param buffer
 * @return
 */
bool IO_writeStringToFile(const char * path, const char * str);

/**
 * @brief IO_appendStringToFile
 * @param path
 * @param buffer
 * @return
 */
bool IO_appendStringToFile(const char * path, const char * str);

/**
 * @brief IO_readDataFromFile
 * @param path
 * @param data
 * @param buffer_size
 * @return
 */
bool IO_readDataFromFile(const char * path, char * data, size_t buffer_size);

/**
 * @brief IO_writeDataToFile
 * @param path
 * @param data
 * @param buffer_size
 * @return
 */
bool IO_writeDataToFile(const char * path, const char * data, size_t data_size);

/**
 * @brief IO_writeDataToFile
 * @param path
 * @param data
 * @return
 */
bool IO_logError(const char * str);


#endif // IO_H
