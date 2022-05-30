/**
 * @file unit.h
 * @author your name (you@domain.com)
 * @brief
 * @version 0.1
 * @date 2022-03-08
 *
 * @copyright Copyright (c) 2022
 *
 */





/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __UNIT_H
#define __UNIT_H



#include <stdint.h>
#include "cJSON.h"





/**
 * @brief Get the token object
 *
 * @param token
 */



extern void get_token(char *token);
extern uint8_t is_app_running(void);
extern void set_app_running(uint8_t running);
extern void delay_ms(unsigned long mSec);
extern void mqtt_get_time(char *psDateTime);
extern int AtoH(char *str, uint8_t *out);
extern uint8_t itobcd(uint8_t data);
extern cJSON *string2Json(const uint8_t *str);



#endif /* __UNIT_H */
