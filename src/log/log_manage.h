/**
  ******************************************************************************
  * @author  Lanceli
  * @version V1.0.0
  * @date    30-Aug-2021
  * @brief   the program log process
  * @attention
  * Copyright (c) 2021 Lanceli All rights reserved.
  ******************************************************************************
  */

 /* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __LOG_MANAGE_H
#define __LOG_MANAGE_H

#include <stdint.h>



typedef enum
{
  MSG_VERBOSE,
  MSG_INFO,
  MSG_DEBUG,
  MSG_WARNING,
  MSG_ERROR

} logLevelEnum;



extern uint8_t log_set_level(logLevelEnum level);
extern void log_printf(logLevelEnum level, const char *fmt, ...);
extern uint8_t log_manageInit(uint8_t enable);
extern void log_closeFile(void);


#endif /* __LOG_MANAGE_H */
