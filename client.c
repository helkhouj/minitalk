/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: helkhouj <helkhouj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/19 22:41:41 by helkhouj          #+#    #+#             */
/*   Updated: 2025/04/19 22:52:52 by helkhouj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "client.h"

volatile sig_atomic_t	g_ack = 0;

int	main(int argc, char **argv)
{
	pid_t	pid;
	char	*msg;
	int		i;

	i = 0;
	if (argc != 3)
	{
		ft_putstr("Usage: ./client <PID> <message>\n");
		exit(1);
	}
	pid = (pid_t)ft_atoi(argv[1]);
	check_pid(pid);
	msg = argv[2];
	signal(SIGUSR1, handle_ack);
	while (msg[i])
		send_char(pid, msg[i++]);
	send_char(pid, '\0');
	return (0);
}
