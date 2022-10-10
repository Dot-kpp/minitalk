#include "../include/minitalk.h"

void		print_pid(void)
{
	char	*tmp;

	tmp = ft_itoa(getpid());
	write(1, "Server pid: ", 12);
	write(1, tmp, ft_strlen(tmp));
	write(1, "\n", 1);
}

void bit_turned_on(int sig, siginfo_t *info, void *context)
{
	(void)sig;
	(void)context;
	(void)info;
	if (!print.top_bit)
	{
		print.top_bit = 1 << 6;
		++(print.top_byte);
	}
	print.message[print.top_byte] += print.top_bit;
	print.top_bit >>= 1;
	if (print.top_byte == BUFFSIZE - 2 && !print.top_bit)
		print.overflow = TRUE;
}

void bit_turned_off(int sig, siginfo_t *info, void *context)
{
	(void)sig;
	(void)context;
	if (!print.top_bit)
	{
		print.top_bit = 1 << 6;
		++(print.top_byte);
	}
	print.top_bit >>= 1;
	if (print.top_byte == BUFFSIZE - 2 && !print.top_bit)
		print.overflow = TRUE;
	else if (!print.message[print.top_byte] && !print.top_bit)
	{
		print.received = TRUE;
		kill(info->si_pid, SIGUSR1);
	}
}

t_bool server_handler(void)
{
	while (1)
	{
		pause();
		if (print.received || print.overflow)
		{
			write(1, print.message, ft_strlen(print.message));
			ft_bzero(print.message, BUFFSIZE);
			print.top_byte = 0;
			print.top_bit = 1 << 6;
			if (print.received)
				write(1, "\n", 1);
			print.reveived = False;
			print.overflow = False;
		}
	}
	return (True);
}

int			main(void)
{
	struct sigaction active_bit;
	struct sigaction null_bit;

	active_bit.sa_sigaction = bit_turned_on;
	null_bit.sa_sigaction = bit_turned_off;
	active_bit.sa_flags = SA_SIGINFO;
	null_bit.sa_flags = SA_SIGINFO;

	if (sigaction(SIGUSR1, &active_bit, NULL) != 0)
		signal_error();
	if (sigaction(SIGUSR2, &null_bit, NULL) != 0)
		signal_error();
	print_pid();
	ft_bzero(print.message, BUFFSIZE);
	server_handler();
}
