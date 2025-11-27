/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Part1_Prompt.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoesterl <aoesterl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/30 15:40:27 by aoesterl          #+#    #+#             */
/*   Updated: 2025/11/27 12:33:07 by aoesterl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	replace_by_tilde(t_valist *env, t_prompt *invite, int *len_home)
{
	int		i;
	char	*home;

	home = getenv_intern(env, "HOME");
	if (home == NULL)
		return (1);
	i = ft_strlen(home);
	if (ft_strncmp(home, invite->cwd, i) == 0)
	{
		*len_home = i;
		return (0);
	}
	return (1);
}

char	*color_of_exit(t_shell *shell)
{
	if (shell->exit_status == 0)
		return (GREEN);
	return (RED);
}

static int	len_prompt(t_shell *shell, t_valist *env, int *len_home,
		char *exit_status)
{
	int			i;
	t_prompt	*invite;

	invite = &shell->invite;
	i = 0;
	invite->color_exit = color_of_exit(shell);
	i += ft_strlen(invite->color_exit);
	i += ft_strlen(exit_status);
	i += ft_strlen("-> ");
	i += ft_strlen(invite->color_user);
	i += ft_strlen(invite->user);
	i += ft_strlen(" ");
	i += ft_strlen(invite->color_cwd);
	if (replace_by_tilde(env, invite, len_home) == 0)
		i += ft_strlen("~");
	i += ft_strlen(invite->cwd + *len_home);
	i += ft_strlen(invite->color_reset);
	i += ft_strlen("$ ");
	return (i);
}

static char	*create_prompt(t_shell *shell, t_valist *env, t_prompt *invite)
{
	char	*p;
	char	*exit_s;
	int		len_home;

	exit_s = ft_itoa(shell->exit_status);
	if (exit_s == NULL)
		return (NULL);
	len_home = 0;
	p = malloc(sizeof(char) * (len_prompt(shell, env, &len_home, exit_s) + 1));
	if (p == NULL)
		return (free(exit_s), NULL);
	p[0] = '\0';
	ft_strcat(invite->color_exit, p);
	ft_strcat(exit_s, p);
	ft_strcat("-> ", p);
	ft_strcat(invite->color_user, p);
	ft_strcat(invite->user, p);
	ft_strcat(" ", p);
	ft_strcat(invite->color_cwd, p);
	if (len_home != 0)
		ft_strcat("~", p);
	ft_strcat(&invite->cwd[len_home], p);
	ft_strcat(invite->color_reset, p);
	ft_strcat("$ ", p);
	return (free(exit_s), p);
}

int	get_prompt(t_shell *shell, t_valist *env, t_prompt *invite)
{
	invite->user = getenv_intern(env, "USER");
	if (invite->user == NULL || *invite->user == '\0')
		invite->user = "Unknown";
	invite->cwd = getcwd(NULL, 0);
	if (invite->cwd == NULL)
	{
		invite->cwd = ft_strdup("no_where");
		if (invite->cwd == NULL)
			return (ERROR);
	}
	invite->prompt = create_prompt(shell, env, invite);
	free(invite->cwd);
	invite->cwd = NULL;
	if (invite->prompt == NULL)
		return (ERROR);
	return (0);
}

/**
 * @brief environnement pour tester plusieurs fonctions pour s'assurer qu'elles
 * fonctionnent bien avant de les incorporer dans le projet. si une fonction a
 * ete test et a l'air de bien fonctionner, on peut mettre un commentaire
 * GOODJOB sous la fonction: ce qui veut dire que la fonction a subit une
 * batterie de test.
 **/
