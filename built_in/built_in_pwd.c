/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_pwd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoesterl <aoesterl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 17:00:14 by aoesterl          #+#    #+#             */
/*   Updated: 2025/11/10 17:01:32 by aoesterl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


int ft_pwd(void)
{
	char *path;
	path = getcwd(NULL, 0);
	if(path == NULL)
		return(GEN_ERRNO);
	write(1, path, ft_strlen(path));
	write(1, "\n", 1);
	free(path);
	return(0);
}