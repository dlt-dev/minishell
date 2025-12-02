/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Part5_waitpid.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoesterl <aoesterl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/02 03:32:27 by aoesterl          #+#    #+#             */
/*   Updated: 2025/12/02 03:32:48 by aoesterl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	waitpid_verify_status(pid_t pid)
{
	int	status;

	if (waitpid(pid, &status, 0) < 0)
		return (perror("Waitpid: "), 1);
	if (WIFEXITED(status) != 0)
		return (WEXITSTATUS(status));
	if (WIFSIGNALED(status) != 0)
	{
		if (WTERMSIG(status) == SIGQUIT)
			write_str_fd("Quit (core dumped)", 2);
		return (WTERMSIG(status) + 128);
	}
	return (0);
}

int	wait_and_status(t_shell *shell, pid_t last_pid)
{
	int	flag_n;
	int	status;

	status = 0;
	flag_n = 0;
	shell->exit_status = waitpid_verify_status(last_pid);
	while (waitpid(-1, &status, 0) != ERROR)
	{
		if (WIFSIGNALED(status) != 0)
			flag_n = 1;
	}
	if (shell->exit_status == SIGINT + 128)
		flag_n = 1;
	if (flag_n == 1)
		write(1, "\n", 1);
	handle_shell_sig(shell);
	return (0);
}