/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgavel <pgavel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 19:01:39 by pgavel            #+#    #+#             */
/*   Updated: 2025/04/04 05:19:26 by pgavel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* server.c */
#include <unistd.h>
#include <signal.h>
#include <stdlib.h>
#include <stdio.h>

// Variable globale pour stocker le caractère en cours de réception
static unsigned char g_char = 0;
static int g_bits_received = 0;

void handle_signal(int signum)
{
    // Décale le bit reçu et ajoute 1 si SIGUSR1, 0 si SIGUSR2
    g_char = g_char << 1;
    if (signum == SIGUSR1)
        g_char = g_char | 1;
    
    g_bits_received++;
    
    // Si on a reçu 8 bits (un caractère complet)
    if (g_bits_received == 8)
    {
        // Affiche le caractère
        write(1, &g_char, 1);
        
        // Réinitialise pour le prochain caractère
        g_char = 0;
        g_bits_received = 0;
    }
}

int main(void)
{
    pid_t pid;
    struct sigaction sa;
    
    // Obtenir et afficher le PID du serveur
    pid = getpid();
    printf("Server PID: %d\n", pid);
    
    // Configuration des gestionnaires de signaux
    sa.sa_handler = handle_signal;
    sa.sa_flags = 0;
    sigemptyset(&sa.sa_mask);
    
    // Enregistrement des gestionnaires
    sigaction(SIGUSR1, &sa, NULL);
    sigaction(SIGUSR2, &sa, NULL);
    
    // Boucle infinie pour rester actif et attendre les signaux
    while (1)
        pause();
    
    return (0);
}
