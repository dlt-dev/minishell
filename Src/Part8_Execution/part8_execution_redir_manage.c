/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   part8_execution_redir_manage.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoesterl <aoesterl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 16:12:55 by aoesterl          #+#    #+#             */
/*   Updated: 2025/11/11 18:19:26 by aoesterl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "minishell.h"






// typedef struct s_redir
// {
// 	char			*filename;
// 	int				redir_type;
// 	struct s_redir	*next;
	 
// }	t_redir;

// typedef struct s_exec
// {
// 	char			**cmds;
// 	struct s_redir	*redir;
// 	struct s_exec	*next;
// }	t_exec;


// int apply_redir_infile(t_redir *redir, struct stat *buf)
// { 
// 	int fd;
// 	struct stat buf;
// 	if(stat(redir->filename, &buf) == ERROR)
// 		return(ERROR);
// 	if(S_ISREG(buf.st_mode) == 0 || S_ISLNK(buf->st_mode) == 0)
			
// 	fd = (redir->filename, O_RDONLY);
// 	if(fd == ERROR)
// 		perror("")
// 	dup2(fd, 1)
// 	close(fd);
	
// }

// int apply_redir(t_redir *redir)
// {
// 	int check_failed;
// 	struct stat buf;
	
// 	while(redir != NULL)
// 	{
// 		check_failed = 0;
// 		if(stat(redir->filename, &buf) == ERROR)
// 			return(ERROR);
// 		if(redir->redir_type == HEREDOC)
// 			check_failed = apply_redir_heredoc(redir, &buf);
// 		if(redir->redir_type == INFILE)
// 			check_failed = apply_redir_infile(redir, &buf); 
// 		if(redir->redir_type == OUTFILE)
// 			check_failed =  apply_redir_outfile(redir, &buf); 
// 		if(redir->redir_type == OUTFILE_APPEND)
// 			check_failed = apply_redir_outfile_append(redir, &buf);
// 		if(check_failed == ERROR)
// 			return(ERROR);
// 		redir = redir->next;
// 	}
// 	return(0);	
// }








// PARENT (shell principal)
// │
// ├─ Si 1 seule commande et builtin → exécution directe
// │
// └─ Sinon :
//    ├─ fork chaque commande
//    │   ├─ setup redirs (dup2)
//    │   ├─ setup pipes (dup2)
//    │   └─ execve ou builtin
//    └─ wait tous les enfants
