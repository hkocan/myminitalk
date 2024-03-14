/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkocan <hkocan@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 15:59:21 by hkocan            #+#    #+#             */
/*   Updated: 2024/01/17 18:33:41 by hkocan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include <unistd.h>

void	putnbr(long n)
{
	if (n > 9)
		putnbr(n / 10);
	write(1, &"012345679"[n % 10], 1);
}

static void	signal_handler(int sig, siginfo_t *inf, void *context)
{
	static unsigned char	c = 0;
	static unsigned char	i = 0;

	(void)context;
	c = (c << 1) | !!(sig == SIGUSR1);
	i++;
	write(1, &c, (i == 8));
	kill(inf->si_pid, (i == 8 && !c) * SIGUSR2);
	i = !(i == 8) * i;
}

int	main(void)
{
	struct sigaction	x;

	write(1, "Process ID: ", 11);
	putnbr(getpid());
	write(1, "\n", 1);
	x.sa_flags = SA_SIGINFO;
	x.sa_sigaction = signal_handler;
	sigaction(SIGUSR1, &x, NULL);
	sigaction(SIGUSR2, &x, NULL);
	while (1)
		pause();
}
