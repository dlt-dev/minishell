/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_env.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoesterl <aoesterl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 17:00:20 by aoesterl          #+#    #+#             */
/*   Updated: 2025/11/10 17:02:05 by aoesterl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void ft_env(t_valist *env)
{	
	if(env == NULL)
		return;
	while(env != NULL)
	{ 	
		write(1, env->name, ft_strlen(env->name));
		write(1, "=", 1);
		write(1 , env->value, ft_strlen(env->value));
		write(1, "\n", 1);
		env = env->next;
	}
}