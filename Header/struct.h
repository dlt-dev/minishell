/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoesterl <aoesterl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/09 11:50:13 by aoesterl          #+#    #+#             */
/*   Updated: 2025/10/11 13:07:15 by aoesterl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H
# define STRUCT_H

enum token_type
{
	WORD, //(WORD)
	META, //(new line)
	PIPE, //(end of file)
	REDIR,
};

typedef struct s_list
{ 
	char *content;
	int type;
	struct s_list *previous;
	struct s_list *next;
}	t_list;

typedef struct s_prompt
{ 
	int pos_cwd;
	char *user;
	char *cwd;
	char *empty;
	char *home;
	char *prompt;

	char *color_user;
	char *color_cwd;
	char *color_reset;
}t_prompt;


// typedef struct s_syntax
// { 
// 	char *blank;
// 	char *ifs;
// 	char *white_space;
// 	char *ctrl_operat;
// 	char *metachar;
// } t_syntax;


#endif