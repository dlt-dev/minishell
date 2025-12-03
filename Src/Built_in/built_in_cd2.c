/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_cd2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoesterl <aoesterl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/02 01:50:04 by aoesterl          #+#    #+#             */
/*   Updated: 2025/12/03 17:39:12 by aoesterl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*getenv_intern(t_valist *env, char *name)
{
	while (env != NULL)
	{
		if (strcmp(env->name, name) == 0)
			return (env->value);
		env = env->next;
	}
	return (NULL);
}

char	*create_affectation(char *name, char *value)
{
	t_cb	buffer;
	char	*str;

	init_chunk_buffer(&buffer, 20, 2);
	if (cb_append_str(&buffer, name) == ERROR)
		return (NULL);
	if (cb_append_char(&buffer, '=') == ERROR)
		return (NULL);
	if (cb_append_str(&buffer, value) == ERROR)
		return (NULL);
	str = fusion_all_chunk(&buffer);
	if (str == NULL)
		return (NULL);
	return (str);
}

char	**create_export_tab(char *pwd)
{
	char	**args;

	args = malloc(sizeof(char *) * 3);
	if (args == NULL)
		return (NULL);
	args[0] = ft_strdup("export");
	if (args[0] == NULL)
		return (ft_free_tab(args), NULL);
	args[1] = ft_strdup(pwd);
	if (args[1] == NULL)
		return (ft_free_tab(args), NULL);
	args[2] = NULL;
	return (args);
}

int	update_env(t_shell *shell, char *name, char *value, int fd_out)
{
	char	*affectation;
	char	**args;

	if (name == NULL || value == NULL)
		return (ERROR);
	affectation = create_affectation(name, value);
	if (affectation == NULL)
		return (GEN_ERRNO);
	args = create_export_tab(affectation);
	if (args == NULL)
		return (free(affectation), GEN_ERRNO);
	if (builtin_export(shell, shell->env, args, fd_out) == ERROR)
		return (free(affectation), ft_free_tab(args), GEN_ERRNO);
	return (free(affectation), ft_free_tab(args), 0);
}

int	update_cwd(t_shell *shell, t_valist *env, int fd_out)
{
	char	*pwd;
	char	*oldpwd;

	pwd = getcwd(NULL, 0);
	oldpwd = getenv_intern(env, "PWD");
	if (pwd == NULL)
		return (perror("getcwd"), ERROR);
	if (oldpwd != NULL)
	{
		if (update_env(shell, "OLDPWD", oldpwd, fd_out) == ERROR)
			return (free(pwd), ERROR);
	}
	if (update_env(shell, "PWD", pwd, fd_out) == ERROR)
		return (free(pwd), ERROR);
	free(pwd);
	return (0);
}
