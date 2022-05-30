/**
 * @file unit.c
 * @author your name (you@domain.com)
 * @brief
 * @version 0.1
 * @date 2022-03-08
 *
 * @copyright Copyright (c) 2022
 *
 */

#include "main.h"



static uint8_t flag_is_running = RESET;
volatile uint16_t plc_tokenSeed = 1;




/**
 * @brief Get the token object
 *
 * @param token
 */
void get_token(char *token)
{
	if (plc_tokenSeed >= 65535)
		plc_tokenSeed = 0;

	sprintf(token, "%d", plc_tokenSeed);

	plc_tokenSeed++;
}




/**
 * @brief  itobcd
 * @param  data: int data
 * @retval BCD data
 * @note
 */
uint8_t itobcd(uint8_t data)
{
	return (((data / 10 << 4) & 0xf0) | ((data % 10) & 0x0f));
}




/**
 * @brief  get the timestamp string
 * @param  psDateTime: string of get the system timestamp
 * @retval none
 * @note
 */
void mqtt_get_time(char *psDateTime)
{
	struct timeval tv;
	struct timezone tz;
	struct tm *pTM;

	gettimeofday(&tv, &tz);
	pTM = localtime(&tv.tv_sec);

	sprintf(psDateTime, "%04d-%02d-%02dT%02d:%02d:%02d.%03d+0800",
			pTM->tm_year + 1900, pTM->tm_mon + 1, pTM->tm_mday,
			pTM->tm_hour, pTM->tm_min, pTM->tm_sec, (int)(tv.tv_usec / 1000));
}



/**
 * @brief  is_app_running check
 * @param  running:
 * @retval None
 */
uint8_t is_app_running(void)
{
	return flag_is_running;
}




/**
 * @brief  set_app_running setting
 * @param  running:
 * @retval None
 */
void set_app_running(uint8_t running)
{
	flag_is_running = running;
}




/**
 * @brief delay_ms
 *
 * @param mSec
 */
void delay_ms(unsigned long mSec)
{
	struct timeval tv;
	tv.tv_sec = mSec / 1000;
	tv.tv_usec = (mSec % 1000) * 1000;
	int err;
	do
	{
		err = select(0, NULL, NULL, NULL, &tv);
	} while (err < 0 && errno == EINTR);
}




/**
 * @brief  set_app_running setting
 * @param  str:
 * @param  out:
 * @param  outlen:
 * @retval None
 */
int AtoH(char *str, uint8_t *out)
{
	char *p = str;

	char high = 0;
	char low = 0;

	int tmplen = 0;
	int cnt = 0;

	if ((str == NULL) || ((out == NULL)))
	{
		return 0;
	}

	tmplen = strlen(p);

	if (tmplen == 0)
	{
		return 0;
	}

	while (cnt < (tmplen / 2))
	{
		high = ((*p > '9') && ((*p <= 'F') || (*p <= 'f'))) ? *p - 48 - 7 : *p - 48;
		low = (*(++p) > '9' && ((*p <= 'F') || (*p <= 'f'))) ? *(p)-48 - 7 : *(p)-48;

		out[cnt] = ((high & 0x0f) << 4 | (low & 0x0f));

		p++;
		cnt++;
	}

	if (tmplen % 2 != 0)
	{
		out[cnt] = ((*p > '9') && ((*p <= 'F') || (*p <= 'f'))) ? *p - 48 - 7 : *p - 48;
	}

	return tmplen / 2 + tmplen % 2;
}





/**
 * @brief string to json
 *
 * @param str: input data
 * @return cJSON*
 */
cJSON *string2Json(const uint8_t *str)
{
	if (str == NULL)
	{
		log_printf(MSG_ERROR, "string2Json: (str == NULL)");
		return NULL;
	}

	cJSON *ret = cJSON_Parse((char *)str);
	if (ret == NULL)
	{
		log_printf(MSG_ERROR, "string2Json: ret == NULL!\n");
		return NULL;
	}
	else
	{
		if (ret->type != cJSON_Object)
		{
			log_printf(MSG_ERROR, "string2Json: ret->type error!\n");
			return NULL;
		}
	}

	return ret;
}
