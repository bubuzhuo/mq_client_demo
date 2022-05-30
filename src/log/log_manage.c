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

#include "main.h"






#ifdef CONFIG_LOG
static FILE *LOG_FILE = NULL;
#endif

logLevelEnum log_level = MSG_DEBUG;
volatile uint8_t rsyslog_flag = FALSE;




/**
 * @brief log_set_level
 *
 * @param level
 * @return uint8_t
 */
uint8_t log_set_level(logLevelEnum level)
{
	if ((level > 4) || (level < 0))
	{
		log_printf(MSG_ERROR, "msg_error: failed to set log level.\n");
		return FALSE;
	}
	else
	{
		log_level = level;
		log_printf(MSG_INFO, "[%d] log_set_level ok.\n", log_level);
		return TRUE;
	}
}



/**
 * @brief log_printf
 *
 * @param level
 * @param fmt
 * @param ...
 */
void log_printf(logLevelEnum level, const char *fmt, ...)
{
	va_list ap;
#ifdef DEBUG_TIME
	struct tm *pTM;
	time_t nSeconds;
#endif
	va_start(ap, fmt);

	if (level >= log_level)
	{
#ifdef DEBUG_TIME
		time(&nSeconds);
		pTM = localtime(&nSeconds);
#endif
#ifdef CONFIG_LOG
		if (LOG_FILE)
		{
#ifdef DEBUG_TIME
			fprintf(LOG_FILE, "%4d-%02d-%02d %02d:%02d:%02d ",
					pTM->tm_year + 1900, pTM->tm_mon + 1, pTM->tm_mday, pTM->tm_hour, pTM->tm_min, pTM->tm_sec);
#endif
			vfprintf(LOG_FILE, fmt, ap);
		}
		else
		{
#endif

			if (rsyslog_flag)
			{
				switch (level)
				{
				case MSG_VERBOSE:
					vsyslog(LOG_NOTICE, fmt, ap);
					break;

				case MSG_DEBUG:
					vsyslog(LOG_DEBUG, fmt, ap);
					break;

				case MSG_INFO:
					vsyslog(LOG_INFO, fmt, ap);
					break;

				case MSG_WARNING:
					vsyslog(LOG_WARNING, fmt, ap);
					break;

				case MSG_ERROR:
					vsyslog(LOG_ERR, fmt, ap);
					break;

				default:
					break;
				}
			}
			else
			{
#ifdef DEBUG_TIME
				printf("%4d-%02d-%02d %02d:%02d:%02d ",
					   pTM->tm_year + 1900, pTM->tm_mon + 1, pTM->tm_mday, pTM->tm_hour, pTM->tm_min, pTM->tm_sec);
#endif
				vprintf(fmt, ap);
			}

#ifdef CONFIG_LOG
		}
#endif
	}
	va_end(ap);
}



#ifdef CONFIG_LOG
static uint8_t log_createFile(const char *path)
{
	if (path == NULL)
	{
		log_printf(MSG_ERROR, "path is NULL\r\n");
		return FALSE;
	}

	LOG_FILE = fopen(path, "a");
	if (LOG_FILE == NULL)
	{
		log_printf(MSG_ERROR, "log_open_file: failed to open %s log file, using standard output\r\n", path);
		return FALSE;
	}

	log_printf(MSG_DEBUG, "Create log file successfully, path: %s.\r\n", path);

	return TRUE;
}
#endif



void log_closeFile(void)
{

#ifdef CONFIG_LOG
	if (LOG_FILE == NULL)
	{
		log_printf(MSG_ERROR, "log file pointer is NULL!\r\n");
		return;
	}

	fclose(LOG_FILE);
	LOG_FILE = NULL;
#endif

	if (rsyslog_flag)
		closelog();
}




/**
 * @brief log_manageInit
 *
 * @param enable
 * @return uint8_t
 */
uint8_t log_manageInit(uint8_t enable)
{



#ifdef CONFIG_LOG
	char log_dir[64] = {0};

	struct tm *pTM;
	time_t nSeconds;

	time(&nSeconds);
	pTM = localtime(&nSeconds);

	sprintf(log_dir, "./log_%4d-%02d-%02d",
			pTM->tm_year + 1900, pTM->tm_mon + 1, pTM->tm_mday);

	if (!log_createFile(log_dir))
	{
		log_printf(MSG_ERROR, "log_createFile error!\r\n");
		return FALSE;
	}

#endif

	if (enable)
	{
		rsyslog_flag = TRUE;
		printf("log_manageInit: openlog init.\n");
		openlog("XhPLCService", LOG_PID | LOG_NDELAY, LOG_USER);
	}

	return TRUE;
}

