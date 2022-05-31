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
 * @brief amqp_connection_state_t
 *
 */
amqp_connection_state_t amqpConectClient;


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
		log_printf(MSG_ERROR, "amqp_channel_open error.\n");
		return NULL;
	}

	return connection_state_;
}



/**
 * @brief close_and_destroy_connection.
 *
 * @param connection_state_
 */
void close_and_destroy_connection(amqp_connection_state_t connection_state_)
{
	amqp_rpc_reply_t rpc_reply = amqp_connection_close(connection_state_, AMQP_REPLY_SUCCESS);
	assert(rpc_reply.reply_type == AMQP_RESPONSE_NORMAL);

	int rc = amqp_destroy_connection(connection_state_);
	assert(rc == AMQP_STATUS_OK);
}

/**
 * @brief mqClient_process
 *
 * @param arg
 * @return void*
 */
static void *mqClient_process(void *arg)
{
	mqMessageTypeDef *mqMessage = (mqMessageTypeDef *)arg;
	MQ_CLIENT_STATE = MQ_CLIENT_CLOSE;

	while (is_app_running())
	{
		switch (MQ_CLIENT_STATE)
		{
		case MQ_CLIENT_CLOSE:
			MQ_CLIENT_STATE = MQ_CLIENT_CREATE;
			log_printf(MSG_DEBUG, "mqClient_process: MQ_CLIENT_CLOSE -> MQ_CLIENT_CREATE\n");
			break;

		case MQ_CLIENT_CREATE:
			amqpConectClient = setup_connection_and_channel(mqMessage->hostName, mqMessage->channel_id,
															mqMessage->admin, mqMessage->password);
			if (amqpConectClient == NULL)
			{
				log_printf(MSG_ERROR, "mqClient_process: setup_connection_and_channel error!\n");
				MQ_CLIENT_STATE = MQ_CLIENT_DESTROY;
				log_printf(MSG_DEBUG, "mqClient_process: MQ_CLIENT_CREATE -> MQ_CLIENT_DESTROY\n");
			}
			else
			{
				MQ_CLIENT_STATE = MQ_CLIENT_RUN;
				log_printf(MSG_DEBUG, "mqClient_process: MQ_CLIENT_CREATE -> MQ_CLIENT_RUN\n");
			}
			break;

		case MQ_CLIENT_RUN:
			break;

		case MQ_CLIENT_DESTROY:
			break;

		default:
			log_printf(MSG_ERROR, "mqClient_process: switch error!\n");
			break;
		}
		delay_ms(500);
	}

	return NULL;
}











/**
 * @brief mqCilent_init
 *
 * @return uint8_t
 */
mqMessageTypeDef *mqCilent_init(void)
{
	pthread_t tid_mqClient;
	mqMessageTypeDef *mqMessage = (mqMessageTypeDef *)malloc(sizeof(mqMessageTypeDef));

	mqMessage->hostName = (char *)malloc(128);
	mqMessage->admin = (char *)malloc(128);
	mqMessage->password = (char *)malloc(128);
	mqMessage->channel_id = 0;

	if (pthread_create(&tid_mqClient, NULL, mqClient_process, (void *)mqMessage) < 0)
	{
		log_printf(MSG_ERROR, "mqCilent_init create error!\n");
		return FALSE;
	}

	return mqMessage;
}

/**
 * @brief mqCilent_destroy
 * 
 * @param p mqMessageTypeDef object.
 */
void mqCilent_destroy(mqMessageTypeDef *p)
{
	log_printf(MSG_WARNING, "mqCilent_destroy: [MSG_WARNING] mqCilent_destroy exit!\n");

	close_and_destroy_connection(amqpConectClient);

	free(p->hostName);
	free(p->admin);
	free(p->password);
}
