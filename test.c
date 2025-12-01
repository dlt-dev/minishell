/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoesterl <aoesterl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/30 15:40:27 by aoesterl          #+#    #+#             */
/*   Updated: 2025/11/30 23:56:57 by aoesterl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Header/minishell.h"
#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>

int main(void)
{
    printf("=== TEST isatty() ===\n\n");

    printf("stdin  (fd 0): %s\n", isatty(STDIN_FILENO) ? "TTY" : "NOT TTY");
    printf("stdout (fd 1): %s\n", isatty(STDOUT_FILENO) ? "TTY" : "NOT TTY");
    printf("stderr (fd 2): %s\n", isatty(STDERR_FILENO) ? "TTY" : "NOT TTY");

    printf("\n");
    printf("errno = %d (%s)\n", errno, strerror(errno));

    // Essayer aussi d'appeler isatty sur un mauvais fd
    int ret = isatty(42);
    printf("\nfd 42 : %s (ret=%d)\n", ret == 1 ? "TTY" : "NOT TTY", ret);
    printf("errno = %d (%s)\n", errno, strerror(errno));

    return 0;
}

