/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dario <dario@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 20:05:00 by dario             #+#    #+#             */
/*   Updated: 2025/03/17 11:26:21 by dario            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void	send_char(pid_t server_pid, char c)
{
	int	bit;

	bit = 0;
	while (bit < BIT_SIZE)
	{
		if (c & (0x80) >> bit)
			ft_kill(server_pid, SIGUSR1);
		else
			ft_kill(server_pid, SIGUSR2);
		++bit;
		usleep(10000);
	}
}

void	send_msg(pid_t server_pid, const char *msg)
{
	while (*msg)
	{
		send_char(server_pid, *msg);
		++msg;
	}
	send_char(server_pid, '\0');
}

bool	pid_check(char *pid)
{
	size_t	i;

	if (!pid)
		return (false);
	i = 0;
	while (pid[i])
	{
		if (!ft_isdigit(pid[i]))
			return (false);
		++i;
	}
	return (true);
}

int	main(int argc, char **argv)
{
	const char	*msg;
	pid_t		pid;

	if (argc != 3)
	{
		ft_printf("Modo de ejecución: %s <PID_SERVIDOR> <MENSAJE>\n", argv[0]);
		exit(1);
	}
	msg = argv[2];
	if (!pid_check(argv[1]))
		error_exit("El PID debe estar formado únicamente por dígitos");
	pid = ft_atoi(argv[1]);
	ft_printf("Cliente: Enviando mensaje \"%s\" al servidor %d\n", msg, pid);
	send_msg(pid, msg);
	return (0);
}
