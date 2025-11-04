/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoesterl <aoesterl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/30 15:40:27 by aoesterl          #+#    #+#             */
/*   Updated: 2025/11/04 00:02:38 by aoesterl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Header/minishell.h"
#include "unistd.h"
#include "stdio.h"
#include "stdlib.h"


int checker_close_quotes(char *str)
{
    int i;
    char flag_quotes;
 
    flag_quotes = 0;
    i = 0;
    while(str[i] != '\0')
    {
        if(str[i] == '\"' || str[i] == '\'')
        {
            flag_quotes = str[i];
            i++;
            while(str[i] != flag_quotes && str[i] != '\0')
                i++;
            if(str[i] == flag_quotes)
            {
                i++;
                flag_quotes = 0;
            }
        }
        else
            i++;    
    }
    if(flag_quotes == '\'' || flag_quotes == '\"')
        return(ERROR);
    return(0);
} 


int main (int argc, char **argv)
{
    char *str = "\"argv[1]\"";
    if(checker_close_quotes(str) == ERROR)
        return(printf("oulalalalal"));
    if(checker_close_quotes(str) == 0)
        return(printf("all good"));
}

// int main()
// { 
//     t_list* ins_lst;
//     t_list *lst;
//     lst = NULL;
//     char *a = ft_strndup("a b", 6);
// 	char *b = ft_strndup("oscar", 5);
// 	char *c = ft_strndup("papa",  4);
//     char *d = ft_strndup("maman",  5);
//     fill_in_lst(&lst, a, WORD);
// 	fill_in_lst(&lst, b, WORD);
// 	fill_in_lst(&lst, c, WORD);
//     delete_quotes(lst, &ins_lst);
//     print_str_lst(ins_lst);
// }

// int main()
// {
//     int i;

//     i = 0;
// 	t_list *lst;
//     t_list *lst2;
//     t_list *tmp;
//     t_list *tmp1;
// 	lst = NULL;
//     lst2 = NULL;
// 	char *a = ft_strndup("arthur", 6);
// 	char *b = ft_strndup("oscar", 5);
// 	char *c = ft_strndup("papa",  4);
//     char *d = ft_strndup("maman",  5);
//     char *ok1 = ft_strndup("test1", 5);
// 	char *ok2 = ft_strndup("test2", 5);
// 	char *ok3 = ft_strndup("test3", 5);
// 	fill_in_lst(&lst, a, WORD);
// 	fill_in_lst(&lst, b, WORD);
// 	fill_in_lst(&lst, c, WORD);
//     fill_in_lst(&lst, d, WORD);
    
//     fill_in_lst(&lst2, ok1, WORD);
// 	fill_in_lst(&lst2, ok2, WORD);
// 	fill_in_lst(&lst2, ok3, WORD);
//     lst = NULL;
//     tmp = lst;
//     while(i < 2)
//     {
//         tmp1 = tmp;
//         tmp = tmp->next;
//         i++;
//     }
//     printf("%d\n", ft_lst_len(lst2));
//     insert_multi_node(tmp, lst2);
//     del_one_relink(&lst, tmp, tmp1);
// 	// print_str_lst(lst);
// 	ft_free_lst(&lst);
// }
