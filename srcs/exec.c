#include "minishell.h"

//main function that will run one command at a time in the list
//start by taking the first command, figuring out which is the correct path
//figure out if it needs to redirect and how to redirect

void	exec_cmd(t_cont *cont)
{
	list_get_path(cont->cmd, cont->env);

}

int		list_get_path(t_cmd *cmd, t_env *env)
{
	t_cmd	*hold;

	hold = cmd;
	while (hold)
	{
		hold->abspath = get_abs_path(hold->arg[0], env);
		
	}
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
	while (split[++i])
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
	return (NULL);
}

int	merge_path_name(char **path, const char *name)
{
	char *hold;
	char *hold2;

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