/*
 * rtt_log.h
 *
 *  Created on: 2019/01/13
 *      Author: zekuan.czk
 */

#ifndef LOG_RTT_LOG_H__
#define LOG_RTT_LOG_H__

#ifdef __cplusplus
 extern "C" {
#endif

#include <stdint.h>
#include <stdarg.h>
#include <stdbool.h>
#include <stdio.h>
#include "SEGGER_RTT_Conf.h"
#include "SEGGER_RTT.h"

#ifndef USE_RTT_LOG
#define USE_RTT_LOG         (1)
#endif

#define LOG_USE_COLORS

#ifdef LOG_USE_COLORS
    #define LC_BLACK    "\x1B[1;30m"
    #define LC_RED      "\x1B[1;31m"
    #define LC_GREEN    "\x1B[1;32m"
    #define LC_YELLOW   "\x1B[1;33m"
    #define LC_BLUE     "\x1B[1;34m"
    #define LC_MAGENTA  "\x1B[1;35m"
    #define LC_CYAN     "\x1B[1;36m"
    #define LC_WHITE    "\x1B[1;37m"
    #define LC_DEFAULT
#else
    #define LC_BLACK
    #define LC_RED
    #define LC_GREEN
    #define LC_YELLOW
    #define LC_BLUE
    #define LC_MAGENTA
    #define LC_CYAN
    #define LC_WHITE
    #define LC_DEFAULT
#endif

int SEGGER_RTT_vprintf(unsigned BufferIndex, const char * sFormat, va_list * pParamList);
int SEGGER_RTT_printf(unsigned BufferIndex, const char * sFormat, ...);
int SEGGER_RTT_TerminalOut (char TerminalID, const char* s);
int SEGGER_RTT_SetTerminal (char TerminalId);

#define LOGX(x, ...)                {SEGGER_RTT_SetTerminal(x); \
                                    SEGGER_RTT_printf(0, __VA_ARGS__); \
                                    SEGGER_RTT_SetTerminal(0);}

#define MAX_LOG_BUFF_SIZE           (256u)

extern char log_buff[MAX_LOG_BUFF_SIZE];

#define LOG_DEFAULT_TERMINAL        0
#define LOG_PRINT(...)              SEGGER_RTT_printf(LOG_DEFAULT_TERMINAL, __VA_ARGS__);

#define LOG                         LOG_PRINT

#define LOG1_COLOR                  LC_GREEN
#define LOG1_TERMINAL               1
#define LOG1(...)                   LOGX(LOG1_TERMINAL, LOG1_COLOR __VA_ARGS__)

#define LOG2_COLOR                  LC_GREEN
#define LOG2_TERMINAL               2
#define LOG2(...)                   LOGX(LOG2_TERMINAL, LOG2_COLOR __VA_ARGS__)

#define LOG3_COLOR                  LC_GREEN
#define LOG3_TERMINAL               3
#define LOG3(...)                   LOGX(LOG3_TERMINAL, LOG3_COLOR __VA_ARGS__)

#define LOG4_COLOR                  LC_GREEN
#define LOG4_TERMINAL               4
#define LOG4(...)                   LOGX(LOG4_TERMINAL, LOG4_COLOR __VA_ARGS__)

#define LOG5_COLOR                  LC_GREEN
#define LOG5_TERMINAL               5
#define LOG5(...)                   LOGX(LOG5_TERMINAL, LOG5_COLOR __VA_ARGS__)

#define LOG6_COLOR                  LC_GREEN
#define LOG6_TERMINAL               6
#define LOG6(...)                   LOGX(LOG6_TERMINAL, LOG6_COLOR __VA_ARGS__)

//LOG compatible float format
#define LOGF_COLORS                 LC_MAGENTA
#define LOGF_TERMINAL               0
#define LOGF(...)                   {sprintf(log_buff, LOGF_COLORS __VA_ARGS__); \
                                    LOGX(LOGF_TERMINAL, log_buff);}

#define LOG_PRINTF(...)             {sprintf(log_buff, LOGF_COLORS __VA_ARGS__); \
                                    SEGGER_RTT_printf(LOG_DEFAULT_TERMINAL, log_buff);}
#define LOGFF                       LOG_PRINTF

//LOG for warnning..
#define WARN_LOG_COLOR              LC_YELLOW
#define WARN_LOG_TERMINAL           8
#define LOG_WARN(...)               {sprintf(log_buff, WARN_LOG_COLOR __VA_ARGS__); \
                                    LOGX(WARN_LOG_TERMINAL, log_buff);}
//LOG for error..
#define ERROR_LOG_COLOR             LC_RED
#define ERROR_LOG_TERMINAL          9
#define LOG_ERR(...)                {sprintf(log_buff, ERROR_LOG_COLOR __VA_ARGS__); \
                                    LOGX(ERROR_LOG_TERMINAL, log_buff);}
#define LOG_ERROR(...)              LOG(LC_RED __VA_ARGS__)
#define LOG_DEBUG(...)              LOG(LC_YELLOW __VA_ARGS__)														
#define LOG_INFO(...)               LOG(LC_GREEN __VA_ARGS__)
#define LOG_TRACE(...)              LOG(LC_CYAN __VA_ARGS__)

#ifdef __cplusplus
}
#endif

#endif /* LOG_RTT_LOG_H__ */
