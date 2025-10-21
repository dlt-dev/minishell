/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Part5_word_splitting.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoesterl <aoesterl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/21 17:17:34 by aoesterl          #+#    #+#             */
/*   Updated: 2025/10/22 01:13:07 by aoesterl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


//faire une boucle while sur la liste chainee
//reperer les content qui contiennt des espaces
//split le node->content en char **
//mettre chaque char * dans un node
//supprime l'ancien node et mettre les nodes a l'endroit voulu
// creer un char **pour recup les mots a split







int count_space_in_content(t_shell *shell, char *str)
{
	int i;
	int flag_quotes;
	int count;

	i = 0;
	while(str[i] != '\0')
	{
		flag_quotes = 0;
		if(str[i] == '\"' || str[i] == '\'')
		{
			flag_quotes = str[i];
			i++;
			while(str[i] != flag_quotes && str[i] != '\0')
				i++;
			if(str[i] == flag_quotes)
				i++; 
		}
		else
			i++;
		if(is_str(str[i], " \t\n") == IS)
			return(0);
	}
	return(ERROR);
}


int create_str(t_shell *shell, t_cb *lst_buffer)
{
	
	
}

int create_node(t_shell *shell, char *str)
{
	int i;
	 
	i = 0
	while( )
	if(init_chunk_buffer(&shell->lst_buffer, 10, 2) == ERROR);
		return(ERROR);
	create_str(shell, &shell->lst_buffer);
	
	
}



int word_splitting(t_shell *shell, t_list *lst)
{
	t_list *tmp;
	t_list *curr_node;
    t_list *prev_node;
	
    curr_node = lst;
    prev_node = NULL;
	if(lst == NULL)
		return(0);
	while(curr_node != NULL)
	{
		if(space_in_content(shell, curr_node->content) == 0);
			create_node(shell, curr_node->content)



		
	}



	
} 