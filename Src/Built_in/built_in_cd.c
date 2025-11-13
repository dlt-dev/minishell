/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_cd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoesterl <aoesterl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 16:56:31 by aoesterl          #+#    #+#             */
/*   Updated: 2025/11/13 20:18:31 by aoesterl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char* getenv_intern(t_valist* env, char *pattern)
{
	while(env != NULL)
	{ 
		if(strcmp(env->name, pattern) == 0)
			return(env->value);
		env = env->next;
	}
	return(NULL);
}

int cd_only(t_shell *shell)
{ 
	char *str;

	str = getenv_intern(shell->env, "HOME");
	if(str == NULL)
	{ 
		printf("minishell : cd : HOME not set");
		return(GEN_ERRNO);
	}
	else
	{ 
		if(chdir(str) == ERROR)
		{ 
			perror(str); 
			return(GEN_ERRNO);
		}
		else
			printf("%s\n", getcwd(NULL, 0));
	}
	return(0);
}

int too_much_arg(void)
{ 
	char *message;
	message = "too many arguments";
	write(1, message, ft_strlen(message));
	return(GEN_ERRNO);
}

int builtin_cd(t_shell* shell, char **argv)
{
	int i;
	char *message;

	message = "too many arguments";
	i = 1;
	while(argv[i] != NULL)
		i++;
	if(i == 1)
		return(cd_only(shell));
	if(i > 2)
		return(too_much_arg());
	if(chdir(argv[1]) == ERROR)
	{ 
		perror(argv[1]);	
		return(GEN_ERRNO);
	}
	else
		printf("%s\n", getcwd(NULL, 0));
	return(0);
}


