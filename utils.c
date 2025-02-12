/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dario <dario@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 20:05:07 by dario             #+#    #+#             */
/*   Updated: 2025/02/12 20:05:21 by dario            ###   ########.fr       */
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