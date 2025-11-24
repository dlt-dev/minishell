
#include "minishell.h"

int waitpid_verify_status (pid_t pid)
{ 
	int status;
		
	waitpid(pid, &status, 0);
	if(WIFEXITED(status) != 0)
		return(WEXITSTATUS(status));
	if(WIFSIGNALED(status) != 0)
		return(WTERMSIG(status) + 128);
	return(0);
}

int	wait_and_status(t_shell *shell, pid_t last_pid)
{
	//int status;
	//pid_t pid_childs;

	//waitpid(last_pid, &status, 0);
	shell->exit_status = waitpid_verify_status(last_pid);
	while (waitpid(-1, 0, 0) != ERROR)
		continue ;
	return (0);
}

int	handle_simple_command(t_shell *shell, t_exec *cmd_lst, t_valist *env) // CAS DE LA COMMANDE UNIQUE
{
	if (cmd_lst->cmds[0] && (is_built_in(cmd_lst->cmds[0]) != 0)) // BUILT IN
	{
		if (execute_built_in(shell, is_built_in(cmd_lst->cmds[0]), cmd_lst->cmds, env) == ERROR)
			return (ERROR);
	}
	else if (cmd_lst->cmds[0] && (is_built_in(cmd_lst->cmds[0]) == 0)) // EXECVE
	{
		if (exec_fork_one(shell, cmd_lst->cmds, env) == ERROR)
			return (ERROR);
	}
	return (0);
}

int	handle_pipe_command(t_shell *shell, t_exec *current, t_valist *env)
{
	int pipe_fd[2];
	pid_t pid;

	// int i = 0; // TEST PRINT
	// printf("pipe routine\n"); // TEST PRINT
	while (current)
	{
		//close(pipe_fd[0]);
		if (pipe(pipe_fd) == ERROR) // cree un pipe pour chaques commandes
			return (perror("pipe"), ERROR);
		// printf("execute command [%d]\n", i); // TEST PRINT
		// i++; // TEST PRINT
		pid = exec_fork_pipe(shell, current, current->cmds, env, pipe_fd);
		if (pid == ERROR)
			return (close(pipe_fd[0]), close(pipe_fd[1]), ERROR);
		current = current->next;
	}
	wait_and_status(shell, pid);
	close(pipe_fd[0]);
	return (0);
}

// int	handle_pipe_command(t_shell *shell, t_exec *current, t_valist *env)
// {
// 	int pipe_fd[2];
// 	pid_t pid;

// 	// int i = 0; // TEST PRINT
// 	// printf("pipe routine\n"); // TEST PRINT
// 	while (current)
// 	{
// 		//close(pipe_fd[0]);
// 		if (pipe(pipe_fd) == ERROR) // cree un pipe pour chaques commandes
// 			return (perror("pipe"), ERROR);
// 		// printf("execute command [%d]\n", i); // TEST PRINT
// 		// i++; // TEST PRINT
// 		pid = exec_fork_pipe(shell, current, current->cmds, env, pipe_fd);
// 		if (pid == ERROR)
// 			return (close(pipe_fd[0]), close(pipe_fd[1]), ERROR);
// 		current = current->next;
// 		if(shell->prev_fd != -1)
// 			close(shell->prev_fd);
// 		shell->prev_fd = pipe_fd[0];
// 		close(pipe_fd[1]);
		
// 	}
// 	wait_and_status(shell, pid);
// 	return (0);
// }

int	manage_execution(t_shell *shell, t_valist *env) // nombre de commande , char **cmds
{
	int command_nb;
	int check_failed;
	command_nb = ft_lstexec_size(shell->cmd_lst);

	if (!shell->cmd_lst || !shell->cmd_lst->cmds) //!!\\ ADD POuR EVITER SEGFAULT REDIR UNIQUE
		return (0);
	printf("commande_nb = %d\n", command_nb);// TEST PRINT
	printf("prev_fd = %d\n", shell->prev_fd);// TEST PRINT
	test_print_fd(shell->cmd_lst); //  TESTPRINT
	if (command_nb == 1)
	{
		check_failed = handle_simple_command(shell, shell->cmd_lst, env);
		if(check_failed == ERROR)
			return(ERROR);
	}
	else if (command_nb > 1)
	{
		if(handle_pipe_command(shell, shell->cmd_lst, env) == ERROR)
			return(ERROR);
	}
	return (0);
}
