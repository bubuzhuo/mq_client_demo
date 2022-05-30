/**
 * @file fileCtr.c
 * @author your name (you@domain.com)
 * @brief
 * @version 0.1
 * @date 2022-04-26
 *
 * @copyright Copyright (c) 2022
 *
 */

#include "main.h"

/**
 * @brief Get the Config object
 *
 * @param filedir
 * @return char* 使用完后需要对内存进行释放
 */
char *FILE_getFromDir(const char *filedir, uint32_t fileSize)
{
	int filehandle = 0;
	uint32_t read_len = 0;

	if ((filedir == NULL) || (fileSize < 1))
	{
		log_printf(MSG_ERROR, "FILE_getFromDir: (filedir == NULL)\n");
		return NULL;
	}

	char *ret_buffer = (char *)malloc(fileSize);
	if (ret_buffer == NULL)
	{
		log_printf(MSG_ERROR, "FILE_getFromDir: (ret_buffer == NULL)\n");
		return NULL;
	}
	memset(ret_buffer, 0x00, fileSize);

	filehandle = open(filedir, O_RDONLY);
	read_len = read(filehandle, ret_buffer, fileSize);

	if (read_len > 0)
	{
		log_printf(MSG_INFO, "FILE_getFromDir: read_len:%d\n[JSON String]:\n%s\n",
				   read_len, ret_buffer);
	}
	else
	{
		log_printf(MSG_ERROR, "FILE_getFromDir: read() error!\n");
		free(ret_buffer);
		ret_buffer = NULL;
	}

	close(filehandle);

	return ret_buffer;
}
