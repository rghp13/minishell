#include "minishell.h"

/*
**main function that will run one command at a time in the list
**start by taking the first command, figuring out which is the correct path
**figure out if it needs to redirect and how to redirect
*/

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
			exec_cmd(hold, cont);
		hold = hold->next;
	}
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
		wait(&status);
		kill(pid, SIGTERM);
		cont->exit_status = status;
	}
	else
	{
		if (execve(cmd->abspath, cmd->arg, cont->envstr) == -1)
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
	int		len;

	hold = cmd;
	while (hold)
	{
		len = ft_strlen(hold->arg[0]);
		if (len >= 2 && hold->arg[0][0] == '.' && hold->arg[0][1] == '/')
			hold->abspath = ft_strdup(hold->arg[0]);
		else if (len >= 2 && hold->arg[0][0] == '~' && hold->arg[0][1] == '/')
			hold->abspath = get_home_path(hold->arg[0], env->cont);
		else
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
