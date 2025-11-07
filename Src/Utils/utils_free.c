/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_free.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoesterl <aoesterl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/21 18:51:00 by aoesterl          #+#    #+#             */
/*   Updated: 2025/10/22 18:46:01 by aoesterl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void ft_free_lst(t_list **lst)
{
	t_list *tmp;
	
	if(*lst == NULL)
		return;
	tmp = *lst;
	while(*lst != NULL)
	{
		tmp = (*lst)->next;
		if((*lst)->content != NULL)
		{
			free((*lst)->content);
			(*lst)->content = NULL;
		}
		free(*lst);
		*lst = tmp; 
	}
}
//GOODJOB

void ft_free_str(char **str)
{
	if(*str == NULL)
		return;
	free(*str);
	*str = NULL; 
}

void	ft_free_split(char ***tab)
{
	int	i;

	i = 0;
	if (*tab == NULL)
		return ;
	while ((*tab)[i] != NULL)
	{
		free((*tab)[i]);
		i++;
	}
	free(*tab);
	*tab = NULL;
}