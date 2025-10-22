/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Part5_word_splitting.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoesterl <aoesterl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/21 17:17:34 by aoesterl          #+#    #+#             */
/*   Updated: 2025/10/22 17:59:09 by aoesterl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


//faire une boucle while sur la liste chainee
//reperer les content qui contiennt des espaces
//split le node->content en char **
//mettre chaque char * dans un node
//supprime l'ancien node et mettre les nodes a l'endroit voulu
// creer un char **pour recup les mots a split





int skip_quotes(char *str)
{
	int flag_quotes;
	int i;

	i = 0;
	flag_quotes = str[i];
	i++;
	while(str[i] != flag_quotes && str[i] != '\0')
		i++;
	if(str[i] == flag_quotes)
		i++;
	return(i);
}

int skip_word(char *str)
{
	int  i;
	i = 0;
	while(is_char_in_str(str[i], " \t\n") == IS_NOT && str[i] != '\0')
	{
		if(str[i] == '\"' || str[i] == '\'')
			i += skip_quotes(&str[i]);
		else
			i++;
	}
	return(i);
}

int count_word_hdle_quotes(char *str)
{
	int i;
	int count;

	i = 0;
	count = 0;
	while(str[i] != '\0')
	{
		while(is_char_in_str(str[i], " \t\n") == IS && str[i] != '\0')
			i++;
		if(str[i] != '\0')
		{
			i += skip_word(&str[i]);
			count += 1;
		}
	}
	return(count);
}

int fill_quotes_in_buffer(t_cb *lst_buffer, char *str)
{
	int i;
	int flag_quotes;

	flag_quotes = str[i];
	i = 0;
	if(cb_append_char(lst_buffer, str[i]) == ERROR)
		return(ERROR);
	i++;
	while(str[i] != flag_quotes && str[i] != '\0')
	{
		if(cb_append_char(lst_buffer, str[i]) == ERROR)
			return(ERROR);
		i++;
	}
	if(str[i] == flag_quotes)
	{
		if(cb_append_char(lst_buffer, str[i]) == ERROR)
			return(ERROR);
		i++;
	}
	return(i);
}

int substr_buffer_full(t_cb *lst_buffer, char *str)
{
	int i;
	int check_failed;
	
	i = 0;
	while(is_char_in_str(str[i], " \t\n") == IS_NOT && str[i] != '\0')
	{
		if(str[i] == '\"' || str[i] == '\'')
		{
			check_failed = fill_quotes_in_buffer(lst_buffer, &str[i]);
			if(check_failed == ERROR)
				return(ERROR);
			i += check_failed;
		}
		else
		{
			if(cb_append_char(lst_buffer, str[i]) == ERROR)
				return(ERROR);
			i++;
		}
	}
	return(i);
}

char *substr_hdle_quotes(char *str, int *i)
{
	t_cb lst_buffer;
	char *str;
	int check_failed;

	if(init_chunk_buffer(&lst_buffer, 10, 2) == ERROR)
		return(NULL);
	check_failed = substr_buffer_full(&lst_buffer, str);
	if(check_failed == ERROR)
		return(free_chunk_buffer(&lst_buffer), NULL);
	*i += check_failed;
	str = fusion_all_chunk(&lst_buffer);
	if(str == NULL)
		return(free_chunk_buffer(&lst_buffer), NULL);
	return(str);
}


char **word_splitting(char *str, int count_word)
{
	char **tab;
	int i;
	int j;
	
	i = 0;
	j = 0;
	tab = malloc(sizeof(char *) *(count_word + 1));
	if(tab == NULL)
		return(NULL);
	while(str[i] != '\0')
	{
		while(is_char_in_str(str[i], " \t\n") == IS && str[i] != '\0')
			i++;
		if(str[i] != '\0')
		{
			tab[j] = substr_hdle_quotes(&str[i], &i);
			if(tab[j] == NULL)
				return(ft_free_split(&tab), NULL);
			j++;
		}
	}
	tab[j] = NULL;
	return(tab);
}

t_list *put_tab_in_lst(char **tab)
{
	t_list *lst;
	int i;

	i = 0;
	lst = NULL;
	while(tab[i] != NULL)
	{
		if(fill_in_lst(lst, tab[i], WORD) == ERROR)
			return(ft_free_lst(lst), ERROR);
		i++;
	}
	return(lst);
}

void connect_multi_node(t_list **main_lst, t_list *lst)
{
	if(*main)

}

void del_one_link_lst(t_list **lst)

int split_param(t_shell *shell, t_list *lst)
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
		if(count_word_hdle_quotes(shell, curr_node->content) == 0);
			create_node(shell, curr_node->content)



		
	}



	
} 