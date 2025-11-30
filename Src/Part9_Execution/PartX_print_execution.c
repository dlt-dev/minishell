/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PartX_print_execution.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoesterl <aoesterl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/20 14:02:40 by aoesterl          #+#    #+#             */
/*   Updated: 2025/11/30 04:10:29 by aoesterl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_char_tab(char **tab)
{
	int	i;

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

void	test_print_fd(t_exec *cmd_list)
{
	int	i;

	i = 0;
	while (cmd_list != NULL)
	{
		printf("cmd[%d] ->> cmd fd_in = %d | fd_out = %d\n", i, cmd_list->fd_in,
			cmd_list->fd_out);
		i++;
		cmd_list = cmd_list->next;
	}
}

void failed_exec_message (char *cmd, char * message)
{
	write_str_fd("minishell: ", 2);
	write_str_fd(cmd, 2);
	write_str_fd(message, 2);
	
}
