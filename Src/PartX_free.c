/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PartX_free.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arthurito <arthurito@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/30 17:44:28 by aoesterl          #+#    #+#             */
/*   Updated: 2025/11/08 22:59:57 by arthurito        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void free_all(t_shell *shell)
{ 
	ft_free_lst(&shell->lst);
	ft_free_str(&shell->invite.prompt);
	ft_free_str(&shell->rd_line);
	free_chunk_buffer(&shell->lst_buffer);
}

void free_exit(t_shell *shell, int code, char *message)
{ 
	if(message != NULL)
		perror(message);
	free_all(shell);
	ft_free_var(&shell->env);
	clear_history();
	exit(code);
}

/**
 * @brief 
 * @param free_exit aura pour objectif de tout free et 
 * d'exit avec le bon code. pour l'instant j'envoie lst a
 * free mais peut etre qu'il y aura plus tard une plus grosse
 * structure contenant t_list lst et on remplacera le parametre lst
 * plus tard par cette structure.
 * @param ft_free_lst ATTENTION: le pointeur lst n'est pas remis a 
 * NULL apres ft_free_lst, il faudra donc metttre lst = NULL apres 
 * un @param ft_free_lst, pour etre sur de ne plus acceder a lst
 * (mais a priori si free_exit est appele il n'y a pas de probleme)
 */