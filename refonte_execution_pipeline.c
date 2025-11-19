int exec_fork_pipe(t_shell *shell,t_exec *current, char **cmd, t_valist *env, int pipe_fd[2])
{
	pid_t child;

	// check si j'ai affaire a un built in
	// lance routine_built_in() si c'est le cas

	child = fork();
	
	if (child < 0)
		return (perror("fork: "), ERROR);
	if(child > 0)
	{ 
		close(pipe_fd[0]);
		return(child);
	}
	if (child == 0)
	{
		if (is_built_in(current->cmds[0]) != 0) // cas built in
		{
			printf("fork builtin routine\n");
			routine_builtin_pipe(shell, current, cmd, env, pipe_fd);
		}
		routine_pipe(shell, current, cmd, env, pipe_fd); // routine execve()
	}
	close(pipe_fd[0]);
	//waitpid(child, 0, 0);
	return (child);
}


int	routine_builtin_pipe(t_shell *shell, t_exec *current, char **cmd, t_valist *env, int pipe_fd[2])
{
	apply_redirection()
	execute_built_in(shell, is_built_in(cmd[0]), cmd , env);
	printf("j'ai execute mon builtin\n");
	exit(1);//fin du fork()
}

int routine_pipe(t_shell *shell,t_exec *current, char **cmd, t_valist *env, int pipe_fd[2])
{
	// !! il me faut le fd in et ou de LA cmd
	char	*my_cmd_path;
	char	**env_tab_exe;
	int	prev_fd = shell->prev_fd;

	env_tab_exe = env_list_to_envp(env);

 	if (access(cmd[0], X_OK) == 0)
		execve(cmd[0], cmd, env_tab_exe);
	
	my_cmd_path = find_my_cmd_path(cmd[0], env_tab_exe);
	if (!my_cmd_path || my_cmd_path[0] == '\0')
	{
		ft_free_tab(env_tab_exe);
		//close(fd_out);
		//close(fd_in);
		path_not_found();
	}

	// IN
	if (current->fd_in != STDIN_FILENO)
	{
		dup2(current->fd_in, STDIN_FILENO);
		close(current->fd_in);
	}
	else if (prev_fd != -1)
	{
		dup2(prev_fd, STDIN_FILENO);
		close(prev_fd);
	}
	// OUT
	if (current->fd_out != STDOUT_FILENO)
	{
		dup2(current->fd_out, STDOUT_FILENO);
		close(current->fd_out);
	}
/* 	else if (!current->next) // si pb pour les redirs de la derniere commmande .
	{
		
	} */
	else if (current->next) 
	{
		dup2(pipe_fd[1], STDOUT_FILENO);
	}

	close(pipe_fd[0]);
	close(pipe_fd[1]);
	
	execve(my_cmd_path, cmd, env_tab_exe);
	perror("execve");
	exit(1);
}