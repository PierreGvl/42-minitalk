/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitalk.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgavel <pgavel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 19:01:55 by pgavel            #+#    #+#             */
/*   Updated: 2025/04/05 18:47:47 by pgavel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINITALK_H
# define MINITALK_H

# include <signal.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/types.h>

/**
 * Structure to hold server data
 */
typedef struct s_data
{
	int		bit_position;
	char	current_char;
	pid_t	client_pid;
}	t_data;

/**
 * Structure to hold client data
 */
typedef struct s_client_data
{
	int	ack_received;
}	t_client_data;

void	ft_putchar_fd(char c, int fd);
void	ft_putstr_fd(char *s, int fd);
void	ft_putnbr_fd(int n, int fd);
int		ft_atoi(const char *str);
size_t	ft_strlen(const char *s);

void	exit_error(char *message);

#endif