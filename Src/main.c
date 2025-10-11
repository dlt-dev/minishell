/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoesterl <aoesterl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/08 14:04:25 by aoesterl          #+#    #+#             */
/*   Updated: 2025/10/11 13:49:54 by aoesterl         ###   ########.fr       */
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

int main()
{ 
	t_list *lst;
	t_prompt prompt;
	char *a;
	a = NULL;
	lst = NULL; 
	while(1)
	{ 
		if(ft_prompt(&prompt) == ERROR)
			return(ERROR);
		readline(prompt.prompt);
	}
}