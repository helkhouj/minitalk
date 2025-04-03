#include <signal.h>
#include <unistd.h>
#include <sys/types.h>


static void	ft_putnbr(pid_t pid)
{
	char	digit;

	if (pid > 9)
		ft_putnbr(pid / 10);
	digit = (pid % 10) + '0';
	write(1, &digit, 1);
}

static void	signal_handler(int sig)
{
	static int	bit = 7;
	static char	c = 0;

	if (sig == SIGUSR1)
		c |= (1 << bit);
	else if (sig == SIGUSR2)
		c &= ~(1 << bit);
	bit--;
	if (bit < 0)
	{
		if (c == '\0')
			write(1, "\n", 1);
		else
			write(1, &c, 1);
		bit = 7;
		c = 0;
	}
}

int	main(void)
{
	pid_t	pid;

	pid = getpid();
	write(1, "Server PID: ", 12);
	ft_putnbr(pid);
	write(1, "\n", 1);
	signal(SIGUSR1, signal_handler);
	signal(SIGUSR2, signal_handler);
	while (1)
		pause();
	return (0);
}
