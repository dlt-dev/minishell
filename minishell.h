/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdelattr <jdelattr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/29 17:17:54 by jdelattr          #+#    #+#             */
/*   Updated: 2025/10/01 19:16:35 by jdelattr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

#include <unistd.h> 
#include <stdlib.h>
#include <errno.h>
#include <stdio.h>

#define GEN_ERRNO 1
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
/* 
WORD (commandes, arguments, fichiers)

PIPE (|)

REDIR_IN (<)

REDIR_OUT (>)

APPEND (>>)

HEREDOC (<<) */

typedef struct s_list
{ 
	char *content;
	int type;
	struct s_list *previous;
	struct s_list *next;
}	t_list;

//free_exit
void free_exit(t_list *lst, int code, char *message);
void ft_free_lst(t_list *lst);


//malloc_lexing.c
char *ft_strndup(char *str, int size);

//utils_lexing.c
int is_spaces (char c);
int is_separator(char c);
int is_metachar(char c);
int is_quote(char c);


// utils_lst.c
t_list	*ft_lstnew(void *content);
void	ft_lstadd_back(t_list **lst, t_list *new);
int fill_in_lst(t_list **lst, char *content);
void print_str_lst(t_list *lst);

// utils.c
size_t	ft_strlen(char *str);
char	*ft_strdup(char *s);

#endif

