#include "../includes/minitalk.h"

void		print_pid(void)
{
	char	*tmp;

	tmp = ft_itoa(getpid());
	write(1, "Server pid: ", 12);
	write(1, tmp, ft_strlen(tmp));
	write(1, "\n", 1);
}

int			main(void)
{
	print_pid();
	main_handler();
}