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
	if (!print_mess.top_bit)
	{
		print_mess.top_bit = 1 << 6;
		++(print_mess.top_byte);
	}
	print_mess.message[print_mess.top_byte] += print_mess.top_bit;
	print_mess.top_bit >>= 1;
	if (print_mess.top_byte == BUFFSIZE - 2 && !print_mess.top_bit)
		print_mess.overflow = 1;
}

void bit_turned_off(int sig, siginfo_t *info, void *context)
{
	(void)sig;
	(void)context;
	if (!print_mess.top_bit)
	{
		print_mess.top_bit = 1 << 6;
		++(print_mess.top_byte);
	}
	print_mess.top_bit >>= 1;
	if (print_mess.top_byte == BUFFSIZE - 2 && !print_mess.top_bit)
		print_mess.overflow = 1;
	else if (!print_mess.message[print_mess.top_byte] && !print_mess.top_bit)
	{
		print_mess.received = 1;
		kill(info->si_pid, SIGUSR1);
	}
}

t_bool server_handler(void)
{
	while (1)
	{
		pause();
		if (print_mess.received || print_mess.overflow)
		{
			write(1, print_mess.message, ft_strlen(print_mess.message));
			ft_bzero(print_mess.message, BUFFSIZE);
			print_mess.top_byte = 0;
			print_mess.top_bit = 1 << 6;
			if (print_mess.received)
				write(1, "\n", 1);
			print_mess.received = False;
			print_mess.overflow = False;
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
	ft_bzero(print_mess.message, BUFFSIZE);
	server_handler();
}
