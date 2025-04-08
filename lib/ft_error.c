/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgavel <pgavel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/06 16:19:28 by pgavel            #+#    #+#             */
/*   Updated: 2025/04/06 16:19:29 by pgavel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minitalk.h"

void	ft_error(char *message)
{
	ft_putstr_fd("\033[31m", 2);
	ft_putstr_fd(message, 2);
	ft_putstr_fd("\033[0m\n", 2);
	exit(EXIT_FAILURE);
}
