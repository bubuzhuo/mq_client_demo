/**
 * @file device_init.c
 * @author your name (you@dodevcice_init.com)
 * @brief
 * @version 0.1
 * @date 2022-05-11
 *
 * @copyright Copyright (c) 2022
 *
 */

#include "main.h"

/**
 * @brief 设备管理信息
 *
 */
mqMessageTypeDef *mqMessageConfig = NULL;

/**
 * @brief device_init.
 *
 * @return uint8_t
 */
uint8_t device_init(void)
{

	/* get configuration from config JSON file*/
	if (!config_get_MQ())
	{
		log_printf(MSG_ERROR, "device_init: config_get_MQ error!\n");
		return FALSE;
	}

	mqMessageConfig = mqCilent_init();
	if (mqMessageConfig == NULL)
	{
		log_printf(MSG_ERROR, "mqCilent_init error!\n");
		return FALSE;
	}

	return TRUE;
}

/**
 * @brief device_destroy.
 *
 */
void device_destroy(void)
{
	mqCilent_destroy(mqMessageConfig);
}