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
