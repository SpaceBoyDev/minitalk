/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dario <dario@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 20:05:00 by dario             #+#    #+#             */
/*   Updated: 2025/02/12 20:02:27 by dario            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

bool	arg_check(char *pid)
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
	if (argc != 3)
		error_exit("Incorrect amount of arguments");
	if (!arg_check(argv[1]))
		error_exit("PID should only contain digits");

	return (0);
}