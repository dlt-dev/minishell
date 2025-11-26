/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_cd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoesterl <aoesterl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 16:56:31 by aoesterl          #+#    #+#             */
/*   Updated: 2025/11/26 02:09:08 by aoesterl         ###   ########.fr       */
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


int set_pwd(t_shell *shell, t_valist *env)
{
	char *cwd;
	char *affectation;

	affectation 
	
	cwd = getcwd(NULL, 0);
	if(cwd != NULL)
	{
		if(getenv_intern(env, "PWD") == NULL)
			
	}

}

int cd_only(t_shell *shell)
{ 
	char *str;
	char *msg;

	msg = "minishell : cd : HOME not set\n";
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
	msg = "minishell: cd : too many arguments\n";
	write(1, msg, ft_strlen(msg));
	return(GEN_ERRNO);
}

int builtin_cd(t_shell* shell, char **argv)
{
	int i;
	
	i = 1;
	while(argv[i] != NULL)
		i++;
	if(i == 1)
		return(cd_only(shell));
	if(i > 2)
		return(too_much_arg());
	if(chdir(argv[1]) == ERROR)
	{ 
		print_error_message("cd", argv[1]);	
		return(GEN_ERRNO);
	}
	return(0);
}


