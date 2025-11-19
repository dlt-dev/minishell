	
	
int apply_rediredtion()
{
	int	prev_fd;

	prev_fd = shell->prev_fd;
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
	else if (current->next) 
	{
		dup2(pipe_fd[1], STDOUT_FILENO);
	}

	close(pipe_fd[0]);
	close(pipe_fd[1]);
	return(0);
}