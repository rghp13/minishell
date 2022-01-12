#include "minishell.h"

//main function that will run one command at a time in the list
//start by taking the first command, figuring out which is the correct path
//figure out if it needs to redirect and how to redirect

void	exec_cmd(t_env *env, t_cmd *cmd)
{
	return ;
}

char	*get_abs_path(const char *src, t_env *env)
{
	char	*bin;
	char	*hold;
	char	**split;
	int		i;

	bin = get_key_val("PATH", env);
	i = 0;
	if (bin == NULL)
		return (NULL);
	split = ft_split(bin, ':');
	free(bin);
	if (split == NULL)
		return (NULL);
	while (split[i])
	{
		split[i] = ft_strjoin(split[i], "/");
		if (hold == NULL)
		{
			ft_free_all_split(split);
			return (NULL);
		}
		split[i] = ft_strjoin(split[i], src);

	}
	return (bin);
}