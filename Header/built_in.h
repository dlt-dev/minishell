/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoesterl <aoesterl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/11 17:33:42 by aoesterl          #+#    #+#             */
/*   Updated: 2025/11/11 17:39:18 by aoesterl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILT_IN_H
	#define BUILT_IN_H

#include "struct.h"


int builtin_cd(char **argv);
void builtin_echo(char **args);
void builtin_env(t_valist *env);
void builtin_exit(t_shell *shell);
int builtin_pwd(void);
void builtin_unset(t_shell *shell, t_valist *env, char **args);

int builtin_export(t_shell *shell, t_valist *env, char **args);
int is_an_affectation(char *str, int *len_name);


#endif