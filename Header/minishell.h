/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoesterl <aoesterl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/29 17:17:54 by jdelattr          #+#    #+#             */
/*   Updated: 2025/12/02 04:09:13 by aoesterl         ###   ########.fr       */
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
# include "get_next_line.h"
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
void	interactive_shell(t_shell *shell);
int		non_interactive_shell(t_shell *shell);

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
char	*create_expand_str(t_shell *shell, char *str);
int		main_expand(t_shell *shell, t_list *lst_node);

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
char	*delete_quotes_str(t_list *node);

// Part7_Cmd_struct
void	print_cmd_list(t_exec *head); // TEST PRINT
char	*redir_name(int type); // TEST PRINT
int		add_arg_command(t_exec *current, char *cmd);
int		logical_struct(t_shell *shell, t_exec *current, t_list *token);
int		redir_management(t_exec *current, t_list *token, int type);
void	print_syntax_error(t_shell *shell, char *tok_content);
void	free_exec(t_exec *cmd);
void	free_tab(char **cmds);

// Part8_Open_fd
int		check_all_redir(t_shell *shell);
int		handle_heredoc(t_shell *shell, char *delimit);
int		here_doc_no_expand(char *delimit, int pipefd[2]);
int		here_doc_expand(t_shell *shell, char *delimit, int pipefd[2]);

// Part9 : execution
	//Part1_exec_main.c
int		manage_execution(t_shell *shell, t_valist *env);
	//Part2_A_exec_built_in.c
int		is_built_in(char *cmd);
int		execute_built_in(t_shell *shell, int type, char **args, int print_flag);
	//Part2_B_routine_simple_cmd.c
int		exec_fork_one(t_shell *shell, char **cmd, t_valist *env);
	//Part2_C_routine_pipe.c
int		exec_fork_pipe(t_shell *shell, t_exec *current, char **cmd,
			int pipe_fd[2]);
	//Part3_apply_redirection.c
int		apply_redir_pipe(t_shell *shell, t_exec *current, int pipe_fd[2]);
	//part4_execve.c
int		do_execve(char **cmd, t_valist *env);
	//Part4_utils_execution.c
int		exist_and_access(char *my_path, struct stat *st, int *check);
int		ft_lstexec_size(t_exec *lst);
char	*find_my_cmd_path(char *my_cmd, char **envp, int *check);
	//Part5_waitpid.c
int		wait_and_status(t_shell *shell, pid_t last_pid);
	// PartX_debug_exec.c
void	test_print_fd(t_exec *cmd_list); // TEST
void	print_char_tab(char **tab); // TEST

// PartX_free.c
int		close_all_redir(t_exec *commands);
void	free_all(t_shell *shell);
void	free_exit(t_shell *shell, int code, char *message);
void	free_exec(t_exec *cmd);
void	free_exec_lst(t_exec **head);

//PartZ_Signaux
	//parent_and_child_shell_sig
void	handle_shell_sig(t_shell *shell);
void	sig_update_exit_status(t_shell *shell);
void	set_ignore_sig(t_shell *shell);
void	set_default_sig(t_shell *shell);
	//heredoc
void	set_heredoc_sig(t_shell *shell);

extern volatile sig_atomic_t	flag_signal;

#endif