/**
 * @file device_init.h
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2022-05-11
 * 
 * @copyright Copyright (c) 2022
 * 
 */


/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __DEVICE_INIT_H
#define __DEVICE_INIT_H

#include <stdint.h>
#include "mq_client.h"



extern mqMessageTypeDef *mqMessageConfig;

/**
 * @brief device_init
 * 
 * @return uint8_t 
 */
extern uint8_t device_init(void);



/**
 * @brief device_destroy
 * 
 */
extern void device_destroy(void);



#endif /* __DEVICE_INIT_H */


