/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkocan <hkocan@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 15:59:36 by hkocan            #+#    #+#             */
/*   Updated: 2024/01/17 15:59:52 by hkocan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include <unistd.h>

int	ft_atoi(const char *str)
{
	int	sign;
	int	res;

	sign = 1;
	res = 0;
	while (*str == 32 || (9 <= *str && *str <= 13))
		str++;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			sign *= -1;
		str++;
	}
	while (*str != '\0' && (*str >= '0' && *str <= '9'))
	{
		res = (res * 10) + (*str - '0');
		str++;
	}
	return (res * sign);
}

static void	received_signal(int sig)
{
	if (sig == SIGUSR2)
	{
		write(1, "Signal Received\n", 16);
	}
}

static void	signal_sendler(pid_t pid, char c)
{
	int	i;

	i = -1;
	while (++i < 8)
	{
		if (c << i & 128)
			kill(pid, SIGUSR1);
		else
			kill(pid, SIGUSR2);
		usleep(200);
	}
}

int	main(int argc, char *argv[])
{
	pid_t	pid;

	if (argc == 3)
	{
		pid = ft_atoi(argv[1]);
		if (!pid || pid == -1)
		{
			write(2, "faulty pid", 10);
			return (1);
		}
		signal(SIGUSR2, received_signal);
		while (*argv[2])
			signal_sendler(pid, *argv[2]++);
		signal_sendler(pid, '\0');
		return (0);
	}
	else
	{
		write(1, "ENTER 3 ARGUMENTS\n", 19);
		write(1, "1-PROGRAM NAME,2-PID,3-MESSAGE\n", 32);
	}
	return (1);
}
