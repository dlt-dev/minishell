/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_built_in.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoesterl <aoesterl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/07 17:02:26 by aoesterl          #+#    #+#             */
/*   Updated: 2025/11/10 18:11:34 by aoesterl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Header/minishell.h"


int is_a_valid_name(char* str)
{
	int i;
	int flag_name;
	
	flag_name = 0;
	i = 0;
	if ((str[0] < 'A' || str[0] > 'Z') && (str[0] < 'a' || str[0] > 'z')
		&& (str[0] != '_'))
		flag_name = 1;
	while(str[i] != '=' && str[i] != '\0')
	{
		if ((str[i] < '0' || str[i] > '9') && (str[i] < 'A' || str[i] > 'Z')
			&& (str[i] < 'a' || str[i] > 'z') && (str[i] != '_'))
			flag_name = 1;
		i++;
	}
	if(flag_name == 1)
		return(ERROR);
	return(0);
}

int is_an_affectation(char *str, int *len_name)
{ 
	int i;

	*len_name = length_name(str);
	i = 0;
	if(is_a_valid_name(str) == ERROR) // not a valid identifier
	{ 
		printf("minishell: export: \'%s\': not a valid identifier\n", str);
		return(ERROR);
	}
	while(i < *len_name)
		i++;
	if(str[i] == '=')
		return(IS); // est une affectation;
	return(IS_NOT); // n'est pas une affecation;
}

int verify_existing_var(t_valist *env, char *value, char *name)
{ 
	while(env != NULL)
	{
		if(strcmp(name, env->name) == 0)
		{
			free(env->value);
			env->value = value;
			return(free(name), IS);
		}
		env = env->next;
	}
	return(ERROR);
}

int add_affectation(t_shell *shell, t_valist *env, char *str, int len_name)
{
	t_valist *node;
	char *name;
	char *value;
	int i;

	i = 0;
	name = ft_strndup(str, len_name);
	if(name == NULL)
		return(ERROR);
	value = ft_strdup(&str[len_name + 1]);
	if(value == NULL)
		return(free(name), ERROR);
	if(verify_existing_var(env, value, name) == IS)
		return(0);
	node = var_new(name, value);
	if(node == NULL)
		return(free(name), free(value), ERROR);
	var_addback(&shell->env, node);
	return(0);
}
 
int ft_export(t_shell *shell, t_valist *env, char **args)
{ 
	int i;	
	int len_name;
	int ret;
	
	i = 0;
	while(args[i] != NULL)
	{
		ret = is_an_affectation(args[i], &len_name);
		if(ret == ERROR)
				shell->exit_status = GEN_ERRNO;
		if(ret == IS)
		{ 
			if(add_affectation(shell, env, args[i], len_name) == ERROR)
				return(ERROR);
		}
		i++;
	}
	return(0);	
}


int main(int argc, char **argv, char **envp)
{
	char *args[6];
	char *args2[3];
	
	t_shell shell;

	args[0] = "export";
	args[1] = "var=a b";
	args[2] = "=prout";
	args[3] = "v-w=54";
	args[4] = "ab=42";
	args[5] = NULL;

	args2[0] = "unset";
	args2[1] = "var";
	args2[2] = NULL;
	if(init_variable(&shell, argc, argv, envp) == ERROR)
		free_exit(&shell, GEN_ERRNO, NULL);
	ft_export(&shell, shell.env, args);
	ft_unset(&shell, shell.env, args2);
	print_var_lst(shell.env);
	
}

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