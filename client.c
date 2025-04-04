/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgavel <pgavel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 19:01:25 by pgavel            #+#    #+#             */
/*   Updated: 2025/04/04 05:24:14 by pgavel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* client.c */
#include <unistd.h>
#include <signal.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

// Envoie un seul bit au serveur
void send_bit(pid_t server_pid, int bit)
{
    if (bit)
        kill(server_pid, SIGUSR1);
    else
        kill(server_pid, SIGUSR2);
    
    // Petit délai pour assurer que le serveur a le temps de traiter
    usleep(100);
}

// Envoie un caractère au serveur bit par bit
void send_char(pid_t server_pid, unsigned char c)
{
    int i;
    unsigned char mask;
    
    // Envoie les bits du plus significatif au moins significatif
    for (i = 7; i >= 0; i--)
    {
        mask = 1 << i;
        send_bit(server_pid, c & mask);
    }
}

int main(int argc, char **argv)
{
    pid_t server_pid;
    char *message;
    size_t i;
    
    // Vérifier les arguments
    if (argc != 3)
    {
        printf("Usage: %s <server_pid> <message>\n", argv[0]);
        return (1);
    }
    
    // Récupérer le PID du serveur
    server_pid = atoi(argv[1]);
    if (server_pid <= 0)
    {
        printf("Invalid server PID\n");
        return (1);
    }
    
    // Récupérer le message
    message = argv[2];
    
    // Envoyer chaque caractère du message
    for (i = 0; i < strlen(message); i++)
        send_char(server_pid, message[i]);
    
    // Envoyer le caractère de fin
    send_char(server_pid, '\0');
    
    return (0);
}