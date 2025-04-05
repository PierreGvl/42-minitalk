/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgavel <pgavel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 19:01:39 by pgavel            #+#    #+#             */
/*   Updated: 2025/04/05 17:58:32 by pgavel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

static t_data	g_data;

/**
 * Initializes the global data structure.
 */
static void	init_data(void)
{
	g_data.bit_position = 0;
	g_data.current_char = 0;
	g_data.client_pid = 0;
}

/**
 * Handle the signal received from client
 * SIGUSR1 represents a bit value of 0
 * SIGUSR2 represents a bit value of 1
 */
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
	
	// Envoyer l'accusé de réception après chaque bit, pas seulement après un caractère complet
	kill(g_data.client_pid, SIGUSR1);
}

/**
 * Set up the signal handler
 */
static void	setup_signals(void)
{
	struct sigaction	sa;

	sa.sa_sigaction = handle_signal;
	sa.sa_flags = SA_SIGINFO;
	sigemptyset(&sa.sa_mask);
	
	if (sigaction(SIGUSR1, &sa, NULL) == -1)
	{
		ft_putstr_fd("Error setting up SIGUSR1 handler\n", 2);
		exit(EXIT_FAILURE);
	}
	
	if (sigaction(SIGUSR2, &sa, NULL) == -1)
	{
		ft_putstr_fd("Error setting up SIGUSR2 handler\n", 2);
		exit(EXIT_FAILURE);
	}
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