#ifndef MINITALK_H
# define MINITALK_H

#include <signal.h>
#include <zconf.h>
#include "../libft/headers/libft.h"

# define BUFFSIZE 1

# ifndef TRUE
#  define TRUE 1
# endif

# ifndef FALSE
#  define FALSE 0
# endif


void	pid_error(char *str_error);
void	input_error(void);
void	success(int sig);


#endif