/**
 * @file mq_client.c
 * @author your name (you@domain.com)
 * @brief
 * @version 0.1
 * @date 2022-05-30
 *
 * @copyright Copyright (c) 2022
 *
 */

#include "main.h"

/**
 * @brief Set the up connection and channel object
 *
 * @param host_mq
 * @param fixed_channel_id
 * @param admin_mq
 * @param password_mq
 * @return amqp_connection_state_t
 */
amqp_connection_state_t setup_connection_and_channel(const char *host_mq,
													 uint16_t fixed_channel_id,
													 const char *admin_mq,
													 const char *password_mq)
{
	amqp_connection_state_t connection_state_ = amqp_new_connection();

	amqp_socket_t *socket = amqp_tcp_socket_new(connection_state_);
	if (socket == NULL)
	{
		log_printf(MSG_ERROR, "setup_connection_and_channel: (socket==NULL)\n");
		return NULL;
	}

	int rc = amqp_socket_open(socket, host_mq, AMQP_PROTOCOL_PORT);
	if (rc != AMQP_STATUS_OK)
	{
		log_printf(MSG_ERROR, "amqp_socket_open error [code: %d]\n", rc);
		return NULL;
	}

	amqp_rpc_reply_t rpc_reply = amqp_login(connection_state_, "/", 1, AMQP_DEFAULT_FRAME_SIZE,
											AMQP_DEFAULT_HEARTBEAT, AMQP_SASL_METHOD_PLAIN, admin_mq, password_mq);
	if (rpc_reply.reply_type != AMQP_RESPONSE_NORMAL)
	{
		log_printf(MSG_ERROR, "amqp_login error [code: %d]\n", rpc_reply.reply_type);
		return NULL;
	}

	amqp_channel_open_ok_t *res = amqp_channel_open(connection_state_, fixed_channel_id);
	if (res == NULL)
	{
		log_printf(MSG_ERROR, "amqp_channel_open error \n");
		return NULL;
	}

	return connection_state_;
}


