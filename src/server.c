#include "../include/minitalk.h"

void		print_pid(void)
{
	char	*tmp;

	tmp = ft_itoa(getpid());
	write(1, "Server pid: ", 12);
	write(1, tmp, ft_strlen(tmp));
	write(1, "\n", 1);
}

void bit_turned_on();
void bit_turned_off();

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
	struct sigaction sa;

	sa.sa_handler = &server_handle;
	sa.sa_flags = SA_SIGINFO;
	
	print_pid();
	server_handler();
}
