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
 * @brief Set the up connection and channel object
 *
 * @param host_mq
 * @param fixed_channel_id
 * @param admin_mq
 * @param password_mq
 * @return amqp_connection_state_t
 */
extern amqp_connection_state_t setup_connection_and_channel(const char *host_mq,
															uint16_t fixed_channel_id,
															const char *admin_mq,
															const char *password_mq);

#endif /* __MQ_CLIENT */
