#include "minishell.h"

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
	apply_redirection(shell, current);
	execute_built_in(shell, is_built_in(cmd[0]), cmd , env);
	printf("j'ai execute mon builtin\n");
	exit(1);//fin du fork()
}

int routine_pipe(t_shell *shell,t_exec *current, char **cmd, t_valist *env, int pipe_fd[2])
{
	// !! il me faut le fd in et ou de LA cmd
	char	*my_cmd_path;
	char	**env_tab;

	env_tab = env_list_to_envp(env);
	apply_redirection(shell, current, pipe_fd);


 	if (access(cmd[0], X_OK) == 0)
		execve(cmd[0], cmd, env_tab);
	
	my_cmd_path = find_my_cmd_path(cmd[0], env_tab);
	if (my_cmd_path == NULL || my_cmd_path[0] == '\0')
	{
		ft_free_tab(env_tab);
		//close(fd_out);
		//close(fd_in);
		path_not_found();
	}
	execve(my_cmd_path, cmd, env_tab);
	perror("execve");
	exit(1);
}