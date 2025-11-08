/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_built_in.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arthurito <arthurito@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/07 17:02:26 by aoesterl          #+#    #+#             */
/*   Updated: 2025/11/08 23:13:01 by arthurito        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Header/minishell.h"


// void ft_echo(char **args)
// { 
// 	int i;
// 	int flag_n;

// 	flag_n = 0;
// 	i = 1;
// 	while(ft_strcmp(args[i], "-n") == 0)
// 	{
// 		flag_n = 1;
// 		i++;
// 	}
// 	while(args[i] != NULL)
// 	{ 
// 		write(1 , args[i], ft_strlen(args[i]));
// 		write(1 , " ", 1);
// 		i++; 
// 	}
// 	if(flag_n == 0)
// 		write(1, "\n", 1);
// }

// int ft_pwd(void)
// {
// 	char *path;
// 	path = getcwd(NULL, 0);
// 	if(path == NULL)
// 		return(GEN_ERRNO);
// 	write(1, path, ft_strlen(path));
// 	write(1, "\n", 1);
// 	free(path);
// 	return(0);
// }

// int ft_cd(char **argv)
// {
// 	int i;
// 	char *path;
// 	char *message;

// 	message = "too many arguments";
// 	i = 1;
// 	while(argv[i] != NULL)
// 		i++;
// 	if(i > 2)
// 	{ 
// 		write(1, message, ft_strlen(message));
// 		message = "too many arguments";
// 		return(GEN_ERRNO);
// 	}	
// 	if(chdir(argv[1]) == ERROR)
// 	{ 
// 		perror(argv[1]);	
// 		return(GEN_ERRNO);
// 	}
// 	else
// 		printf("%s\n", getcwd(NULL, 0));
// 	return(0);
// }

// void ft_exit(t_shell *shell)
// {
// 	free_exit(shell, 0,  "exit");
// }

// void ft_env(t_valist *env)
// {	
// 	while(env != NULL)
// 	{ 	
// 		write(1, env->name, ft_strlen(env->name));
// 		write(1, "=", 1);
// 		write(1 , env->value, ft_strlen(env->value));
// 		write(1, "\n", 1);
// 		env = env->next;
// 	}
// }

// int main(int argc, char **argv)
// {
// 	int exit;

// 	exit = 0;
// 	if(argc < 2)
// 		return(0);
// 	// ft_echo(&argv[1]);
// 	// ft_pwd();
// 	exit = ft_cd(&argv[1]);
// 	printf("%d\n", exit);
// }

int main ()
{
	// readline(NULL);
	perror(NULL);
	
}