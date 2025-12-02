/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdelattr <jdelattr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/09 11:50:13 by aoesterl          #+#    #+#             */
/*   Updated: 2025/12/02 13:03:36 by jdelattr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H
# define STRUCT_H

# include "exec_struct.h"
# include "minishell.h"
# include <signal.h>
# include <stdlib.h>
# define _POSIX_C_SOURCE 200809L

enum					e_token_type
{
	WORD = 1,
	META = 2,
	QUOTE = 3,
	DOLLAR = 4,
	FILES = 5,
	CMD = 6,
	DELIMITOR = 7,
	PIPE = 8,
	REDIR = 9,
	HEREDOC = 10,
	INFILE = 11,
	OUTFILE = 12,
	OUTFILE_APPEND = 13,
};

typedef struct s_flag
{
	int					type;
	int					quote;
	int					dollar;
	int					pipe;
	int					word_type;
	int					redir;
	int					redir_type;
}						t_flag;

typedef struct s_list
{
	char				*content;
	t_flag				flag;
	struct s_list		*next;
}						t_list;

typedef struct s_prompt
{
	char				*user;
	char				*cwd;
	char				*prompt;
	char				*color_exit;
	char				*color_user;
	char				*color_cwd;
	char				*color_reset;
}						t_prompt;

typedef struct s_valist
{
	char				*name;
	char				*value;
	int					len_name;
	struct s_valist		*next;
}						t_valist;

typedef struct s_shell
{
	t_prompt			invite;
	char				*rd_line;
	t_list				*lst;
	t_exec				*cmd_lst;
	t_valist			*env;
	int					exit_status;
	int					prev_fd;
	struct sigaction	sigint;
	struct sigaction	sigquit;
}						t_shell;

/**
 * @brief @param t_shell contient @param t_prompt
 * @param rd_line (ce qui est tapé)
 * @param t_var (les va_env et local), @param lst (listes des tokens) et
 * @param exit_status (#?), pour pouvoir tout transporter quand on veut
 */

#endif
