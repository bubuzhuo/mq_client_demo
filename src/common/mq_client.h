/**
 * @file mq_client.h
 * @author your name (you@domain.com)
 * @brief
 * @version 0.1
 * @date 2022-05-30
 *
 * @copyright Copyright (c) 2022
 *
 */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MQ_CLIENT
#define __MQ_CLIENT

#include <stdint.h>
/* mq lib inlcude ----------------------------------------------------------*/
#include "rabbitmq-c/amqp.h"
#include "rabbitmq-c/tcp_socket.h"

/**
 * @brief mqStateENUM
 *
 */
enum mqStateENUM
{
	MQ_CLIENT_CLOSE,
	MQ_CLIENT_CREATE,
	MQ_CLIENT_RUN,
	MQ_CLIENT_DESTROY

} MQ_CLIENT_STATE;

/**
 * @brief mqMessageTypeDef
 *
 */
typedef struct
{

	char *hostName;
	uint16_t channel_id;
	char *admin;
	char *password;

} mqMessageTypeDef;





/**
 * @brief mqCilent_init
 *
 * @return uint8_t
 */
extern mqMessageTypeDef *mqCilent_init(void);

/**
 * @brief mqCilent_destroy
 * 
 * @param p mqMessageTypeDef object.
 */
extern void mqCilent_destroy(mqMessageTypeDef *p);

#endif /* __MQ_CLIENT */
