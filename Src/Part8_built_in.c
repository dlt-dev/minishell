/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Part8_built_in.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdelattr <jdelattr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/11 19:54:50 by jdelattr          #+#    #+#             */
/*   Updated: 2025/11/12 15:01:11 by jdelattr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void ft_exit(t_shell *shell)
{
	free_exit(shell, 0,  "exit");
}

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

void find_env_to_unset(t_shell *shell, t_valist *env, char *name)
{ 
	t_valist *prev_node;

	prev_node = NULL;
	while(env != NULL)
	{ 
		if(ft_strcmp(name, env->name) == 0)
		{ 
			del_one_valist(&shell->env, env, prev_node); // trouver la fonction
			return;
		}
		prev_node = env;
		env = env->next;
	}
}

void ft_unset(t_shell *shell, t_valist *env, char **args)
{
	int i;

	i = 1;
	if(env == NULL)
		return;
	while(args[i] != NULL)
	{
		find_env_to_unset(shell, env, args[i]);
		i++;
	}
}

/* void ft_unset(void)
{
	printf("execute unset !\n");
} */

void ft_export(void)
{
	printf("execute export !\n");
}

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

int ft_cd(char **argv)
{
	int i;
	//char *path;
	char *message;

	message = "too many arguments";
	i = 1;
	while(argv[i] != NULL)
		i++;
	if(i > 2)
	{ 
		write(1, message, ft_strlen(message));
		message = "too many arguments";
		return(GEN_ERRNO);
	}	
	if(chdir(argv[1]) == ERROR)
	{ 
		perror(argv[1]);	
		return(GEN_ERRNO);
	}
	else
		printf("%s\n", getcwd(NULL, 0));
	return(0);
}

void ft_echo(char **args)
{ 
	int i;
	int flag_n;

	flag_n = 0;
	i = 1;
	while(ft_strcmp(args[i], "-n") == 0)
	{
		flag_n = 1;
		i++;
	}
	while(args[i] != NULL)
	{ 
		write(1 , args[i], ft_strlen(args[i]));
		write(1 , " ", 1);
		i++; 
	}
	if(flag_n == 0)
		write(1, "\n", 1);
}

/////////////////////////////////////
/// @fonctions manage_built_in.c /// 
////////////////////////////////////

enum	e_builtin_type
{
	NO_BUILT_IN,
	ECHO,
	CD,
	PWD,
	EXPORT,
	UNSET,
	ENV,
	EXIT,
};

int	is_built_in(char *cmd) // return l'enum du builtin
{
	if (ft_strncmp(cmd, "echo", ft_strlen("echo")) == 0)
		return (1);
	if (ft_strncmp(cmd, "cd", ft_strlen("cd")) == 0)
		return (2);
	if (ft_strncmp(cmd, "pwd", ft_strlen("pwd")) == 0)
		return (3);
	if (ft_strncmp(cmd, "export", ft_strlen("export")) == 0)
		return (4);
	if (ft_strncmp(cmd, "unset", ft_strlen("unset")) == 0)
		return (5);
	if (ft_strncmp(cmd, "env", ft_strlen("env")) == 0)
		return (6);
	if (ft_strncmp(cmd, "exit", ft_strlen("exit")) == 0)
		return (7);

	else
		return (NO_BUILT_IN);
}

int	execute_built_in(t_shell *shell, int type, char **args, t_valist *env)//, char **args)
{
	if (type == ECHO) // echo with option -n
		ft_echo(args);
	if (type == CD) // with only a relative or absolute path
		ft_cd(args);
	if (type == PWD) // no opt
		ft_pwd();
	if (type == EXPORT) // no opt mais plusieurs args
		ft_export();
	if (type == UNSET) // no opt
		ft_unset(shell, env, args); //ft_unset(shell, env, args);
	if (type == ENV) // no opt
		ft_env(env);
	if (type == EXIT) // no opt
		ft_exit(shell); //(args) si args est ce que j'execute qm ???
	//else
	return (1);
	
}