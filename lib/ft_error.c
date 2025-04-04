#include "../includes/minitalk.h"

void	ft_error(char *message)
{
	ft_putstr_fd("\033[31m", 2);
	ft_putstr_fd(message, 2);
	ft_putstr_fd("\033[0m\n", 2);
	exit(EXIT_FAILURE);
}