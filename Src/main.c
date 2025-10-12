/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arthurito <arthurito@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/08 14:04:25 by aoesterl          #+#    #+#             */
/*   Updated: 2025/10/13 00:38:04 by arthurito        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void init_shell(t_shell *sh)
{ 
	*sh = (t_shell){0};
	sh->invite.color_reset = RESET;
	sh->invite.color_user = YELL_PS;
	sh->invite.color_cwd = BLUE_PS;
}
/**
 *	init_shell mets toutes les valeurs a NULL sauf celle qui sont précisé
 */

 
int main()
{ 
	t_shell shell; 
	
	while(1)
	{
		init_shell(&shell);
		if(get_prompt(&shell.invite) == ERROR)
			return(ERROR);
		shell.rd_line = readline(shell.invite.prompt);
		if(shell.rd_line == NULL)
			free_exit(&shell, GEN_ERRNO, NULL);
		if(lexing(shell.rd_line, &shell.lst) == ERROR)
			free_exit(&shell, GEN_ERRNO, NULL);
		// free_all(&shell);
	}
}

