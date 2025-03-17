/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dario <dario@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 20:05:00 by dario             #+#    #+#             */
/*   Updated: 2025/03/17 21:34:45 by dario            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

volatile sig_atomic_t	g_server_pid = BUSY;

static void	ack_handler(void)
{
	g_server_pid = READY;
}

static void	end_handler(void)
{
	write(1, "\tMessage received\n", 19);
	exit(0);
}

void	send_char(pid_t server_pid, char c)
{
	int	bit;

	bit = 0;
	while (bit < BIT_SIZE)
	{
		if (c & (0x80) >> bit)
			signal_kill(server_pid, SIGUSR1);
		else
			signal_kill(server_pid, SIGUSR2);
		++bit;
		while (g_server_pid == BUSY)
			pause();
		g_server_pid = BUSY;
	}
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

	create_signal(SIGUSR1, ack_handler, false);
	create_signal(SIGUSR2, end_handler, false);
	if (argc != 3)
		error_exit("Client:\n"
			"Execute like this: ./client <SERVER_PID> <MESSAGE>\n");
	if (!pid_check(argv[1]))
		error_exit("Client:\nServer PID must contain digits only");
	msg = argv[2];
	pid = ft_atoi(argv[1]);
	ft_printf("Client:\n"
		"Sending message \"%s\" to server %d\n", msg, pid);
	while (*msg)
	{
		send_char(pid, *msg);
		++msg;
	}
	send_char(pid, '\0');
	return (0);
}
