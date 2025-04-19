/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: helkhouj <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/19 22:59:17 by helkhouj          #+#    #+#             */
/*   Updated: 2025/04/19 22:59:18 by helkhouj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CLIENT_H
# define CLIENT_H

# include <unistd.h>
# include <stdlib.h>
# include <signal.h>
# include <limits.h>

extern volatile sig_atomic_t	g_ack;

void	ft_putstr(const char *s);
int		ft_atoi(const char *s);
void	check_pid(pid_t pid);
void	handle_ack(int sig);
void	send_char(pid_t pid, char c);
int		is_invalid_pid(long long result, int sign);
void	exit_invalid_pid(void);

#endif
