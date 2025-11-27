/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signaux.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoesterl <aoesterl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/06 18:59:45 by aoesterl          #+#    #+#             */
/*   Updated: 2025/11/27 12:37:46 by aoesterl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include <unistd.h>
// #include <signal.h>
// #include <stdio.h>
// #include <stdio.h>
// #include <readline/readline.h>
// #include <readline/history.h>

// volatile sig_atomic_t flag_sig = 0;

// void handle_sig(int sig)
// {
//     if(flag_sig == 1)
//         return ;
//     if(sig == SIGINT)
//         write(1, "\nSignal INT\n", 11);
//     if(sig == SIGQUIT)
//         write(1, "\nSignal QUIT\n", 12);
// }

// int main ()
// {
//     int i;

//     i = 0;
//     struct sigaction sig;

//     sig = (struct sigaction){0};
//     sig.sa_handler = handle_sig;
//     sigemptyset(&sig.sa_mask);
//     sig.sa_flags = 0;

//     sigaction(SIGINT, &sig, NULL);
//     sigaction(SIGQUIT, &sig, NULL);
//     while (1)
//     {
//         i = 0;
//         flag_sig = 0;
//         readline("prompt: $ ");
//         flag_sig = 1;
//         while(i < 10000000)
//             i++;

//     }

// }