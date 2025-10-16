/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoesterl <aoesterl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/30 15:40:27 by aoesterl          #+#    #+#             */
/*   Updated: 2025/10/16 23:50:40 by aoesterl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Header/minishell.h"
#include "unistd.h"
#include "stdio.h"
#include "stdlib.h"

// #define YELL_PS "\033[33;1m"
// #define BLUE_PS "\033[34;1m"

int len_number (int nb)
{
	int i;

	i = 0;
	if(nb < 0)
		return(ERROR);
	if(nb == 0)
		return(1);
	while(nb > 0)
	{
		nb = nb/10;
		i++;
	}
	return(i);
}

int main(int argc, char **argv)
{ 
	printf("%d", len_number(125));
}

// void change (t_list *lst)
// {
// 	int i;
// 	t_list *tmp;

// 	tmp = lst;
// 	i = 0;
// 	while(i < 3 && lst != NULL)
// 	{ 
// 		tmp = tmp->next;
// 		i++;
// 	}
// 	delone_relink_chain(&lst, tmp);
// }

// int  main()
// {
// 	t_list *lst = NULL;
// 	fill_in_lst(&lst, ft_strdup("bonjour"), 0);
// 	fill_in_lst(&lst, ft_strdup("je"), 0);
// 	fill_in_lst(&lst, ft_strdup("suis"), 0);
// 	fill_in_lst(&lst, ft_strdup("arthur"), 0);
// 	fill_in_lst(&lst, ft_strdup("aurevoir"), 0);
// 	change(lst);
// 	print_str_lst(lst);
// }