/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: helkhouj <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/19 22:41:41 by helkhouj          #+#    #+#             */
/*   Updated: 2025/04/19 22:41:52 by helkhouj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include <signal.h>
#include <limits.h>

volatile sig_atomic_t	g_ack = 0;

static void	ft_putstr(const char *s)
{
	while (*s)
		write(1, s++, 1);
}


static int	ft_atoi(const char *s)
{
	int			i = 0;
	int			sign = 1;
	long long	result = 0;

	while (s[i] == ' ' || s[i] == '\t' || s[i] == '\n')
		i++;
	if (s[i] == '+' || s[i] == '-')
	{
		if (s[i] == '-')
			sign = -1;
		i++;
	}
	while (s[i] >= '0' && s[i] <= '9')
	{
		result = result * 10 + (s[i++] - '0');
		if ((sign == 1 && result > INT_MAX) || (sign == -1 && -result < INT_MIN))
		{
			write(1, "INVALID PID\n", 12);
			exit(1);
		}
	}
	if (s[i] != '\0')
	{
		write(1, "INVALID PID\n", 12);
		exit(1);
	}
	return ((int)(result * sign));
}

static void	check_pid(pid_t pid)
{
	if (pid <= 0 || kill(pid, 0) == -1)
	{
		ft_putstr("INVALID PID\n");
		exit(1);
	}
}

static void	handle_ack(int sig)
{
	(void)sig;
	g_ack = 1;
}

static void	send_char(pid_t pid, char c)
{
	int	bit = 0;

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

int	main(int argc, char **argv)
{
	pid_t	pid;
	char	*msg;
	int		i = 0;

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
