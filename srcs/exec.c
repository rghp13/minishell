#include "minishell.h"

/*
**main function that will run one command at a time in the list
**start by taking the first command, figuring out which is the correct path
**figure out if it needs to redirect and how to redirect
*/

int	exec_main(t_cont *cont)
{
	t_cmd	*hold;

	hold = cont->cmd;
	list_get_path(cont->cmd, cont->env);
	while (hold)
	{
		if (hold->pipechain)
		{
			if (pipe_execution(hold, cont))
				error_status(cont);
			fd_reset(cont);
		}
		else if (hold->input_type > -1 || hold->output_type > -1)
		{
			if (!prepare_redirection(hold, cont))
				exec_bultin_bin_bridge(hold, cont);
			else
				error_status(cont);
			fd_close(cont);
			fd_reset(cont);
		}
		else
			exec_bultin_bin_bridge(hold, cont);
		hold = hold->next;
	}
	return (0);
}

void	exec_cmd(t_cmd *cmd, t_cont *cont)
{
	pid_t	pid;
	int		status;

	status = 0;
	pid = fork();
	if (pid == -1)
		perror("fork");
	else if (pid > 0)
	{
		cont->child_pid = pid;
		wait(&status);
		kill(pid, SIGTERM);
		if (WIFEXITED(status))
			cont->exit_status = WEXITSTATUS(status);
		else if (WIFSIGNALED(status))
			cont->exit_status = (128 + WTERMSIG(status));
		cont->child_pid = 0;
	}
	else
	{
		if (execve(cmd->abspath, cmd->arg, cont->envstr) == -1)
		{
			perror("shell");
			exit(err_ret_value(errno, cont, cmd));
		}
		exit(EXIT_SUCCESS);
	}
}

int	list_get_path(t_cmd *cmd, t_env *env)
{
	t_cmd	*hold;
	t_cmd	*pipe;
	int		len;

	hold = cmd;
	while (hold)
	{
		relative_path_bridge(hold, env);
		pipe = hold->pipechain;
		while (pipe)
		{
			relative_path_bridge(pipe, env);
			pipe = pipe->next;
		}
		hold = hold->next;
	}
	return (0);
}

char	*get_abs_path(const char *src, t_env *env)
{
	char	*bin;
	char	**split;
	int		i;

	i = -1;
	if (ft_strchr(src, '/'))
		return (find_relative_path(src, env->cont));
	split = ret_path_split(env);
	if (split == NULL)
		return (NULL);
	while (split[++i])
	{
		if (merge_path_name(&split[i], src) != 0)
			return ((void *)(uintptr_t)ft_free_all_split(split));
		if (access(split[i], F_OK) != -1)
		{
			bin = ft_strdup(split[i]);
			ft_free_all_split(split);
			return (bin);
		}
	}
	ft_free_all_split(split);
	return (NULL);
}

int	merge_path_name(char **path, const char *name)
{
	char	*hold;
	char	*hold2;

	if (*path == NULL)
		return (1);
	hold = ft_strjoin(*path, "/");
	if (hold == NULL)
		return (1);
	hold2 = ft_strjoin(hold, name);
	free(hold);
	if (hold2 == NULL)
		return (1);
	free(*path);
	*path = hold2;
	return (0);
}
