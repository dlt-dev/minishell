/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   part4_B_expand_create.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoesterl <aoesterl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 13:25:16 by aoesterl          #+#    #+#             */
/*   Updated: 2025/10/17 00:03:59 by aoesterl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"










// int	expand_param(t_shell *shell, t_list *lst)
// {
// 	int i;
// 	if (lst == NULL)
// 		return (ERROR);
// 	while (lst != NULL)
// 	{
// 		if (lst->flag.dollar == DOLLAR)
// 		{
// 			i = count_expansion(shell, lst->content);
// 			// printf("node :\n%s\nsize du la chaine finale %d\n", lst->content,
// 			// 	i);
// 			// printf("taille de %s: %lu\n", getenv("USER"),
// 			// 	strlen(getenv("USER")));
// 			create_expansion(); 
// 		}
// 		lst = lst->next;
// 	}
// 	return (0);
// }