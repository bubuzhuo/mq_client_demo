/**
 * @file fileCtr.h
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2022-04-26
 * 
 * @copyright Copyright (c) 2022
 * 
 */


/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __FILECTR_H
#define __FILECTR_H



#include <stdint.h>



/**
 * @brief Get the Config object
 *
 * @param filedir
 * @return char* 使用完后需要对内存进行释放
 */
extern char *FILE_getFromDir(const char *filedir, uint32_t fileSize);



#endif /* __FILECTR_H  */


