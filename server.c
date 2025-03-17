/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dario <dario@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 20:05:05 by dario             #+#    #+#             */
/*   Updated: 2025/03/17 11:48:21 by dario            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <malloc.h>

char    *mensaje;
int     bit_count = 0;
char    caracter_actual = 0;

void    manejador(int sig)
{
    // Desplazar un bit a la izquierda
    caracter_actual <<= 1;

    // Si la señal es SIGUSR1, añadimos un '1'
    if (sig == SIGUSR1)
    {
        caracter_actual |= 1;
    }
    bit_count++;
    // Cuando se reciben 8 bits, se almacena el carácter
    if (bit_count == BIT_SIZE)
    {
        int len = mensaje ? ft_strlen(mensaje) : 0;
        mensaje = realloc(mensaje, len + 2); // +2 para el nuevo char y el '\0'
        mensaje[len] = caracter_actual;
        mensaje[len + 1] = '\0';
        if (caracter_actual == '\0')
        { // Fin del mensaje
            printf("Servidor: Mensaje recibido -> \"%s\"\n", mensaje);
            free(mensaje);
            mensaje = NULL;
        }
        caracter_actual = 0;
        bit_count = 0;
    }
}

int main()
{
    struct sigaction    sa;
    sigemptyset(&sa.sa_mask);
    sa.sa_handler = manejador;
    sa.sa_flags = 0;
    sigaction(SIGUSR1, &sa, NULL);
    sigaction(SIGUSR2, &sa, NULL);
    printf("Servidor iniciado. PID: %d\n", getpid());
    while (1)
        pause(); // Espera señales
    return (0);
}
