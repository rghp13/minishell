#include "../includes/minishell.h"

int	exec_bultin_bin_bridge(t_cmd *cmd, t_cont *cont)
{
	struct termios	t;

	tcgetattr(0, &t);
	t.c_cc[VQUIT] = 034;
	tcsetattr(0, TCSANOW, &t);
	if (check_builtin(cmd->arg[0]) == 1)
		run_builtin(cmd, cont);
	else
		exec_cmd(cmd, cont);
	tcgetattr(0, &t);
	t.c_cc[VQUIT] = 0;
	tcsetattr(0, TCSANOW, &t);
	return (0);
}
//possibly removing this function
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
	//else if (len >= 2 && cmd->arg[0][0] == '~' && cmd->arg[0][1] == '/')
		//cmd->abspath = get_home_path(cmd->arg[0], env->cont);
	else
	{
		cmd->abspath = get_abs_path(cmd->arg[0], env);
	}
	return (0);
}

int	err_ret_value(int erno, t_cont *cont, t_cmd *cmd)
{
	ft_putnbr_fd(erno, STDERR_FILENO);
	ft_putchar_fd('\n', STDERR_FILENO);
	if (cmd->abspath == NULL && access(cmd->arg[0], F_OK) == 0)//exists but not on path
	{
		if (access(cmd->arg[0], X_OK))//no exec permission
			return (126);
	}
	if (cmd->abspath == NULL)//cmd not found
		return (127);
	if (erno == 13)
		return (126);
	return (1);
}

void	error_status(t_cont *cont)
{
	perror("Bash");
	cont->exit_status = 1;
	return ;
}