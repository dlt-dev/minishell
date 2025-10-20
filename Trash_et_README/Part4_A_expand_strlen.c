/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Part4_A_expand_strlen.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoesterl <aoesterl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/15 15:15:26 by aoesterl          #+#    #+#             */
/*   Updated: 2025/10/21 00:56:54 by aoesterl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "minishell.h"

// int count_var(t_valist *var,  char *str, int len_name)
// {
// 	int count;

// 	count = 0;
// 	if(var == NULL || str == NULL)
// 		return(0);
// 	while (var != NULL)
// 	{
// 		if (ft_strncmp(str, var->name, var->len_name) == 0)
// 			if(len_name == var->len_name)
// 			{
// 				count = ft_strlen(var->value);
// 				break;
// 			}
// 		var = var->next;
// 	}
// 	return(count);
// }

// int	length_var(t_valist *env, t_valist *local, char *str, int *i)
// {
// 	int count;
// 	int len_name;

// 	count = 0;
// 	len_name = length_name(str);
// 	*i += len_name;
// 	if (len_name == 0)
// 	{ 
// 		count = 1;
// 		return(count);
// 	}
// 	count += count_var(env, str, len_name);
// 	if(count == 0)
// 		count+= count_var(local, str, len_name);
// 	return (count);
// }

// /**
//  * @brief 3 counts sont a distinguer dans le cas d'une expansion de variable:
//  * - Si le $ est suivi d'un nom de variable qui n'existe pas (ex : $prout).
//  * le $prout disparait dans la nouvelle chaine et il n'y a pas de caractere en plus.
//  * Donc count = 0;
//  * - Si le $ est directement suivi d'un caractere qui n'est pas admis dans un "name",
//  * le $ est considere comme tout seul et ne fait pas d'expansion. on garde donc le $,
//  * Donc count = 1;
//  * - Si le nom de variable est valide, le $name est remplace par sa valeur.
//  * Donc count = taille de la value de la variable (name=value).
//  * 
//  * @return int 
//  */

// int handle_dollar(t_shell* shell, char *str, int *i)
// { 
// 	int count;

// 	count = 0;
// 	(*i)++;
// 	if(str[*i] == '?')
// 	{
// 		(*i)++;
// 		count += len_number(shell->exit_status);
// 	}
// 	else
// 		count += length_var(shell->var.env, shell->var.local, &str[*i], i);
// 	return(count);
// }
// /**
//  * @brief @param handle_dollar on compte a partir du $ pour savoir quel
//  * taille fera l'expansion.
//  * si juste apres le $ on a ? : il faut compter la taille de l'exit_code
//  * sinon il s'agira d'une expansion de variable: lenght_var
//  * @param i: dans le meme temps, on envoie i pour savoir combien de caractere
//  * on doit skip dans la chaine analyse.
//  * @return int : lenght de l'expansion
//  */


// int handle_double_quotes(t_shell *shell, char *str, int *i)
// { 
// 	int count;

// 	(*i)++;
// 	count = 1;
// 	while(str[*i] != '\0' && str[*i] != '\"')
// 	{
// 		if(str[*i] == '$')
// 			count += handle_dollar(shell, str, i);
// 		else
// 		{ 
// 			count++;
// 			(*i)++;
// 		}
// 	}
// 	if(str[*i] == '\"')
// 	{
// 		count++;
// 		(*i)++;
// 	}
// 	return(count);
// }

// int	handle_single_quotes(char *str, int *i)
// {
// 	int count;
	
// 	(*i)++;
// 	count = 1;
// 	while (str[*i] != '\0' && str[*i] != '\'')
// 	{
// 		count++;
// 		(*i)++;
// 	}
// 	if(str[*i] == '\'')
// 	{
// 		count++;
// 		(*i)++;		
// 	}
// 	return (count);
// }

// int	count_expand(t_shell *shell, char *str)
// {
// 	int	i;
// 	int	new_str;

// 	i = 0;
// 	new_str = 0;
// 	while (str[i] != '\0')
// 	{
// 		if (str[i] == '\'')
// 			new_str += handle_single_quotes(str, &i);
// 		else if(str[i] == '\"')
// 			new_str += handle_double_quotes(shell, str, &i);
// 		else if (str[i] == '$')
// 			new_str += handle_dollar(shell, str, &i);
// 		else
// 		{
// 			new_str++;
// 			i++;
// 		}
// 	}
// 	return (new_str);
// }
// /**
//  * @brief @param count_expand count le nombre de caractere que contiendra 
//  * la chaine finale apres l'expansion. 
//  * @param i fait defiler la chaine actuelle 
//  * @param new_str variable retourner pour savoir la taille de la chaine finale
//  * @return int 
//  */

 
// int	expand_param(t_shell *shell, t_list *lst)
// {
// 	int i;
// 	if (lst == NULL)
// 		return (ERROR);
// 	while (lst != NULL)
// 	{
// 		if (lst->flag.dollar == DOLLAR)
// 		{
// 			i = count_expand(shell, lst->content);
// 			printf("node :\n%s\nsize du la chaine finale %d\n", lst->content,
// 				i);
// 			printf("taille de %s: %lu\n", getenv("USER"),
// 				strlen(getenv("USER")));
// 		}
// 		lst = lst->next;
// 	}
// 	return (0);
// }
