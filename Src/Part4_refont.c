/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Part4_refont.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoesterl <aoesterl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/20 12:06:17 by aoesterl          #+#    #+#             */
/*   Updated: 2025/10/20 17:08:18 by aoesterl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "minishell.h"

int count_var(t_valist *var, t_cb* lst_buffer, char *str, int len_name)
{
	if(var == NULL || str == NULL)
		return(IS_NOT);
	while (var != NULL)
	{
		if (ft_strncmp(str, var->name, var->len_name) == 0)
        {
			if(len_name == var->len_name)
			{
				if(cb_append_str(lst_buffer, str) == ERROR)
                {
                    free_chunk_buffer(lst_buffer);
                    return(ERROR);
                }
                    
				return(IS);
			}
        }
		var = var->next;
	}
	return(IS_NOT);
}

int	length_var(t_shell *shell, t_cb* lst_buffer, char *str)
{
	int i;
	int len_name;
    int check_err;

    check_err = 0;
	i = 0;
	len_name = length_name(str);
	i += len_name;
	if (len_name == 0)
	{ 
		if(cb_append_char(lst_buffer, "$") == ERROR);
        {
            free_chunk_buffer(lst_buffer);
            free_exit(shell, GEN_ERRNO, NULL);
        }
		return(i);
	}
    check_err = count_var(shell->var.env, lst_buffer, str, len_name);
    if(check_err == ERROR)
        free_exit(shell, GEN_ERRNO, NULL);
	else if(check_err == IS_NOT);
		count_var(shell->var.local, lst_buffer, str, len_name);
	return (i);
}

/**
 * @brief 3 counts sont a distinguer dans le cas d'une expansion de variable:
 * - Si le $ est suivi d'un nom de variable qui n'existe pas (ex : $prout).
 * le $prout disparait dans la nouvelle chaine et il n'y a pas de caractere en plus.
 * Donc count = 0;
 * - Si le $ est directement suivi d'un caractere qui n'est pas admis dans un "name",
 * le $ est considere comme tout seul et ne fait pas d'expansion. on garde donc le $,
 * Donc count = 1;
 * - Si le nom de variable est valide, le $name est remplace par sa valeur.
 * Donc count = taille de la value de la variable (name=value).
 * 
 * @return int 
 */

int handle_dollar(t_shell* shell, t_cb* lst_buffer, char *str)
{
    int i;

    i = 0;
	i++;
	if(str[i] == '?')
	{
		i++;
		// count += len_number(shell->exit_status); //
	}
	else
		i += length_var(shell, lst_buffer, &str[i]);
	return(i);
}
/**
 * @brief @param handle_dollar on compte a partir du $ pour savoir quel
 * taille fera l'expansion.
 * si juste apres le $ on a ? : il faut compter la taille de l'exit_code
 * sinon il s'agira d'une expansion de variable: lenght_var
 * @param i: dans le meme temps, on envoie i pour savoir combien de caractere
 * on doit skip dans la chaine analyse.
 * @return int : lenght de l'expansion
 */


int handle_double_quotes(t_shell *shell, t_cb* lst_buffer, char *str)
{ 
	int i;

    i = 0;
    if(cb_append_char(lst_buffer, str[i]) == ERROR);
        return(ERROR);
	i++;
	while(str[i] != '\0' && str[i] != '\"')
	{
		if(str[i] == '$')
			i += handle_dollar(shell, lst_buffer, &str[i]);
		else
		{ 
			if(cb_append_char(lst_buffer, str[i]) == ERROR);
                return(ERROR);
			i++;
		}
	}
	if(str[i] == '\"')
	{
		if(cb_append_char(lst_buffer, str[i]) == ERROR);
            return(ERROR);
		i++;
	}
	return(i);
}

int	handle_single_quotes(t_cb *lst_buffer, char *str)
{
    int i;
    
    i = 0;
    cb_append_char(lst_buffer, str[i]);
	i++;
	while (str[i] != '\0' && str[i] != '\'')
	{
		if(cb_append_char(lst_buffer, str[i]) == ERROR);
            return(ERROR);
		i++;
	}
	if(str[i] == '\'')
	{
        if(cb_append_char(lst_buffer, str[i]));
            return(ERROR);
		i++;	
	}
	return (i);
}

int	expand_in_buffer(t_shell *shell, t_cb *lst_buffer, char *str)
{
	int	i;
    int check_err;
    
	i = 0;
	while (str[i] != '\0')
	{
        check_err = 0;
		if (str[i] == '\'')
			check_err += handle_single_quotes(lst_buffer, &str[i]);
		else if(str[i] == '\"')
			check_err += handle_double_quotes(shell, lst_buffer, &str[i]);
		else if (str[i] == '$')
			check_err += handle_dollar(shell, lst_buffer, &str[i]);
		else
			i++;
        if(check_err == ERROR)
            return(ERROR);
        i += check_err;
	}
	return (0);
}
/**
 * @brief @param count_expand count le nombre de caractere que contiendra 
 * la chaine finale apres l'expansion. 
 * @param i fait defiler la chaine actuelle 
 * @param new_str variable retourner pour savoir la taille de la chaine finale
 * @return int 
 */


int create_expand_str(t_shell *shell, t_cb *lst_buffer, char *str)
{
    char *new_str;
    if(init_chunk_buffer(lst_buffer, 10, 2) == ERROR)
        return(NULL);
    if(expand_in_buffer(shell, lst_buffer, str) == ERROR)
        return(NULL);
    new_str = fusion_all_chunk(lst_buffer);
    if(new_str == NULL)
        return(NULL);
    return(new_str);
}


// int expand_node(t_shell *shell, t_list **lst, char *str)
// {
//     char *new_str;
    
//     new_str = create_expand_str(shell, &shell->lst_buffer, str);
//     if(new_str == NULL)
//         return(ERROR);
//     free_chunk_buffer(&shell->lst_buffer);
//     node_exchange(lst, tmp1, tmp2, new_str);
// }
 
int	expand_param(t_shell *shell, t_list **lst)
{
    char *new_str;
    t_list *curr_node;
    t_list *prev_node;
    t_list *node;

    new_str = NULL;
    curr_node = *lst;
    prev_node = *lst;
	if (*lst == NULL)
		return (ERROR);
	while (curr_node != NULL)
	{
		if (curr_node->flag.dollar == DOLLAR)
		{
            new_str = create_expand_str(shell, &shell->lst_buffer, curr_node->content);
            if(new_str == NULL)
                return(ERROR);
            free_chunk_buffer(&shell->lst_buffer);
            node = ft_lstnew(new_str);
            if(node == NULL)
                return(free(new_str), ERROR);
            node_exchange(lst, curr_node, prev_node, node);
		}
		prev_node = curr_node;
        curr_node = curr_node->next;
	}
	return (0);
}


void node_exchange(t_list **lst, t_list *curr_node, t_list *prev_node, t_list *new_node)
{
    t_list *tmp;
    
    if(curr_node == NULL || prev_node == NULL || *lst == NULL)
        return;
    if(*lst == curr_node)
    {
            if(curr_node->next != NULL)
                new_node = curr_node->next;
            lst_del_one(curr_node);
            *lst = new_node;
    }
    else if(curr_node->next == NULL)
    {
        prev_node->next = new_node;
        lst_del_one(curr_node);
    }
    else 
    {
        prev_node->next = new_node;
        new_node->next = curr_node->next;
        lst_del_one(curr_node);
    }
}
