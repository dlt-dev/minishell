/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoesterl <aoesterl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/30 15:40:27 by aoesterl          #+#    #+#             */
/*   Updated: 2025/10/16 17:06:26 by aoesterl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Header/minishell.h"
#include "unistd.h"
#include "stdio.h"
#include "stdlib.h"

// #define YELL_PS "\033[33;1m"
// #define BLUE_PS "\033[34;1m"

// void lst_del_one(t_list *node)
// {
// 	if(node == NULL)
// 		return;
// 	if(node->content != NULL)
// 		free(node->content);
// 	free(node);
// } 

\
int length_name(char *name)
{ 
	int i;

	i = 0;
	if((name[0] < 'A' || name[0] > 'Z') && 
		(name[0] < 'a' || name[0] > 'z') && (name[0] != '_'))
			return(0);
	while(name[i] != '\0')
	{
		if((name[i] < '0' || name[i] > '9') &&
		(name[i] < 'A' || name[i] > 'Z') && 
		(name[i] < 'a' || name[i] > 'z') && (name[i] != '_'))
			break;
		i++;
	} 
	return(i);
}

int main(int argc, char **argv)
{ 
	(void)argc;
	printf("%d\n", length_name(argv[1]));




	
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