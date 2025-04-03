#include <signal.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>


static void	ft_putstr(char *str)
{
	while (*str)
		write(1, str++, 1);
}

static int	ft_atoi(const char *str)
{
	int	result = 0;

	while (*str >= '0' && *str <= '9')
		result = result * 10 + (*str++ - '0');
	return (result);
}

static void	send_char(pid_t pid, char c)
{
	int	bit;

	bit = 7;
	while (bit >= 0)
	{
		if ((c >> bit) & 1)
			kill(pid, SIGUSR1);
		else
			kill(pid, SIGUSR2);
		usleep(100);
		bit--;
	}
}

int	main(int argc, char **argv)
{
	pid_t	pid;
	char	*msg;
	int		i;

	if (argc != 3)
	{
		ft_putstr("Usage: ./client <PID> <message>\n");
		return (1);
	}
	pid = (pid_t)ft_atoi(argv[1]);
	msg = argv[2];
	i = 0;
	while (msg[i])
		send_char(pid, msg[i++]);
	send_char(pid, '\0');
	return (0);
}
