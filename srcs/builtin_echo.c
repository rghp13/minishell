#include "minishell.h"

int	builtin_echo(char **argv, t_cont *cont)
{
	int	n;
	int	flag;
	int	i;

	i = 1;
	n = 0;
	flag = 0;
	set_sig();
	while (argv[i] && is_option(argv[i], cont))
	{
		n = 1;
		if (argv[++i] == NULL)
			return (0);
	}
	while (argv[i])
	{
		if (flag == 0)
			flag++;
		else
			write(STDOUT_FILENO, " ", 1);
		ft_putstr_fd(argv[i++], STDOUT_FILENO);
	}
	if (n == 0)
		write(STDOUT_FILENO, "\n", 1);
	return (0);
}

void	set_sig(void)
{
	struct sigaction	sa;
	
	sa.sa_handler = SIG_DFL;
	sa.sa_flags = SA_RESTART;
	sigaction(SIGINT, &sa, NULL);
	sigaction(SIGQUIT, &sa, NULL);
}

int	is_option(const char *str, t_cont *cont)
{
	int	len;
	int	i;

	i = 1;
	len = ft_strlen(str);
	if (len < 2 || str[0] != '-')
		return (0);
	while (str[i])
	{
		if (str[i] != 'n')
			return (0);
		i++;
	}
	return (1);
}

void	builtin_exec_echo(t_cmd *cmd, t_cont *cont)
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
		exit(builtin_echo(cmd->arg, cont));
}