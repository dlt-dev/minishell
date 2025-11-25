/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_env.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdelattr <jdelattr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 17:00:20 by aoesterl          #+#    #+#             */
/*   Updated: 2025/11/25 14:40:55 by jdelattr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	builtin_env(t_valist *env, int fd_out, int flag_export)
{
	if (env == NULL)
		return (0);
	while (env != NULL)
	{
		if (flag_export == 1)
			write(fd_out, "export ", 7);
		write(fd_out, env->name, ft_strlen(env->name));
		write(fd_out, "=", 1);
		write(fd_out, env->value, ft_strlen(env->value));
		write(fd_out, "\n", 1);
		env = env->next;
	}
	return (0);
}
