/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: helkhouj <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/19 22:41:57 by helkhouj          #+#    #+#             */
/*   Updated: 2025/04/19 22:42:04 by helkhouj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include <unistd.h>

void	ft_putchar(char c)
{
	write(1, &c, 1);
}

void	ft_putnbr(int nbr)
{
	long	n;

	n = nbr;
	if (n < 0)
	{
		write(1, "-", 1);
		n *= -1;
	}
	if (n > 9)
	{
		ft_putnbr(n / 10);
		ft_putnbr(n % 10);
	}
	else
	{
		ft_putchar(n + '0');
	}
}

void	sig_super_func(int n, siginfo_t *info, void *pure)
{
	static int		i_bits;
	static char		c;
	static pid_t	current;

	if (info->si_pid != current)
	{
		i_bits = 0;
		c = 0;
		current = info->si_pid;
	}
	(void)pure;
	if (n == SIGUSR2)
		c |= (1 << i_bits);
	i_bits++;
	if (i_bits == 8)
	{
		if (c == '\0')
			write(1, "\n", 1);
		else
			write(1, &c, 1);
		c = 0;
		i_bits = 0;
	}
	kill(current, SIGUSR1);
}

int	main(void)
{
	struct sigaction	sa;

	ft_putnbr(getpid());
	ft_putchar('\n');
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = SA_SIGINFO;
	sa.sa_sigaction = sig_super_func;
	sigaction(SIGUSR1, &sa, NULL);
	sigaction(SIGUSR2, &sa, NULL);
	while (1)
		pause();
	return (0);
}
