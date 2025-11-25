/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_pwd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdelattr <jdelattr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 17:00:14 by aoesterl          #+#    #+#             */
/*   Updated: 2025/11/25 14:48:12 by jdelattr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	builtin_pwd(int fd_out)
{
	char	*path;

	path = getcwd(NULL, 0);
	if (path == NULL)
		return (GEN_ERRNO);
	write(fd_out, path, ft_strlen(path));
	write(fd_out, "\n", 1);
	free(path);
	return (0);
}
