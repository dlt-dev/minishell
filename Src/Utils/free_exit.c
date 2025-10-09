/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_exit.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoesterl <aoesterl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/30 17:44:28 by aoesterl          #+#    #+#             */
/*   Updated: 2025/09/30 18:58:23 by aoesterl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void ft_free_lst(t_list *lst)
{
	t_list *tmp;
	
	tmp = lst;  
	if(lst == NULL)
		return;
	while(lst != NULL)
	{
		tmp = (lst)->next;
		free((lst)->content);
		free(lst);
		lst = tmp; 
	}
}
//GOODJOB

void free_all(t_list *lst)
{ 
	ft_free_lst(lst);
}

void free_exit(t_list *lst, int code, char *message)
{ 
	perror(message);
	free_all(lst);
	lst = NULL; // par forcement necessaire ici, mais petit exemple
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