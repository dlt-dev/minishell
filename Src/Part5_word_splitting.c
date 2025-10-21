/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Part5_word_splitting.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoesterl <aoesterl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/21 17:17:34 by aoesterl          #+#    #+#             */
/*   Updated: 2025/10/21 19:54:49 by aoesterl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


//faire une boucle while sur la liste chainee
//reperer les content qui contiennt des espaces
//split le node->content en char **
//mettre chaque char * dans un node
//supprime l'ancien node et mettre les nodes a l'endroit voulu
// creer un char **pour recup les mots a split


int word_splitting(t_shell *shell, t_list *lst)
{
	t_list *tmp;
	t_list *curr_node;
    t_list *prev_node;
	
    curr_node = lst;
    prev_node = NULL;
	if(lst == NULL)
		return(0);
	



	
} 