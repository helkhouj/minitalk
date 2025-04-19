/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: helkhouj <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/19 22:59:04 by helkhouj          #+#    #+#             */
/*   Updated: 2025/04/19 22:59:09 by helkhouj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "client.h"

void	ft_putstr(const char *s)
{
	while (*s)
		write(1, s++, 1);
}

void	check_pid(pid_t pid)
{
	if (pid <= 0 || kill(pid, 0) == -1)
	{
		ft_putstr("INVALID PID\n");
		exit(1);
	}
}
