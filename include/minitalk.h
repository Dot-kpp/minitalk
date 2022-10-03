#ifndef MINITALK_H
# define MINITALK_H

#include <signal.h>
#include <unistd.h>
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

void	pid_error(char *str_error);
void	input_error(void);
void	success(int sig);


#endif