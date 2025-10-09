/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoesterl <aoesterl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/08 14:04:25 by aoesterl          #+#    #+#             */
/*   Updated: 2025/10/09 12:08:52 by aoesterl         ###   ########.fr       */
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
	t_syntax syntax;
	
	lst = NULL; 
	//char * a= ">>     <                 b$$$onjour \"je m'appelle \"michelle";
	//char * a= "     \'jhgasd dasjg awjdg$$$$$KH'  kdshd\"\"\"\"\"\"\"hjhjhjk&";
	char * a= " <<< <<<<<  \"arthur\"\"oscar\"\"papa\"  $var\"jeanne\" arthur ";
	lexing(a, &lst);
	print_str_lst(lst);

}