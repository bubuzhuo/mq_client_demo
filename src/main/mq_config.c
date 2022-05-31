/**
 * @file msg_config.c
 * @author your name (you@domain.com)
 * @brief
 * @version 0.1
 * @date 2022-05-09
 *
 * @copyright Copyright (c) 2022
 *
 */

#include "main.h"

/**
 * @brief Get the Conf Msg object
 *
 * @param data
 * @return uint8_t
 */
static uint8_t getConf_Msg(cJSON *data)
{

	cJSON *hostName = NULL;

	if (data->type != cJSON_Object)
	{
		log_printf(MSG_ERROR, "getConf_Msg: cJSON_Object is wrong!\n");
		return FALSE;
	}

	hostName = cJSON_GetObjectItem(data, "hostName");
	if (hostName != NULL)
	{
		if (hostName->type != cJSON_String)
		{
			log_printf(MSG_ERROR, " getConf_Msg: (hostName.type!= cJSON_String)\n");
			return FALSE;
		}
	}
	else
	{
		log_printf(MSG_ERROR, " getConf_Msg: (hostName==NULL)\n");
		return FALSE;
	}
	strcpy(mqMessageConfig->hostName, hostName->valuestring);

	return TRUE;
}

/**
 * @brief config_get_MQ
 *
 * @return uint8_t
 */
uint8_t config_get_MQ(void)
{
	/**
	 * @brief DEV MESSAGE config param getting.
	 *
	 */
	char *conf_buffer = FILE_getFromDir(CONFIG_MQ_MSG_DIR, JSON_BUFFER_LEN);
	if (NULL == conf_buffer)
	{
		log_printf(MSG_ERROR, "config_get_MQ: FILE_getFromDir error!\n");
		return FALSE;
	}

	cJSON *config = string2Json((uint8_t *)conf_buffer);
	if (NULL == config)
	{
		log_printf(MSG_ERROR, "config_get_MQ: string2Json error!\n");
		return FALSE;
	}

	free(conf_buffer);
	conf_buffer = NULL;

	if (!getConf_Msg(config))
	{
		log_printf(MSG_ERROR, "config_get_MQ: getConf_Msg error!\n");
		return FALSE;
	}

	return TRUE;
}
