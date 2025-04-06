/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgavel <pgavel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 19:01:25 by pgavel            #+#    #+#             */
/*   Updated: 2025/04/06 11:27:44 by pgavel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minitalk.h"

static int	g_bit_received;

static void	sig_handler()
{
	g_bit_received = 1;
}

static int check_pid(char *pid_str)
{
    int pid;
	
	pid = ft_atoi(pid_str);

	if (kill(pid, 0) == -1)
		return (0);
 
    return (pid);
}

static void	send_char(pid_t server_pid, unsigned char c)
{
	int	bit;
	int	i;

	i = 0;
	while (i < 8)
	{
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
		while (g_bit_received == 0)
			usleep(100);
		i++;
	}
}

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

int	main(int argc, char **argv)
{
	pid_t	server_pid;

	if (argc != 3)
		ft_error("Usage: ./client [server_pid] [message]");

	server_pid = check_pid(argv[1]);
	if (!server_pid)
		ft_error("Invalid server PID");

	g_bit_received = 0;
	signal(SIGUSR1, sig_handler);
	
	send_string(server_pid, argv[2]);
	
	return (0);
}