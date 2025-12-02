/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_export1.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoesterl <aoesterl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 17:00:10 by aoesterl          #+#    #+#             */
/*   Updated: 2025/12/02 18:17:07 by aoesterl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	verify_existing_var(t_valist *env, char *value, char *name)
{
	while (env != NULL)
	{
		if (strcmp(name, env->name) == 0)
		{
			free(env->value);
			env->value = value;
			return (free(name), IS);
		}
		env = env->next;
	}
	return (ERROR);
}

int	add_affectation(t_shell *shell, t_valist *env, char *str, int len_name)
{
	t_valist	*node;
	char		*name;
	char		*value;

	name = ft_strndup(str, len_name);
	if (name == NULL)
		return (ERROR);
	value = ft_strdup(&str[len_name + 1]);
	if (value == NULL)
		return (free(name), ERROR);
	if (verify_existing_var(env, value, name) == ERROR)
	{
		node = var_new(name, value);
		if (node == NULL)
			return (free(name), free(value), ERROR);
		var_addback(&shell->env, node);
	}
	return (0);
}

int	builtin_export(t_shell *shell, t_valist *env, char **args, int fd_out)
{
	int	i;
	int	len_name;
	int	ret;

	i = 0;
	if (args[1] == NULL)
	{
		builtin_env(env, fd_out, 1);
		return (0);
	}
	while (args[i] != NULL)
	{
		ret = is_an_affectation(args[i], &len_name);
		if (ret == ERROR)
			shell->exit_status = GEN_ERRNO;
		if (ret == IS)
		{
			if (add_affectation(shell, env, args[i], len_name) == ERROR)
				return (ERROR);
		}
		i++;
	}
	shell->exit_status = 0;
	return (0);
}

/**
 * @brief dans @param ft_export on regarde d'abord si l'arguement de l'export
 * est bien une affectation : @param is_an_affecation.
 * 3 valeurs de retour possible :
 * - si le retour de @param is_an_affecation est ERROR, ca veut dire que le nom

	* de l'affectation etait mauvais et on le signale via
	le message "not_a_valid_identifier".
 * - si le retour de @param is_an_affecation est IS_NOT,
	ce n'est pas une affectation,
 * malgre un bon nom, il n'y a pas de =. On ignore si;ple;ent
 * - si le retour de @param is_an_affecation est IS,
	c'est une affectation et une
 * modification va se faire dans env via @param add_affectation.
 */

// int main(int argc, char **argv, char **envp)
// {
// 	char *args[6];
// 	char *args2[3];

// 	t_shell shell;

// 	args[0] = "export";
// 	args[1] = "var=a b";
// 	args[2] = "=prout";
// 	args[3] = "v-w=54";
// 	args[4] = "ab=42";
// 	args[5] = NULL;

// 	args2[0] = "unset";
// 	args2[1] = "var";
// 	args2[2] = NULL;
// 	if(init_variable(&shell, argc, argv, envp) == ERROR)
// 		free_exit(&shell, GEN_ERRNO, NULL);
// 	ft_export(&shell, shell.env, args);
// 	ft_unset(&shell, shell.env, args2);
// 	print_var_lst(shell.env);

// }