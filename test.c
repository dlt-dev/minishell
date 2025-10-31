/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoesterl <aoesterl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/30 15:40:27 by aoesterl          #+#    #+#             */
/*   Updated: 2025/10/31 14:09:09 by aoesterl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Header/minishell.h"
#include "unistd.h"
#include "stdio.h"
#include "stdlib.h"


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

/**
 * @brief @param skip_word on parcours le mot jusqu'au \0 ou
 * jusqu'au prochaine espacement, si on rencontre un quotes on
 * rentre dans @param skip_quotes. les quotes skip les caracteres jusqu'au
 * \0 ou jusqu'a la quotes la suivante.
 * @return int 
 */

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

	i = 0;
	flag_quotes = str[i];
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

/**
 * @brief on retient avec flag_quotes le type de quotes qui est apparu. et 
 * on parcours ensuite la chaine jusqu'au prochain quotes suivant ou jusqu'a
 * ce que \0 soit rencontrer
 * @return i: le nombre d'elements dans les qutes qu'il faut skip.
 */

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

/**
 * @brief @param Substr_buffer_full va parcourir le mot et le mettre dans notre buffer 
 * chunker. On continue tant qu'on ne rencontre pas le \0 ou un espace. Toutefois, si on
 * espace entre " ".  ca ne doti pas arrerter le mot. c'est pourquoi @param fill_quotes_buffer
 * va nour permettre de mettre tout ce qu'il y a entre quotes dans un buffer. 
 * 
 * @return 
 */

char *substr_hdle_quotes(char *str, int *i)
{
	t_cb lst_buffer;
	char *p;
	int check_failed;

	if(init_chunk_buffer(&lst_buffer, 10, 2) == ERROR)
		return(NULL);
	check_failed = substr_buffer_full(&lst_buffer, str);
	if(check_failed == ERROR)
		return(free_chunk_buffer(&lst_buffer), NULL);
	*i += check_failed;
	// printf_buffer(lst_buffer);
	p = fusion_all_chunk(&lst_buffer);
	if(p == NULL)
		return(free_chunk_buffer(&lst_buffer), NULL);
	return(p);
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

/**
 * @brief @param count_word_hdle_quotes va parcourir la chaine content
 * de notre node. si un mot est rencontrer on va dans skip word et on fait
 * +1.
 * @param str: Chaine de caractere a split
 */

t_list *split_in_lst(char **tab, t_list *curr_node)
{
	t_list *lst;
	t_list *tmp;
	int i;

	i = 0;
	lst = NULL;
	while(tab[i] != NULL)
	{
		tmp = ft_lstnew(tab[i]);
		if(tmp == NULL)
			return(ft_free_lst(&lst), NULL);
		memcpy(&tmp->flag, &curr_node->flag, sizeof(t_flag));
		ft_lstadd_back(&lst, tmp);
		i++;
	}
	return(lst);
}

int lst_splitted(t_list *curr_node, t_list **ins_lst)
{
	int count_word;
	char **tab;

	count_word = count_word_hdle_quotes(curr_node->content);
	if(count_word > 1)
	{
		tab = word_splitting(curr_node->content, count_word);
		if(tab == NULL)
			return(ERROR);
		*ins_lst = split_in_lst(tab, curr_node);
		if(ins_lst == NULL)
			return(ft_free_split(&tab), ERROR);
		return(CONTINUE);
	}
	return(0);
}


int main()
{ 
    t_list* ins_lst;
    t_list *lst;
    lst = NULL;
    char *a = ft_strndup("a b", 6);
	char *b = ft_strndup("oscar", 5);
	char *c = ft_strndup("papa",  4);
    char *d = ft_strndup("maman",  5);
    fill_in_lst(&lst, a, WORD);
	fill_in_lst(&lst, b, WORD);
	fill_in_lst(&lst, c, WORD);
    lst_splitted(lst, &ins_lst);
    print_str_lst(ins_lst);
}

// int main()
// {
//     int i;

//     i = 0;
// 	t_list *lst;
//     t_list *lst2;
//     t_list *tmp;
//     t_list *tmp1;
// 	lst = NULL;
//     lst2 = NULL;
// 	char *a = ft_strndup("arthur", 6);
// 	char *b = ft_strndup("oscar", 5);
// 	char *c = ft_strndup("papa",  4);
//     char *d = ft_strndup("maman",  5);
//     char *ok1 = ft_strndup("test1", 5);
// 	char *ok2 = ft_strndup("test2", 5);
// 	char *ok3 = ft_strndup("test3", 5);
// 	fill_in_lst(&lst, a, WORD);
// 	fill_in_lst(&lst, b, WORD);
// 	fill_in_lst(&lst, c, WORD);
//     fill_in_lst(&lst, d, WORD);
    
//     fill_in_lst(&lst2, ok1, WORD);
// 	fill_in_lst(&lst2, ok2, WORD);
// 	fill_in_lst(&lst2, ok3, WORD);
//     lst = NULL;
//     tmp = lst;
//     while(i < 2)
//     {
//         tmp1 = tmp;
//         tmp = tmp->next;
//         i++;
//     }
//     printf("%d\n", ft_lst_len(lst2));
//     insert_multi_node(tmp, lst2);
//     del_one_relink(&lst, tmp, tmp1);
// 	// print_str_lst(lst);
// 	ft_free_lst(&lst);
// }
