/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitalk.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgavel <pgavel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 19:01:55 by pgavel            #+#    #+#             */
/*   Updated: 2025/04/14 21:22:02 by pgavel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINITALK_H
# define MINITALK_H

# define _GNU_SOURCE

# include <signal.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/types.h>

typedef struct s_data
{
	int		bit_position;
	char	current_char;
	pid_t	client_pid;
}	t_data;

void	ft_putchar_fd(char c, int fd);
void	ft_putstr_fd(char *s, int fd);
void	ft_putnbr_fd(int n, int fd);
int		ft_atoi(const char *str);
void	ft_error(char *message);

#endif