/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: helkhouj <helkhouj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/19 22:58:08 by helkhouj          #+#    #+#             */
/*   Updated: 2025/04/19 23:04:10 by helkhouj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "client.h"

int	is_invalid_pid(long long result, int sign)
{
	if ((sign == 1 && result > INT_MAX) || (sign == -1 && - result < INT_MIN))
		return (1);
	return (0);
}

void	exit_invalid_pid(void)
{
	write(1, "INVALID PID\n", 12);
	exit(1);
}

int	ft_atoi(const char *s)
{
	int			i;
	int			sign;
	long long	result;

	i = 0;
	sign = 1;
	result = 0;
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
		if (is_invalid_pid(result, sign))
			exit_invalid_pid();
	}
	if (s[i] != '\0')
		exit_invalid_pid();
	return ((int)(result * sign));
}
