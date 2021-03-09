/**
 * <------------------------------------------------------------------>
 * @name    2D Engine
 * @author  Martin Krcma
 * @date    28. 2. 2021
 * <------------------------------------------------------------------>
 * @file    io.h
 * @brief
 * <------------------------------------------------------------------>
 */

#ifndef IO_H
#define IO_H

#include <stdbool.h>

#define DEFAULT_LOG_ERR_FILE "error.txt"

/**
 * @brief readStringFromFile
 * @param path
 * @param buffer
 * @param size
 * @return
 */
bool readStringFromFile(const char * const path, char * buffer, unsigned int size);

/**
 * @brief writeStringToFile
 * @param path
 * @param buffer
 * @return
 */
bool writeStringToFile(const char * const path, char * buffer);

/**
 * @brief appendStringToFile
 * @param path
 * @param buffer
 * @return
 */
bool appendStringToFile(const char * const path, char * buffer);

/**
 * @brief readDataFromFile
 * @param path
 * @param data
 * @return
 */
bool readDataFromFile(const char * const path, void * data);

/**
 * @brief writeDataToFile
 * @param path
 * @param data
 * @return
 */
bool writeDataToFile(const char * const path, void * data);

/**
 * @brief writeDataToFile
 * @param path
 * @param data
 * @return
 */
bool logError(const char * const str);


#endif // IO_H
