/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arthurito <arthurito@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/08 14:04:25 by aoesterl          #+#    #+#             */
/*   Updated: 2025/10/12 23:33:43 by arthurito        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// void init_var(t_list **lst, t_syntax *syntax)
// { 
// 	*lst = NULL;
// 	syntax->blank= " \t";
// 	syntax->ifs = " \t\n";
// 	syntax->white_space= " \t\n\v\f\r";
// 	syntax->metachar=" \t\n|<>";
// }

void init_shell(t_shell *sh)
{ 
	*sh = (t_shell){0};
	sh->invite.color_reset = RESET;
	sh->invite.color_user = YELL_PS;
	sh->invite.color_cwd = BLUE_PS;
	sh->invite.empty = "\0";
}
/**
 *	init_shell mets toutes les valeurs a NULL sauf celle qui sont précisé
 */

 
int main()
{ 
	t_shell sh; 
	
	while(1)
	{
		init_shell(&sh);
		if(get_prompt(&sh.invite) == ERROR)
			return(ERROR);
		sh.rd_line = readline(sh.invite.prompt);
		lexing(sh.rd_line, &sh.lst);
		refresh(&sh);
	}
}