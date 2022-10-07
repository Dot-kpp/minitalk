#include "../include/minitalk.h"

void	pid_error(char *str_error)
{
	write(2, str_error, ft_strlen(str_error));
	exit(1);
}

void	input_error(void)
{
	write(1, "Please enter a valid input: ./client [server-pid] [message]\n", 59);
	exit(0);
}

void	signal_error(void)
{
	write(1, "Signal error\n", 13);
	exit(0);
}

void	success(void)
{
	write(1, "Received.\n", 10);
}