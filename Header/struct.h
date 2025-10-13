/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoesterl <aoesterl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/09 11:50:13 by aoesterl          #+#    #+#             */
/*   Updated: 2025/10/14 00:52:14 by aoesterl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H
# define STRUCT_H

enum token_type
{
	WORD = 1,
	META,
	PIPE, 
	REDIR,
	QUOTES,
};

typedef struct s_list
{ 
	char *content;
	int type;
	int quotes;
	struct s_list *previous;
	struct s_list *next;
}	t_list;

typedef struct s_prompt
{ 
	char *user;
	char *cwd;
	char *prompt;

	char *color_user;
	char *color_cwd;
	char *color_reset;
}t_prompt;

typedef struct s_var
{
	t_list *env;
	t_list *local;
}t_var;

typedef struct s_shell
{
	t_prompt invite;
	t_list *lst;
	char *rd_line;
	t_var var;
}t_shell;

#endif