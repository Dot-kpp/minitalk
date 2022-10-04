#ifndef MINITALK_H
# define MINITALK_H

#include <signal.h>
#include <unistd.h>
#include <zconf.h>
#include "../libft/headers/libft.h"

# define BUFFSIZE 1

typedef enum e_bool
{
    True,
    False,
}   t_bool;

typedef struct s_stack
{
    char message[BUFFSIZE];
}   t_stack;


typedef struct s_msg
{
	char	c;
	size_t	size;
}			t_msg;

t_msg		g_data;


void	pid_error(char *str_error);
void	input_error(void);
void	success(int sig);
void	signal_error(void);


#endif