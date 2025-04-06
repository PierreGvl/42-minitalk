/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgavel <pgavel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 19:01:25 by pgavel            #+#    #+#             */
/*   Updated: 2025/04/06 08:57:51 by pgavel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

static t_client_data	g_client_data;

/**
 * Handle acknowledgment signal from server
 */
static void	handle_ack(int signum)
{
	(void)signum;
	g_client_data.ack_received = 1;
}

/**
 * Send a single character to the server, bit by bit
 */
static void	send_char(pid_t server_pid, unsigned char c)
{
	int	bit;
	int	i;

	i = 0;
	while (i < 8)
	{
		g_client_data.ack_received = 0;
		bit = (c >> i) & 1;
		if (bit == 0)
		{
			if (kill(server_pid, SIGUSR1) == -1)
				exit_error("Error sending signal to server");
		}
		else
		{
			if (kill(server_pid, SIGUSR2) == -1)
				exit_error("Error sending signal to server");
		}
		
		// Wait for acknowledgment before sending next bit
		while (g_client_data.ack_received == 0)
			usleep(100);
		i++;
	}
}

/**
 * Send a string to the server, character by character
 */
static void	send_string(pid_t server_pid, char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
	{
		send_char(server_pid, str[i]);
		i++;
	}
	// Send null terminator to indicate end of string
	send_char(server_pid, 0);
}

/**
 * Set up the signal handler for acknowledgment
 */
static void	setup_signals(void)
{
	struct sigaction	sa;

	sa.sa_handler = handle_ack;
	sa.sa_flags = 0;
	sigemptyset(&sa.sa_mask);
	
	if (sigaction(SIGUSR1, &sa, NULL) == -1)
	{
		ft_putstr_fd("Error setting up signal handler\n", 2);
		exit(EXIT_FAILURE);
	}
}

int	main(int argc, char **argv)
{
	pid_t	server_pid;

	if (argc != 3)
	{
		ft_putstr_fd("Usage: ./client [server_pid] [message]\n", 2);
		return (EXIT_FAILURE);
	}

	server_pid = ft_atoi(argv[1]);
	if (server_pid <= 0)
	{
		ft_putstr_fd("Invalid server PID\n", 2);
		return (EXIT_FAILURE);
	}

	g_client_data.ack_received = 0;
	setup_signals();
	send_string(server_pid, argv[2]);
	
	return (0);
}