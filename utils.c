/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dario <dario@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 20:05:07 by dario             #+#    #+#             */
/*   Updated: 2025/03/17 15:47:58 by dario            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

char	*error_exit(const char *error_message)
{
	ft_printf(RED"\n-----\nERROR\n-----\n");
	if (error_message)
		ft_printf(YELLOW"%s\n"RST, error_message);
	exit(1);
}

void	signal_kill(pid_t pid, int signo)
{
	if (kill(pid, signo) < 0)
		error_exit("Signal kill failed");
}

void	create_signal(int signo, void *handler, bool siginfo)
{
	struct sigaction	sa;

	sa.sa_sigaction = handler;
	if (siginfo)
		sa.sa_flags = SA_SIGINFO;
	sigemptyset(&sa.sa_mask);
	sigaddset(&sa.sa_mask, SIGUSR1);
	sigaddset(&sa.sa_mask, SIGUSR2);
	if (sigaction(signo, &sa, NULL) < 0)
		error_exit("Sigaction failed");
}
