#include "../include/minitalk.h"

void	send_char(int pid, unsigned char byte)
{
	int	i;

	i = 1 << 6;
	while (i)
	{
		if (byte & i)
		{
			if (kill(pid, SIGUSR1) == -1)
				pid_error("Invalid pid\n");
		}
		else if (kill(pid, SIGUSR2) == -1)
				pid_error("Invalid pid\n");
		i >>= 1;
		usleep(200);
	}
}

void	client_handler(char *str_pid, char *message)
{
	int			pid;

	pid = ft_atoi(str_pid);
	while (*message)
	{
		send_char(pid, *message);
		message++;
	}
	send_char(pid, *message);
}

int		main(int argc, char **argv)
{
	if (argc != 3)
		input_error();
	signal(SIGUSR1, success);
	client_handler(argv[1], argv[2]);
	return (0);
}