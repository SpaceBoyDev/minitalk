/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dario <dario@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 20:05:05 by dario             #+#    #+#             */
/*   Updated: 2025/03/17 13:46:35 by dario            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <malloc.h>


void	handler(int signo, siginfo_t *info)
{
	static char		c = 0;
	static int		bit = 0;
	static pid_t	client_pid = 0;

	if (info->si_pid)
		client_pid = info->si_pid;
	if (signo == SIGUSR1)
		c |= (0b10000000 >> bit);
	else if (signo == SIGUSR2)
		c &= ~(0x80 >> bit);
	++bit;
	if (bit == BIT_SIZE)
	{
		bit = 0;
		if (c == '\0')
		{
			write(1, "\n", 1);
			signal_kill(client_pid, SIGUSR2);
			c = 0;
			return ;
		}
		write(1, &c, 1);
		c = 0;
	}
	signal_kill(client_pid, SIGUSR1);
}

int main()
{
	create_signal(SIGUSR1, handler, true);
	create_signal(SIGUSR2, handler, true);
	ft_printf("Servidor iniciado. PID: %d\n", getpid());
	while (1)
		pause(); // Espera señales
	return (0);
}
