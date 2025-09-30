/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoesterl <aoesterl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/29 17:17:54 by jdelattr          #+#    #+#             */
/*   Updated: 2025/09/30 16:53:09 by aoesterl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

#include <unistd.h> 
#include <stdlib.h>
#include <errno.h>
#include <stdio.h>

#define ERROR -1
#define IS_NOT 0
#define IS 1

// enum token_type
// {
// 	T_WORD //(WORD)
// 	T_NL //(new line)
// 	T_EOF //(end of file)_
// 	T_PIPE
// 	T_REDIR_IN
// 	T_REDIR_OUT
// 	T_
// };

typedef struct s_list
{ 
	char *content;
	int type;
	struct s_list *previous;
	struct s_list *next;
}	t_list;

// utils.c
size_t	ft_strlen(char *str);

// utils_lst.c
t_list	*ft_lstlast(t_list *lst);
t_list	*ft_lstnew(void *content);
void	ft_lstadd_back(t_list **lst, t_list *new);

//util_lexing.c
int is_separator (char c);

#endif