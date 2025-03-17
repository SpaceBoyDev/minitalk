/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitalk.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dario <dario@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 20:05:02 by dario             #+#    #+#             */
/*   Updated: 2025/03/17 13:27:29 by dario            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINITALK_H
# define MINITALK_H

# include <stdio.h>
# include <stdlib.h>
# include <stdbool.h>
# include <signal.h>

# include "libft/libft.h"

# define BIT_SIZE __CHAR_BIT__ /*8*/

# ifndef BUSY
#  define BUSY	0
# endif

# ifndef READY
#  define READY	1
# endif

char	*error_exit(const char *error_message);
void	signal_kill(pid_t pid, int signo);
void	create_signal(int signo, void *handler, bool siginfo);

#endif