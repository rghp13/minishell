#include "../includes/minishell.h"

int	exec_bultin_bin_bridge(t_cmd *cmd, t_cont *cont)
{
	if (check_builtin(cmd->arg[0]) == 1)
		run_builtin(cmd, cont);
	else
		exec_cmd(cmd, cont);
	return (0);
}

char	*get_home_path(const char *str, t_cont *cont)
{
	char	*ptr;
	char	*hold;

	ptr = get_key_val("$HOME", cont->env);
	if (!ptr)
	{
		ft_putstr_fd("bash: HOME not set\n", STDERR_FILENO);
		return (NULL);
	}
	str++;
	hold = ft_strjoin(ptr, str);
	free(ptr);
	printf("%s\n", hold);
	return (hold);
}

int	relative_path_bridge(t_cmd *cmd, t_env *env)
{
	int	len;

	len = ft_strlen(cmd->arg[0]);
	if (len >= 2 && cmd->arg[0][0] == '.' && cmd->arg[0][1] == '/')
		cmd->abspath = ft_strdup(cmd->arg[0]);
	else if (len >= 2 && cmd->arg[0][0] == '~' && cmd->arg[0][1] == '/')
		cmd->abspath = get_home_path(cmd->arg[0], env->cont);
	else
		cmd->abspath = get_abs_path(cmd->arg[0], env);
}
