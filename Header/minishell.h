/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdelattr <jdelattr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/29 17:17:54 by jdelattr          #+#    #+#             */
/*   Updated: 2025/11/20 18:07:38 by jdelattr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

#include <unistd.h> 
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <fcntl.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>


#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>


#include "macro.h"
#include "struct.h"
#include "utils.h"
#include "chunk_buffer.h"
#include "exec_struct.h"
#include "built_in.h"

//Part0: init_variable
int init_variable(t_shell *shell, int argc, char **argv, char **envp);

//Part1: Prompt
int get_prompt(t_shell *shell, t_valist *env , t_prompt *invite);

//Part2: lexing
int lexing(char *str, t_list **lst);

//Part3: Put_flag
void flag_word(t_list*lst);
void put_flags (t_list *lst);

//Part4: Expansion
int	handle_single_quotes(t_cb *lst_buffer, char *str); 
int handle_double_quotes(t_shell *shell, t_cb* lst_buffer, char *str);
int handle_dollar(t_shell* shell, t_cb* lst_buffer, char *str);
int	expand_shell_param(t_shell *shell, t_list *lst);

//Part5: Word_splitting 
int split_param(t_shell *shell, t_list *curr_node, t_list *prev_node);
int count_word_hdle_quotes(char *str);
char **word_splitting(char *str, int count_word);

// Part6_delete_quotes
int delete_quotes(t_shell *shell, t_list *lst);

//Part7 : cmd_struct
// int logical_struct(t_shell *shell, t_list *token);
int redir_management(t_exec *current, t_list *token, int type); //changement
void print_syntax_error(t_shell *shell, char *tok_content); // changement
char *redir_name(int type); // TEST PRINT
void print_cmd_list(t_exec *head); // TEST PRINT

// Part6_delete_quotes
int delete_quotes(t_shell *shell, t_list *lst);

// Part7_Cmd_struct
void	print_cmd_list(t_exec *head); // TEST PRINT
char	*redir_name(int type); // TEST PRINT
int	add_arg_command(t_exec *current, char *cmd);
int	logical_struct(t_shell *shell, t_exec *current, t_list *token);
int	redir_management(t_exec *current, t_list *token, int type);
void	print_syntax_error(t_shell *shell, char *tok_content);
void free_exec(t_exec *cmd);
void free_tab(char **cmds);

//Part8 : execution

int	manage_execution(t_shell *shell, t_valist *env); // execution
int	check_all_redir(t_shell *shell); // open_dir
int handle_heredoc(char *delimit); // heredoc
int	is_built_in(char *cmd); // built_in
int	execute_built_in(t_shell *shell, int type, char **args, t_valist *env); // built_in
int	exec_fork_one(t_shell *shell, char **cmd, t_valist *env);
char	*find_my_cmd_path(char *my_cmd, char **envp);
int	path_not_found(void);
void	ft_free_tab(char **tab);

int	wait_and_status(t_shell *shell, pid_t last_pid);

int	close_all_redir(t_exec *commands);

//PartX_free.c
void free_all(t_shell *shell);
void free_exit(t_shell *shell, int code, char *message);
void free_exec(t_exec *cmd);
void free_exec_lst(t_exec **head);

#endif
