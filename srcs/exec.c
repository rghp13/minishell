#include "minishell.h"

void	exec_cmd(char **cmd, char **envp)
{
	pid_t	pid;
	int		status;

	pid = 0;
	status = 0;
	pid = fork();
	if (pid == -1)
		perror("fork");
	else if (pid > 0)
	{
		waitpid(pid, &status, 0);
		kill(pid, SIGTERM);
	}
	else
	{
		if (execve(cmd[0], cmd, "/usr/local/bin/$cmd") == -1)
			perror("Shell");
		exit(EXIT_FAILURE);
	}
}

void	get_abs_path(char **cmd)
{
	char	*path;
	char	*bin;

	path = strdup(getenv("PATH"));
	return ;
}