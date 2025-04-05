/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitalk.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgavel <pgavel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 19:01:55 by pgavel            #+#    #+#             */
/*   Updated: 2025/04/05 17:48:19 by pgavel           ###   ########.fr       */
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

/**
 * Helper functions (équivalentes à libft)
 */

/* ft_putchar_fd - Écrit un caractère dans un descripteur de fichier */
void	ft_putchar_fd(char c, int fd);

/* ft_putstr_fd - Écrit une chaîne dans un descripteur de fichier */
void	ft_putstr_fd(char *s, int fd);

/* ft_putnbr_fd - Écrit un nombre dans un descripteur de fichier */
void	ft_putnbr_fd(int n, int fd);

/* ft_atoi - Convertit une chaîne en entier */
int		ft_atoi(const char *str);

/* ft_strlen - Retourne la longueur d'une chaîne */
size_t	ft_strlen(const char *s);

/**
 * Helper function for error handling
 */
void	exit_error(char *message);

#endif