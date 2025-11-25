/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PartX_print_execution.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdelattr <jdelattr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/20 14:02:40 by aoesterl          #+#    #+#             */
/*   Updated: 2025/11/25 21:21:14 by jdelattr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_char_tab(char **tab) // TEST
{
	int i;

	i = 0;
	if (!tab)
	{
		printf("(null)\n");
		return ;
	}
	printf("mon char **\n");
	while (tab[i])
	{
		printf("%s\n", tab[i]);
		i++;
	}
}

void	test_print_fd(t_exec *cmd_list) // TEST
{
	int i;

	i = 0;
	while (cmd_list != NULL)
	{
		printf("cmd[%d] ->> cmd fd_in = %d | fd_out = %d\n", i, cmd_list->fd_in,
			cmd_list->fd_out);
		i++;
		cmd_list = cmd_list->next;
	}
}
