/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_signaux.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdelattr <jdelattr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/26 15:57:33 by jdelattr          #+#    #+#             */
/*   Updated: 2025/11/27 14:47:25 by jdelattr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


#include "minishell.h"

#include <signal.h>
#include <stdio.h>
#include <readline/readline.h>

int	waitpid_verify_status(pid_t pid)
{
	int	status;

	waitpid(pid, &status, 0);
	if (WIFEXITED(status) != 0)
		return (WEXITSTATUS(status));
	if (WIFSIGNALED(status) != 0)
		return (WTERMSIG(status) + 128);
	return (0);
}

int	wait_and_status(t_shell *shell, pid_t last_pid)
{
	shell->exit_status = waitpid_verify_status(last_pid);
	while (waitpid(-1, 0, 0) != ERROR)
		continue ;
	return (0);
}

void handle_sigquit() // ctrl + backslash quitte les efants mais pas de shell ?
{

}


void	handle_sigint() // ctrl + C
{
	// SIGINT
	// ctrl-C displays a new prompt on a new line

    //Affiche un saut de ligne, réaffiche le prompt, et ne termine pas le shell.
    //Si une commande est en cours, elle doit être interrompue.


}


/* 	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);


struct sigaction sa;

// 1. Définir le handler
sa.sa_handler = handle_sigint;

// 2. Initialiser le masque de signaux bloqués (aucun ici)
sigemptyset(&sa.sa_mask);

// 3. Pas de flags spéciaux (0 par défaut)
sa.sa_flags = 0;

// Applique cette configuration pour le signal SIGINT (Ctrl+C)
sigaction(SIGINT, &sa, NULL); */


//check AVANT ET APRS READLINE

// REMETTRE LES SIGNAIX A 0 AU DEBUT DE CHAQUES FORK()
	//signal(SIGINT, SIG_DFL); -
	//signal(SIGQUIT, SIG_DFL);

// WAITPID() avec des signaux - LE int status - tule pour les signaux 

// Dans le main :

	//signal(SIGINT, handle_sigint);
	//signal(SIGQUIT, SIG_IGN);

//
/* void	find_exit_stat()
{
	int	g_exit_status = 0;

	// Après waitpid :
	if (WIFEXITED(status))
		g_exit_status = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
		g_exit_status = 128 + WTERMSIG(status);
} */