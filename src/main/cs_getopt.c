/**
 * @file cs_getopt.c
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2022-03-08
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#include "main.h"


/**
 * @brief help
 * 
 */
static void help(void)
{
	printf("option:\n");
	printf("       -h print help information\n");
	printf("       -v print version\n");
	printf("       -DV log out with verbose\n");
	printf("       -DI log out with information\n");
	printf("       -DD log out with debug\n");
	printf("       -DW log out with warnning\n");
	printf("       -DE log out with error\n");
}




/**
 * @brief Get the Option Param object
 * 
 * @param argc 
 * @param argv 
 * @return uint8_t 
 */
uint8_t getOptionParam(int argc, char **argv)
{
	int ch;

	ch = getopt(argc, argv, "hvD:");
	if (ch == -1)
	{
		log_printf(MSG_ERROR, "getopt error!\n");
		return FALSE;
	}

	switch (ch)
	{
	case 'h':
		help();
		exit(0);
		break;

	case 'v':
		printf("version: ST%02d.%03d\n", SOFTWAREVERSION_H, SOFTWAREVERSION_L);
		exit(0);
		break;

	case 'D':
		if (!strcmp(optarg, "V"))
			log_set_level(MSG_VERBOSE);
		else if (!strcmp(optarg, "I"))
			log_set_level(MSG_INFO);
		else if (!strcmp(optarg, "D"))
			log_set_level(MSG_DEBUG);
		else if (!strcmp(optarg, "W"))
			log_set_level(MSG_WARNING);
		else if (!strcmp(optarg, "E"))
			log_set_level(MSG_ERROR);
		break;

	default:
		help();
		break;
	}

	return TRUE;
}

