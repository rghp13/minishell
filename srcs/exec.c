#include "minishell.h"

//main function that will run one command at a time in the list
//start by taking the first command, figuring out which is the correct path
//figure out if it needs to redirect and how to redirect

void	exec_main(t_cont *cont)
{
	t_cmd	*hold;

	hold = cont->cmd;
	list_get_path(cont->cmd, cont->env);
	while (hold)
	{
		if (check_builtin(hold->arg[0]) == 1)
			run_builtin(hold, cont);
		else
			exec_cmd(hold, cont->envstr);
		hold = hold->next;
	}
}

void	exec_cmd(t_cmd *cmd, char **envp)
{
	pid_t	pid;
	int		status;
	int		ret;

	pid = 0;
	status = 0;
	ret = 0;
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
		ret = execve(cmd->abspath, cmd->arg, envp);
		if (ret == -1)
		{
			perror("shell");
			exit(EXIT_FAILURE);
		}
		exit(EXIT_SUCCESS);
	}
}

int	list_get_path(t_cmd *cmd, t_env *env)
{
	t_cmd	*hold;

	hold = cmd;
	while (hold)
	{
		hold->abspath = get_abs_path(hold->arg[0], env);
		hold = hold->next;
	}
	return (0);
}

char	*get_abs_path(const char *src, t_env *env)
{
	char	*bin;
	char	**split;
	int		i;

	bin = get_key_val("$PATH", env);
	i = -1;
	if (bin == NULL)
		return (NULL);
	split = ft_split(bin, ':');
	free(bin);
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
