/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgavel <pgavel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 19:01:39 by pgavel            #+#    #+#             */
/*   Updated: 2025/04/14 21:31:09 by pgavel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

static t_data	g_data;

static void	init_data(void)
{
	g_data.bit_position = 0;
	g_data.current_char = 0;
	g_data.client_pid = 0;
}

static void	handle_signal(int signum, siginfo_t *info, void *context)
{
	(void)context;
	if (g_data.client_pid == 0)
		g_data.client_pid = info->si_pid;
	if (g_data.client_pid != info->si_pid)
	{
		g_data.client_pid = info->si_pid;
		g_data.bit_position = 0;
		g_data.current_char = 0;
	}
	if (signum == SIGUSR2)
		g_data.current_char |= (1 << g_data.bit_position);
	g_data.bit_position++;
	if (g_data.bit_position == 8)
	{
		if (g_data.current_char == 0)
			ft_putchar_fd('\n', 1);
		else
			ft_putchar_fd(g_data.current_char, 1);
		g_data.bit_position = 0;
		g_data.current_char = 0;
	}
	kill(g_data.client_pid, SIGUSR1);
}

static void	setup_signals(void)
{
	struct sigaction	sa;

	sa.sa_sigaction = handle_signal;
	sa.sa_flags = SA_SIGINFO;
	sigemptyset(&sa.sa_mask);
	if (sigaction(SIGUSR1, &sa, NULL) == -1)
		ft_error("Error setting up SIGUSR1 handler");
	if (sigaction(SIGUSR2, &sa, NULL) == -1)
		ft_error("Error setting up SIGUSR2 handler");
}

int	main(void)
{
	init_data();
	setup_signals();
	ft_putstr_fd("Server PID: ", 1);
	ft_putnbr_fd(getpid(), 1);
	ft_putchar_fd('\n', 1);
	while (1)
		pause();
	return (0);
}
