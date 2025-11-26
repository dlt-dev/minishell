/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_struct.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoesterl <aoesterl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/26 17:06:42 by jdelattr          #+#    #+#             */
/*   Updated: 2025/11/26 17:37:55 by aoesterl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_STRUCT_H
# define EXEC_STRUCT_H

typedef struct s_pipex
{
	char			**cmd1;
	char			**cmd2;
}					t_pipex;

typedef struct s_redir
{
	char			*filename;
	int				redir_type;
	struct s_redir	*next;
}					t_redir;

typedef struct s_exec
{
	char			**cmds;
	struct s_redir	*redir;
	struct s_exec	*next;
	int				fd_in;
	int				fd_out;

}					t_exec;

#endif
