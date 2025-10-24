/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Part4_1expand_main.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoesterl <aoesterl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/20 12:06:17 by aoesterl          #+#    #+#             */
/*   Updated: 2025/10/24 19:29:06 by aoesterl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "minishell.h"

static int handle_meanings(t_shell *shell, t_cb* lst_buffer, char *str)
{
    int  i;
    int check_failed;

    i = 0; 
    check_failed = 0;
    if (str[i] == '\'')
        check_failed = handle_single_quotes(lst_buffer, &str[i]);
    else if(str[i] == '\"')
        check_failed = handle_double_quotes(shell, lst_buffer, &str[i]);
    else if (str[i] == '$')
        check_failed = handle_dollar(shell, lst_buffer, &str[i]);
    if(check_failed == ERROR)
        return(ERROR);
    i += check_failed;
    return(i);
}

static int  fill_expand_in_buffer(t_shell *shell, t_cb *lst_buffer, char *str)
{
	int	i;
    int check_failed;
    
	i = 0;
	while (str[i] != '\0')
	{
        check_failed = handle_meanings(shell, lst_buffer, &str[i]);
        if(check_failed == ERROR)
            return(ERROR);
        else if(check_failed == 0)
        {
            if(cb_append_char(lst_buffer, str[i]) == ERROR)
                return(ERROR);
            i++;
        }
        i+= check_failed;
	}
	return (0);
}

static char *create_expand_str(t_shell *shell, t_cb *lst_buffer, char *str)
{
    char *new_str;
    
    new_str = NULL;
    if(init_chunk_buffer(lst_buffer, 10, 2) == ERROR)
        return(NULL);
    if(fill_expand_in_buffer(shell, lst_buffer, str) == ERROR)
        return(NULL);
    new_str = fusion_all_chunk(lst_buffer);
    if(new_str == NULL)
        return(NULL);
    return(new_str);
}


static t_list *create_expand_node(t_shell *shell, t_list *curr_node)
{
    char *new_str;
    t_list *new_node;
    
    new_str = create_expand_str(shell, &shell->lst_buffer, curr_node->content);
    if(new_str == NULL)
        return(NULL);
    new_node = ft_lstnew(new_str);
    new_node->flag.type = WORD;
    new_node->flag.dollar = DOLLAR;
    if(new_node == NULL)
            return(free(new_str), NULL);
    return(new_node);
}
 
int	expand_shell_param(t_shell *shell, t_list *lst)
{
    t_list *tmp;
    t_list *curr_node;
    t_list *prev_node;

    curr_node = lst;
    prev_node = NULL;
	if (lst == NULL)
		return (0);
	while (curr_node != NULL)
	{
		if (curr_node->flag.dollar == DOLLAR)
        {
            tmp = create_expand_node(shell, curr_node);
            if(tmp == NULL)
                return(ERROR);
            node_exchange(&shell->lst, curr_node, prev_node, tmp);
            curr_node = tmp;
        }
		prev_node = curr_node;
        curr_node = curr_node->next;
	}
	return (0);
}
