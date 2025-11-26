/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdelattr <jdelattr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/29 17:17:54 by jdelattr          #+#    #+#             */
/*   Updated: 2025/11/26 17:25:22 by jdelattr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "built_in.h"
# include "chunk_buffer.h"
# include "exec_struct.h"
# include "macro.h"
# include "struct.h"
# include "utils.h"
# include <errno.h>
# include <fcntl.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>

// Part0: init_variable
int		init_variable(t_shell *shell, int argc, char **argv, char **envp);

// Part1: Prompt
int		get_prompt(t_shell *shell, t_valist *env, t_prompt *invite);

// Part2: lexing
int		lexing(char *str, t_list **lst);

// Part3: Put_flag
void	flag_word(t_list *lst);
void	put_flags(t_list *lst);

// Part4: Expansion
int		handle_single_quotes(t_cb *lst_buffer, char *str);
int		handle_double_quotes(t_shell *shell, t_cb *lst_buffer, char *str);
int		handle_dollar(t_shell *shell, t_cb *lst_buffer, char *str);
int		expand_shell_param(t_shell *shell, t_list *lst);

// Part5: Word_splitting
int		split_param(t_shell *shell, t_list *curr_node, t_list *prev_node);
int		count_word_hdle_quotes(char *str);
char	**word_splitting(char *str, int count_word);

// Part6_delete_quotes
int		delete_quotes(t_shell *shell, t_list *lst);
int		chck_dlt_quotes(t_shell *shell, t_list **new_n, t_list *prev_n,
			t_list *lst);
t_list	*delete_quotes_node(t_list *node);
char	*delete_quotes_str(t_list *node);
int		buffer_delete_quotes(t_cb *lst_buffer, char *str);
int		checker_close_quotes(char *str);

// Part7 : cmd_struct

int		redir_management(t_exec *current, t_list *token, int type);
void	print_syntax_error(t_shell *shell, char *tok_content);
char	*redir_name(int type); // TEST PRINT
void	print_cmd_list(t_exec *head); // TEST PRINT

// Part6_delete_quotes
int		delete_quotes(t_shell *shell, t_list *lst);

// Part7_Cmd_struct
void	print_cmd_list(t_exec *head); // TEST PRINT
char	*redir_name(int type); // TEST PRINT
int		add_arg_command(t_exec *current, char *cmd);
int		logical_struct(t_shell *shell, t_exec *current, t_list *token);
int		redir_management(t_exec *current, t_list *token, int type);
void	print_syntax_error(t_shell *shell, char *tok_content);
void	free_exec(t_exec *cmd);
void	free_tab(char **cmds);

// Part8 : execution

int		manage_execution(t_shell *shell, t_valist *env);
int		check_all_redir(t_shell *shell);
int		execute_built_in(t_shell *shell, int type, char **args, int print_flag);
int		exec_fork_one(t_shell *shell, char **cmd, t_valist *env);
int		exec_fork_pipe(t_shell *shell, t_exec *current, char **cmd,
			int pipe_fd[2]);
int		handle_heredoc(char *delimit);
int		apply_redir_pipe(t_shell *shell, t_exec *current, int pipe_fd[2]);
int		do_execve(char **cmd, t_valist *env);
void	test_print_fd(t_exec *cmd_list); // TEST
void	print_char_tab(char **tab); // TEST
int		ft_lstexec_size(t_exec *lst);
int		path_not_found(void);
char	*find_my_cmd_path(char *my_cmd, char **envp, int *check);
int		exist_and_access(char *my_path);
int		is_built_in(char *cmd);
int		close_all_redir(t_exec *commands);
int		wait_and_status(t_shell *shell, pid_t last_pid);

// PartX_free.c
void	free_all(t_shell *shell);
void	free_exit(t_shell *shell, int code, char *message);
void	free_exec(t_exec *cmd);
void	free_exec_lst(t_exec **head);

#endif
