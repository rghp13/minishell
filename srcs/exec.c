#include "minishell.h"

//main function that will run one command at a time in the list
//start by taking the first command, figuring out which is the correct path
//figure out if it needs to redirect and how to redirect

void	exec_cmd(t_env *env, t_cmd *cmd)
{
	return ;
}

void	get_abs_path(const char *src, t_env *env)
{
	char	*bin;
	char	**split;
	int		i;

	split = ft_split(get_key_val("PATH", env), ':');
	
	return ;
}