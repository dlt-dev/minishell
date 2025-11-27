/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_signaux.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoesterl <aoesterl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/26 15:57:33 by jdelattr          #+#    #+#             */
/*   Updated: 2025/11/27 12:36:16 by aoesterl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* 	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);


struct sigaction	sa;

// 1. Définir le handler
sa.sa_handler = handle_sigint;

// 2. Initialiser le masque de signaux bloqués (aucun ici)
sigemptyset(&sa.sa_mask);

// 3. Pas de flags spéciaux (0 par défaut)
sa.sa_flags = 0;

// Applique cette configuration pour le signal SIGINT (Ctrl+C)
sigaction(SIGINT, &sa, NULL); */

// void	handle_sigint(void)
// {
// }