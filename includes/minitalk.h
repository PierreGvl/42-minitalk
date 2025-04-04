/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitalk.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgavel <pgavel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 19:01:55 by pgavel            #+#    #+#             */
/*   Updated: 2025/04/04 05:07:12 by pgavel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINITALK_H
# define MINITALK_H

# include <signal.h>    // Pour signal, SIGUSR1, SIGUSR2
# include <unistd.h>    // Pour write, getpid, usleep, etc.
# include <stdlib.h>    // Pour malloc, free, exit, etc.
# include <sys/types.h>

// Configuration de base de la communication
# define WAIT_TIME 300 // Délai entre les signaux en microsecondes
# define ACK_TIMEOUT 5000 // Délai d'attente pour une confirmation (en microsecondes)

// Messages d'erreur
# define ERR_USAGE_CLIENT "Usage: ./client [server_pid] [message]"
# define ERR_USAGE_SERVER "Usage: ./server"
# define ERR_INVALID_PID "Error: Invalid PID"
# define ERR_SIGNAL_SEND "Error: Signal sending failed"

// Fonctions utilitaires
void    ft_putchar_fd(char c, int fd);
void    ft_putstr_fd(char *s, int fd);
void    ft_putnbr_fd(int n, int fd);
void    ft_putendl_fd(char *s, int fd);
void    ft_error(char *message);
int     ft_atoi(const char *str);
int     ft_isdigit(int c);
size_t  ft_strlen(const char *str);

#endif