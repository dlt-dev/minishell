/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_exec3.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdelattr <jdelattr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/17 18:12:59 by jdelattr          #+#    #+#             */
/*   Updated: 2025/11/17 19:45:50 by jdelattr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* static int	ft_lstvalist_size(t_valist *lst)
{
	int	count;

	count = 0;
	while (lst != NULL)
	{
		count++;
		lst = lst->next;
	}
	return (count);
}

char **env_list_to_envp(t_valist *env_list)
{
	int count = ft_lstvalist_size(env_list);

	char **env = malloc(sizeof(char *) * (count + 1));

	if (!env)
		return NULL;

	int i = 0;
	while (env_list)
	{
		int len_name = strlen(env_list->name);
		int len_val = strlen(env_list->value);

		int total = len_name + 1 + len_val;

		env[i] = malloc(total + 1);

		if (!env[i])
			return NULL; // FREE ?

		ft_memcpy(env[i], env_list->name, len_name);
		env[i][len_name] = '=';
		ft_memcpy(env[i] + len_name + 1, env_list->value, len_val);

		env[i][total] = '\0';

		env_list = env_list->next;
		i++;
	}
	env[i] = NULL;
	return env;
} */

static char *create_str_var(t_valist *current)
{ 
	int		len_name;
	int		len_val;
	char *str;

	len_name = strlen(current->name);
	len_val = strlen(current->value);
	str  = malloc( len_name + 1 + len_val + 1);
	if(str == NULL)
		return(NULL);
	ft_memcpy(str, current->name, len_name);
	str[len_name] = '=';
	ft_memcpy(str + len_name + 1, current->value, len_val);
	str[len_name + 1 + len_val] = '\0';
	return(str);
}

char	**env_list_to_envp(t_valist *env_list, int count)
{
	char	**env;
	int		i;

	env = malloc(sizeof(char *) * (count + 1));
	if (!env)
		return (NULL);
	i = 0;
	while (env_list != NULL)
	{
		env[i] = create_str_var(env_list);
		env_list = env_list->next;
		i++;
	}
	env[i] = NULL;
	return (env);
}

// char	**env_list_to_envp(t_valist *env_list, int count)
// {
// 	char	**env;
// 	int		i;
// 	int		len_name;
// 	int		len_val;

// 	env = malloc(sizeof(char *) * (count + 1));
// 	if (!env)
// 		return (NULL);
// 	i = 0;
// 	while (env_list)
// 	{
// 		len_name = strlen(env_list->name);
// 		len_val = strlen(env_list->value);
// 		env[i] = malloc( len_name + 1 + len_val + 1);
// 		if (!env[i])
// 			return (NULL); // FREE ?
// 		ft_memcpy(env[i], env_list->name, len_name);
// 		env[i][len_name] = '=';
// 		ft_memcpy(env[i] + len_name + 1, env_list->value, len_val);
// 		env[i][len_name + 1 + len_val] = '\0';
// 		env_list = env_list->next;
// 		i++;
// 	}
// 	env[i] = NULL;
// 	return (env);
// }
