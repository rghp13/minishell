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
		exec_cmd(hold, cont->envstr);
		hold = hold->next;
	}
}

void	exec_cmd(t_cmd *cmd, char **envp)
{
	pid_t	pid;
	int		status;

	pid = 0;
	status = 0;
	printf("%s\n", cmd->abspath);
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
		if (execve(cmd->abspath, cmd->arg, envp) == -1)
		{
			perror("shell");
			exit(EXIT_FAILURE);
		}
		exit(EXIT_SUCCESS);
	}
}


int		list_get_path(t_cmd *cmd, t_env *env)
{
	t_cmd	*hold;

	hold = cmd;
	printf("%p\n", hold);
	while (hold)
	{
		hold->abspath = get_abs_path(hold->arg[0], env);
		if (hold->abspath == NULL)
			printf("FAILED TO GET ABSPATH\n");
		hold = hold->next;
	}
	return (0);
}

char	*get_abs_path(const char *src, t_env *env)
{
	char	*bin;
	char	**split;
	int		i;

	bin = get_key_val("PATH", env);
	i = -1;
	if (bin == NULL)
		return (NULL);
	split = ft_split(bin, ':');
	free(bin);
	if (split == NULL)
		return (NULL);
	while (split[++i])//SEE WHY YOU'RE NOT ENTERING THIS WHILE LOOP
	{
		if (merge_path_name(&split[i], src) != 0)
			return ((void*)(uintptr_t)ft_free_all_split(split));
		if (access(split[i], F_OK))
		{
			bin = ft_strdup(split[i]);
			ft_free_all_split(split);
			return (bin);
		}
	}
	ft_free_all_split(split);
	printf("left here\n");
	return (NULL);
}

int	merge_path_name(char **path, const char *name)
{
	char *hold;
	char *hold2;

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