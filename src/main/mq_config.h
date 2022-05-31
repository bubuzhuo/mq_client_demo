/**
 * @file msg_config.h
 * @author your name (you@domain.com)
 * @brief
 * @version 0.1
 * @date 2022-05-09
 *
 * @copyright Copyright (c) 2022
 *
 */


/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MQ_CONFIG_H
#define __MQ_CONFIG_H

#include <stdint.h>


#define CONFIG_MQ_MSG_DIR "./CONFIG_MQ.json"
 




/**
 * @brief config_get_MQ
 *
 * @return uint8_t
 */
extern uint8_t config_get_MQ(void);


#endif /* __MQ_CONFIG_H */
