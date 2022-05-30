/**
 * @file main.h
 * @author your name (you@domain.com)
 * @brief
 * @version 0.1
 * @date 2022-03-08
 *
 * @copyright Copyright (c) 2022
 *
 */




/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H





/* c lib---------------------------------------------------------------------*/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <malloc.h>
#include <termios.h>
#include <stdarg.h>
#include <fcntl.h>
#include <pthread.h>
#include <signal.h>
#include <errno.h>
#include <semaphore.h>
#include <syslog.h>
#include <assert.h>



#include <sys/stat.h>
#include <sys/types.h>
#include <sys/select.h>
#include <sys/time.h>
#include <sys/epoll.h> 

/* mq lib inlcude ----------------------------------------------------------*/
#include "rabbitmq-c/amqp.h"
#include "rabbitmq-c/tcp_socket.h"

/* base lib.----------------------------------------------------------------*/
#include "cJSON.h"
#include "log_manage.h"
#include "cs_getopt.h"
#include "unit.h"
#include "fileCtr.h"


#include "mq_config_demo.h"


/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */
#define SET 1
#define RESET !SET



#ifndef TRUE
#define TRUE 1
#endif
#ifndef FALSE
#define FALSE !TRUE
#endif


#endif /* __MAIN_H */

