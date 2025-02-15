/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dario <dario@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 20:05:00 by dario             #+#    #+#             */
/*   Updated: 2025/02/15 20:28:57 by dario            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"
#define BITS 8 // Tamaño de un carácter en bits

void enviar_caracter(pid_t server_pid, char c) {
    for (int i = BITS - 1; i >= 0; i--) {
        int bit = (c >> i) & 1;
        kill(server_pid, bit ? SIGUSR1 : SIGUSR2);
        usleep(10000); // Pequeña pausa para evitar pérdida de señales
    }
}

void enviar_mensaje(pid_t server_pid, const char *mensaje) {
    while (*mensaje) {
        enviar_caracter(server_pid, *mensaje);
        mensaje++;
    }
    enviar_caracter(server_pid, '\0'); // Enviar fin de mensaje
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Uso: %s <PID_SERVIDOR> <MENSAJE>\n", argv[0]);
        exit(1);
    }

    pid_t server_pid = atoi(argv[1]);
    const char *mensaje = argv[2];

    printf("Cliente: Enviando mensaje \"%s\" al servidor %d\n", mensaje, server_pid);
    enviar_mensaje(server_pid, mensaje);

    return 0;
}

// bool	arg_check(char *pid)
// {
// 	size_t	i;
// 	if (!pid)
// 		return (false);
// 	i = 0;
// 	while (pid[i])
// 	{
// 		if (!ft_isdigit(pid[i]))
// 			return (false);
// 		++i;
// 	}
// 	return (true);
// }

// int	main(int argc, char **argv)
// {
// 	if (argc != 3)
// 		error_exit("Incorrect amount of arguments");
// 	if (!arg_check(argv[1]))
// 		error_exit("PID should only contain digits");
// 	pid_t server_pid = ft_atoi(argv[1]);
	
// 	if (kill(server_pid, SIGUSR1) == -1)
// 	{
// 		error_exit("kill");
// 	}
// 	sleep(1);
	
// 	return (0);
// }