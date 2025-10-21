/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoesterl <aoesterl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/30 15:40:27 by aoesterl          #+#    #+#             */
/*   Updated: 2025/10/22 00:44:36 by aoesterl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Header/minishell.h"
#include "unistd.h"
#include "stdio.h"
#include "stdlib.h"

 

int space_in_content(t_shell *shell, char *str)
{
	int i;
	int flag_quotes;

	i = 0;
	while(str[i] != '\0')
	{
		flag_quotes = 0;
		if(str[i] == '\"' || str[i] == '\'')
		{
			flag_quotes = str[i];
			i++;
			while(str[i] != flag_quotes && str[i] != '\0')
				i++;
			if(str[i] == flag_quotes)
				i++; 
		}
		else
			i++;
		if(is_str(str[i], " \t\n") == IS)
			return(0);
	}
	return(ERROR);
}

int main (int argc, char **argv)
{
	(void)argc;
	t_shell *shell;
	char *str1;
	str1 = "\"dqdzzqd dzd zd d dz ";
	//  "ddzq  \"dqzddqz"
	if(space_in_content(shell, str1) == ERROR)
		printf("ERROR");
	if(space_in_content(shell, str1) == 0)
		printf("we need to manage this");

}


// int main(int argc, char **argv)
// {
// 	char *str2;
	
// 	t_cb lst_buffer;
// 	init_chunk_buffer(&lst_buffer, 200, 2);
// 	cb_append_str(&lst_buffer, argv[1]);
// 	cb_append_str(&lst_buffer, argv[2]);
// 	cb_append_str(&lst_buffer, argv[3]);
// 	cb_append_str(&lst_buffer, argv[4]);

// 	while(lst_buffer.head != NULL)
// 	{
// 		printf("%s\n" , lst_buffer.head->buffer);
// 		lst_buffer.head = lst_buffer.head->next;
// 	}
// 	// printf_buffer(lst_buffer);
// 	// str2 = fusion_all_chunk(&lst_buffer);
	
// 	// printf("%s\n", str2);
// 	// free(str2);
// }