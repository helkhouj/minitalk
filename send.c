/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   send.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: helkhouj <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/19 22:58:23 by helkhouj          #+#    #+#             */
/*   Updated: 2025/04/19 22:58:24 by helkhouj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "client.h"

void	handle_ack(int sig)
{
	(void)sig;
	g_ack = 1;
}

void	send_char(pid_t pid, char c)
{
	int	bit;

	bit = 0;
	while (bit < 8)
	{
		g_ack = 0;
		if (((c >> bit) & 1) == 1)
			kill(pid, SIGUSR2);
		else
			kill(pid, SIGUSR1);
		while (!g_ack)
			;
		bit++;
	}
}
