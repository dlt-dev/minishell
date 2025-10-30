/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdelattr <jdelattr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/09 11:50:13 by aoesterl          #+#    #+#             */
/*   Updated: 2025/10/29 14:06:48 by jdelattr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H
# define STRUCT_H

enum token_type // assigner des token type les redire in ou out???
{
	WORD = 1,
	META = 2,
	PIPE = 3, 
	REDIR,
	QUOTE,
	DOLLAR,
	AFFEC_VAR,
	SINGLE,
	DOUBLE,
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

typedef struct s_flag///// ??? - utilise enum ou type ?
//double definition - flag pourrait etre un int dan lequel on entre va ??
{
	int type;
	int quote;
	int dollar;
	int redir;
	int pipe;
	int affec_var;//?
	int error;//?
}t_flag;

typedef struct s_list
{
	char *content;
	t_flag flag;
	//bool quotted = true / false
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

typedef struct s_var
{
	t_valist *env;
	t_valist *local;
}t_var;

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
	t_var var;
	t_cb lst_buffer;/////////////
	int exit_status;
	
}t_shell;

/**
 * @brief @param t_shell contient @param t_prompt @param rd_line (ce qui est tapé)
 * @param t_var (les va_env et local), @param lst (listes des tokens) et
 * @param exit_status (#?), pour pouvoir tout transporter quand on veut
 * 
 */


#endif