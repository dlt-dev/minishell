/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_free.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdelattr <jdelattr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/21 18:51:00 by aoesterl          #+#    #+#             */
/*   Updated: 2025/11/25 21:15:03 by jdelattr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_free_lst(t_list **lst)
{
	t_list	*tmp;

	if (*lst == NULL)
		return ;
	tmp = *lst;
	while (*lst != NULL)
	{
		tmp = (*lst)->next;
		if ((*lst)->content != NULL)
		{
			free((*lst)->content);
			(*lst)->content = NULL;
		}
		free(*lst);
		*lst = tmp;
	}
}
void	free_redir_list(t_redir **head)
{
	t_redir	*cur;
	t_redir	*next;

	if (!head || !*head)
		return ;
	cur = *head;
	while (cur)
	{
		next = cur->next;
		if (cur->filename)
			free(cur->filename);
		free(cur);
		cur = next;
	}
	*head = NULL;
}

void	free_exec_lst(t_exec **head)
{
	t_exec	*cur;
	t_exec	*next;
	int		i;

	if (!head || !*head)
		return ;
	cur = *head;
	while (cur)
	{
		next = cur->next;
		if (cur->cmds)
		{
			i = 0;
			while (cur->cmds[i])
			{
				free(cur->cmds[i]);
				i++;
			}
			free(cur->cmds);
		}
		free_redir_list(&cur->redir);
		free(cur);
		cur = next;
	}
	*head = NULL;
}
// GOODJOB

void	ft_free_str(char **str)
{
	if (*str == NULL)
		return ;
	free(*str);
	*str = NULL;
}

void	ft_free_split(char ***tab)
{
	int i;

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