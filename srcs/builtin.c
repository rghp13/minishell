#include "minishell.h"

int	check_builtin(const char *cmd)
{
	if (cmd == NULL)
		return (-1);
	if (ft_stringcomp(cmd, "echo") == 0 || ft_stringcomp(cmd, "cd") == 0 || \
	ft_stringcomp(cmd, "pwd") == 0 || ft_stringcomp(cmd, "export") == 0 || \
	ft_stringcomp(cmd, "unset") == 0 || ft_stringcomp(cmd, "env") == 0 || \
	ft_stringcomp(cmd, "exit") == 0)
		return (1);
	else
		return (0);
}

void	run_builtin(t_cmd *cmd, t_cont *cont)
{
	int	(*builtin_func)(char**, t_cont*);

	builtin_func = NULL;
	if (ft_stringcomp(cmd->arg[0], "echo") == 0)
		printf("entered echo\n");
	else if (ft_stringcomp(cmd->arg[0], "cd") == 0)
		printf("entered cd\n");
	else if (ft_stringcomp(cmd->arg[0], "pwd") == 0)
		printf("entered pwd\n");
	else if (ft_stringcomp(cmd->arg[0], "export") == 0)
		builtin_func = &builtin_export;
	else if (ft_stringcomp(cmd->arg[0], "unset") == 0)
		builtin_func = &builtin_unset;
	else if (ft_stringcomp(cmd->arg[0], "env") == 0)
		printf("entered env\n");
	else if (ft_stringcomp(cmd->arg[0], "exit") == 0)
		printf("entered exit\n");
	else
		return ;
	fork_builtin(cmd, cont, builtin_func);
}

void	fork_builtin(t_cmd *cmd, t_cont *cont, int \
(*builtin_func)(char **, t_cont *))
{
	int		status;
	pid_t	pid;

	status = 0;
	if (builtin_func == NULL)
	{
		printf("NULL FUNC POINTER\n");
		return ;
	}
	pid = fork();
	if (pid == -1)
		perror("fork");
	else if (pid > 0)
	{
		wait(&status);
		kill(pid, SIGTERM);
		cont->exit_status = status;
		printf("Success\n");
	}
	else
		exit(builtin_func(cmd->arg, cont));
	return ;
}
