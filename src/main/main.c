/**
 * @file main.c
 * @author your name (you@domain.com)
 * @brief
 * @version 0.1
 * @date 2022-03-08
 *
 * @copyright Copyright (c) 2022
 *
 */

#include "main.h"

/**MAIN_FLAG_STOP*/
static uint8_t MAIN_FLAG_STOP = RESET;




/**
 * @brief signal_handler
 *
 * @param sig
 */
static void signal_handler(int sig)
{
	switch (sig)
	{
	case SIGINT: /* ctrl + c */
		MAIN_FLAG_STOP = SET;
		break;

	case SIGPIPE:
		break;

	default:
		break;
	}
}



/**
 * @brief main
 *
 * @param argc
 * @param argv
 * @return int
 */
int main(int argc, char **argv)
{
	log_set_level(MSG_INFO);

	/* configure signal handling */
	signal(SIGPIPE, signal_handler);
	signal(SIGINT, signal_handler);

	/* parse command line options */
	if (!getOptionParam(argc, argv))
	{
		log_printf(MSG_ERROR, "getOptionParam error!\n");
		exit(-1);
	}



	/* log file initialization */
#ifdef RSYSLOG
	if (!log_manageInit(TRUE))
#else
	if (!log_manageInit(FALSE))
#endif
	{
		log_printf(MSG_ERROR, "log_manageInit error!\r\n");
		exit(-1);
	}
	else
	{
		log_printf(MSG_DEBUG, "log_manageInit setting successfully!\r\n");
	}

	set_app_running(SET);

	while (1)
	{
		if (MAIN_FLAG_STOP)
		{
			set_app_running(FALSE);

			log_closeFile();

			log_printf(MSG_INFO, "main: program stopped.\n");
			exit(0);
		}

		sleep(1);
	}

	pause();

	return 0;
}

