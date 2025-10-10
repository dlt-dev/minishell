/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoesterl <aoesterl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/10 18:45:41 by aoesterl          #+#    #+#             */
/*   Updated: 2025/10/10 18:46:30 by aoesterl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Header/minishell.h"
#include "unistd.h"
#include "stdio.h"
#include "stdlib.h"

#define YELL_PS "\033[33;1m"
#define BLUE_PS "\033[34;1m"

typedef struct s_prompt
{ 
	char *user;
	char *cwd;
	char *empty;
	char *color_user;
	char *color_cwd;
	char *color_reset;
	char *prompt;
	int pos_cwd;
}t_prompt;

size_t	ft_strlen(char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}