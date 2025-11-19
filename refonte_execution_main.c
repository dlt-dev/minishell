
#include "minishell.h"





int handle_simple_command ()
{ 
	if (command_nb == 1) // CAS DE LA COMMANDE UNIQUE
	{
		if (cmd_list->cmds[0] && (is_built_in(cmd_list->cmds[0]) != 0)) // BUILT IN
		{
			if (execute_built_in(shell, is_built_in(cmd_list->cmds[0]), cmd_list->cmds, env) == ERROR)
				return (ERROR);
		}
		else if (cmd_list->cmds[0] && (is_built_in(cmd_list->cmds[0]) == 0)) // EXECVE
		{
			if (exec_fork_one(shell, cmd_list->cmds, env) == ERROR)
				return (ERROR);
		}
	}
}






int	manage_execution(t_shell *shell, t_valist *env) // nombre de commande , char **cmds
{
	int i;
	i = 0;
	t_exec *cmd_list = shell->cmd_lst;
	t_exec *current = cmd_list;
	int command_nb = ft_lstexec_size(cmd_list);
	int pipe_fd[2];
	

	if (check_all_redir(shell) == ERROR) // CHECK REDIR ET FIND LES FD SI BESOIN
		return (ERROR);

	test_print_fd(cmd_list); // TEST PRINT

	if (command_nb == 1) // CAS DE LA COMMANDE UNIQUE
	{
		if (cmd_list->cmds[0] && (is_built_in(cmd_list->cmds[0]) != 0)) // BUILT IN
		{
			if (execute_built_in(shell, is_built_in(cmd_list->cmds[0]), cmd_list->cmds, env) == ERROR)
				return (ERROR);
		}
		else if (cmd_list->cmds[0] && (is_built_in(cmd_list->cmds[0]) == 0)) // EXECVE
		{
			if (exec_fork_one(shell, cmd_list->cmds, env) == ERROR)
				return (ERROR);
		}
	}
	else if (command_nb > 1) // CAS COMMANDE MULTPLES (PIPES)
	{
		pid_t pid; 
		printf("pipe routine\n");
		while (current)
		{
			if (pipe(pipe_fd) < 0)
				return (perror("pipe"), ERROR);
			printf("execute command [%d]\n", i);
			pid = exec_fork_pipe(shell, current, current->cmds, env, pipe_fd);
			if (pid == ERROR)
				return (ERROR);
			current = current->next;
			i++;
			if(shell->prev_fd != -1)
				close(shell->prev_fd);
			shell->prev_fd = pipe_fd[0];
			
		}
		//waitpid(pid, 0, 0); // attends TOUT les processus - doit lancer wait(evec stutus et pid du dernier enfant)
/* 		while (waitpid(-1, 0, 0) != ERROR)
		{
			continue ;
		} */
		//waitpid(-1, 0, 0);


	}
	return (0);
}