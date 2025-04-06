/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgavel <pgavel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 19:01:25 by pgavel            #+#    #+#             */
/*   Updated: 2025/04/06 10:24:07 by pgavel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

// static t_client_data	g_client_data;

static int	g_bit_received;

/*
static void	handle_ack(int signum)
{
	(void)signum;
	g_client_data.ack_received = 1;
}
*/

static void	sig_handler(int sig)
{
	if (sig == SIGUSR1)
		g_bit_received = 1;
	else if (sig == SIGUSR2)
		ft_putstr_fd("OK",1);
}

static void	send_char(pid_t server_pid, unsigned char c)
{
	int	bit;
	int	i;

	i = 0;
	while (i < 8)
	{
		//g_client_data.ack_received = 0;
		g_bit_received = 0;
		bit = (c >> i) & 1;
		if (bit == 0)
		{
			if (kill(server_pid, SIGUSR1) == -1)
				ft_error("Error sending signal to server");
		}
		else
		{
			if (kill(server_pid, SIGUSR2) == -1)
				ft_error("Error sending signal to server");
		}
		
		// Wait for acknowledgment before sending next bit
		while (g_bit_received == 0)
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
/*
static void	setup_signals(void)
{
	struct sigaction	sa;

	sa.sa_handler = handle_ack;
	sa.sa_flags = 0;
	sigemptyset(&sa.sa_mask);
	
	if (sigaction(SIGUSR1, &sa, NULL) == -1)
		ft_error("Error setting up signal handler");
}*/

int	main(int argc, char **argv)
{
	pid_t	server_pid;

	if (argc != 3)
		ft_error("Usage: ./client [server_pid] [message]");

	server_pid = ft_atoi(argv[1]);
	if (server_pid <= 0)
		ft_error("Invalid server PID");

	//g_client_data.ack_received = 0;
	//setup_signals();
	g_bit_received = 0;
	signal(SIGUSR1, sig_handler);
	
	send_string(server_pid, argv[2]);
	
	return (0);
}