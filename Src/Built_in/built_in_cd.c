/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_cd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoesterl <aoesterl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 16:56:31 by aoesterl          #+#    #+#             */
/*   Updated: 2025/12/02 02:23:22 by aoesterl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	cd_only(t_shell *shell)
{
	char	*str;

	str = getenv_intern(shell->env, "HOME");
	if (str == NULL)
	{
		write_str_fd("minishell : cd : HOME not set\n", 2);
		return (GEN_ERRNO);
	}
	else
	{
		if (chdir(str) == ERROR)
		{
			print_error_message("cd", str);
			return (GEN_ERRNO);
		}
	}
	if (update_cwd(shell, shell->env) == ERROR)
		return (GEN_ERRNO);
	return (0);
}

int	builtin_cd(t_shell *shell, char **argv)
{
	int	i;

	i = 1;
	while (argv[i] != NULL)
		i++;
	if (i == 1)
		return (cd_only(shell));
	if (i > 2)
	{
		write_str_fd("minishell: cd : too many arguments\n", 2);
		return (GEN_ERRNO);
	}
	if (chdir(argv[1]) == ERROR)
	{
		print_error_message("cd", argv[1]);
		return (GEN_ERRNO);
	}
	if (update_cwd(shell, shell->env) == ERROR)
		return (GEN_ERRNO);
	return (0);
}
