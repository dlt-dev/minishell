/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoesterl <aoesterl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/09 11:50:13 by aoesterl          #+#    #+#             */
/*   Updated: 2025/11/04 12:50:39 by aoesterl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H
# define STRUCT_H

#include "exec_struct.h"

enum	e_token_type
{
	//type de token
	WORD = 1,
	META = 2,
	
	//special character in WORD
	QUOTE = 3,
	DOLLAR = 4,

	// type de word
	FILES = 5,
	CMD = 6,
	DELIMITOR = 7,
	
	//type de META
	PIPE = 8,
	REDIR = 9,
	
	//type de redirection
	HEREDOC = 10,
	INFILE = 11,
	OUTFILE = 12,
	OUTFILE_APPEND = 13,
	
};



typedef struct s_buffer
{ 
	char *buffer;
	size_t length;
	size_t capacity;
	struct s_buffer *next;
}t_buffer;

typedef struct s_ptr_buffer
{
	t_buffer *head;
	t_buffer *tail;
	size_t capacity;
	size_t total_len;
	int factor;
}t_cb;

/**
 * @brief @param buffer_et_lst_buffer sont des structures de utils_chunk_buffer.
 * Ce sont tous les éléments pour faire un malloc sans avoir besoin de compter.
 */

typedef struct s_flag
{ 
	int type;
	int quote;
	int dollar;
	int pipe;
	int word_type;
	int redir;
	int redir_type;
}t_flag;

typedef struct s_list
{
	char *content;
	t_flag flag;
	struct s_list *next;
}t_list;

typedef struct s_prompt
{ 
	char *user;
	char *cwd;
	char *prompt;

	char *color_user;
	char *color_cwd;
	char *color_reset;
}t_prompt;

typedef struct s_valist
{
	char *name;
	char *value;
	int len_name;
	struct s_valist *next;
}t_valist;

// typedef struct s_var
// {
// 	t_valist *env;
// }t_var;

/**
 * @brief @param t_var contient 2 listes: Une liste des variables d'envirronements
 * et une liste des variables locales au shell. @param t_valist c'est la structure
 * de chacune des listes de variable: le nom, la valeur et la longueur du nom de
 * la variable.
 */
 
typedef struct s_shell
{
	t_prompt invite;
	char *rd_line;
	t_list *lst;
	t_exec *cmd_lst; // la liste de commandes + redir a envoyer a l'execution
	t_valist *env;
	t_cb lst_buffer;
	int exit_status;
	
}t_shell;

/**
 * @brief @param t_shell contient @param t_prompt @param rd_line (ce qui est tapé)
 * @param t_var (les va_env et local), @param lst (listes des tokens) et
 * @param exit_status (#?), pour pouvoir tout transporter quand on veut
 * 
 */


#endif