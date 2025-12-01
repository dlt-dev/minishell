/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_cd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoesterl <aoesterl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 16:56:31 by aoesterl          #+#    #+#             */
/*   Updated: 2025/12/01 20:09:04 by aoesterl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*getenv_intern(t_valist *env, char *name)
{
	while (env != NULL)
	{
		if (strcmp(env->name, name) == 0)
			return (env->value);
		env = env->next;
	}
	return (NULL);
}


int create_affectation(char *name, char *value)
{ 
	t_cb buffer;
	char *str;
	
	init_chunk_buffer(&buffer, 20, 2);
	if(cb_append_str(&buffer, name) == ERROR)
		return(ERROR);
	if(cb_append_char(&buffer, "=") == ERROR)
		return(ERROR);
	if(cb_append_str(&buffer, value) == ERROR)
		return(ERROR);
	str = fusion_all_chunk(&buffer);
	if(str == NULL)
		return(ERROR);
	return(0);
}

char ** create_export_tab(char *pwd)
{ 
	char **args;
	int i;
	
	i = 0;
	args = malloc(sizeof(char *) * 3);
	if(args == NULL)
		return(NULL);
	args[0] = ft_strdup("export");
	if(args[0] == NULL)
		return(ft_free_tab(args), NULL);
	args[1] = ft_strdup(pwd);
	if(args[1] == NULL)
		return(ft_free_tab(args), NULL);
	args[2] = NULL;
	return(0);
}

int update_env(t_shell *shell, t_valist *env, char *name, char *value)
{ 
	char *affectation;
	char **args;
	
	affectation = create_affectation(name, value);
	if(affectation == NULL)
		return(GEN_ERRNO);
	args = create_export_tab(affectation);
	if(args == NULL)
		return(free(affectation), GEN_ERRNO);
	if(builtin_export(shell, env, args) == ERROR)
		return(free(affectation), ft_free_tab(args), GEN_ERRNO);
	return(free(affectation), ft_free_tab(args), 0);
}

int update_cwd(t_shell *shell, t_valist *env, char *name)
{
	char *str;
	char *pwd;
	char **args; 

	str = getcwd(NULL, 0);
	if(str == NULL)
	{ 
		perror("getcwd");
		return(GEN_ERRNO);
	}
}

int main 



int	cd_only(t_shell *shell)
{
	char	*str;
	char	*msg;

	msg = "minishell : cd : HOME not set\n";
	str = getenv_intern(shell->env, "HOME");
	if (str == NULL)
	{
		write(2, msg, ft_strlen(msg));
		return (GEN_ERRNO);
	}
	else
	{
		if (chdir(str) == ERROR)
		{
			print_error_message("cd", str);
			return (GEN_ERRNO);
		}
	}
	// export_cwd(shell, shell->env, "PWD");
	
	return (0);
}

int	too_much_arg(void)
{
	char	*msg;

	msg = "minishell: cd : too many arguments\n";
	write(1, msg, ft_strlen(msg));
	return (GEN_ERRNO);
}

int	builtin_cd(t_shell *shell, char **argv)
{
	int	i;

	i = 1;
	while (argv[i] != NULL)
		i++;
	if (i == 1)
		return (cd_only(shell));
	if (i > 2)
		return (too_much_arg());
	if (chdir(argv[1]) == ERROR)
	{
		print_error_message("cd", argv[1]);
		return (GEN_ERRNO);
	}
	return (0);
}
