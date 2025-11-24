/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdelattr <jdelattr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/11 17:33:42 by aoesterl          #+#    #+#             */
/*   Updated: 2025/11/24 20:09:00 by jdelattr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILT_IN_H
	#define BUILT_IN_H

#include "struct.h"

char* getenv_intern(t_valist* env, char *pattern);
int builtin_cd(t_shell *shell, char **argv);
int builtin_echo(char **args, int fd_out);
int builtin_env(t_valist *env, int fd_out, int flag_export);
void builtin_exit(t_shell *shell, char **args, int print_flag);
int builtin_pwd(int fd_out);
int builtin_unset(t_shell *shell, t_valist *env, char **args);
int builtin_export(t_shell *shell, t_valist *env, char **args);
int is_an_affectation(char *str, int *len_name);

#endif