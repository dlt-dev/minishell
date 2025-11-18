/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_cd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoesterl <aoesterl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 16:56:31 by aoesterl          #+#    #+#             */
/*   Updated: 2025/11/18 02:16:29 by aoesterl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char* getenv_intern(t_valist* env, char *name)
{
	while(env != NULL)
	{ 
		if(strcmp(env->name, name) == 0)
			return(env->value);
		env = env->next;
	}
	return(NULL);
}


int set_env_intern(t_shell *shell, char *name, char *value)
{
	char *new_value;
	t_valist *tmp;
	t_valist *env;
	
	new_value = ft_strdup(value);
	if(new_value == NULL)
		return(ERROR);
	env = shell->env;
	while(env != NULL)
	{ 
		if(strcmp(name, env->name) == 0)
		{ 
			free(env->value);
				env->value = new_value;
			return(0);
		}
		env = env->next;
	}
	tmp = var_new(name, new_value);
	if(tmp == NULL)	
		return(free(new_value), ERROR);
	var_addback(&shell->env, tmp);
	return(0);
}

int cd_only(t_shell *shell)
{ 
	char *str;
	char *msg;

	msg = "minishell: cd: HOME not set\n";
	str = getenv_intern(shell->env, "HOME");
	if(str == NULL)
	{ 
		write (2 , msg, ft_strlen(msg));
		return(GEN_ERRNO);
	}
	else
	{ 
		if(chdir(str) == ERROR)
		{
			print_error_message("cd" , str); 
			return(GEN_ERRNO);
		}
	}
	return(0);
}

int too_much_arg(void)
{ 
	char *msg;
	msg = "minishell: cd: too many arguments\n";
	write(1, msg, ft_strlen(msg));
	return(GEN_ERRNO);
}

int set_new_pwd(t_shell *shell, char* str)
{
	char *new_pwd;

	new_pwd = getcwd(NULL, 0);
	if(new_pwd != NULL)
	{
		if(set_env_intern(shell, "PWD", new_pwd) == ERROR)
			return(free(new_pwd), ERROR);
	}
	if(new_pwd == NULL)
	{
		print_error_message("cd", str);
		return(ERROR);
		// new_pwd = getenv_intern(shell->env, "PWD");
		// if(old_pwd == NULL)
	}
	return(0);
}

int builtin_cd(t_shell* shell, char **args)
{
	int i;
	
	i = 1;
	while(args[i] != NULL)
		i++;
	if(i == 1)
		return(cd_only(shell));
	if(i > 2)
		return(too_much_arg());
	if(chdir(args[1]) == ERROR)
	{
		perror(args[1]);	
		return(GEN_ERRNO);
	}
	else
	{
		if(set_new_pwd(shell, args[1]) == ERROR)
			return(GEN_ERRNO);
	}
	return(0);
}


