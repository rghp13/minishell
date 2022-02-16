#include "../includes/minishell.h"

int	parsing_manager(char *parsed_line, t_cont *cont)
{
	int	val;

	if (syntax_check(parsed_line))
	{
		ft_putstr_fd("Syntax Error\n", STDERR_FILENO);
		cont->exit_status = 2;
		return (-1);
	}
	if (parse_command(parsed_line, &cont->cmd))
	{
		ft_putstr_fd("Parsing Error\n", STDERR_FILENO);
		cont->exit_status = 1;
		return (-1);
	}
	if (substitute_variables(cont))
	{
		ft_putstr_fd("Variable Error\n", STDERR_FILENO);
		cont->exit_status = 1;
		return (-1);
	}
	val = argv_loop(cont);
	if (val)
	{
		if (val == -1)
			ft_putstr_fd("Command not specified\n", STDERR_FILENO);
		if (val == -2)
			ft_putstr_fd("File Error\n", STDERR_FILENO);
		cont->exit_status = 1;
		return (-1);
	}
	return (0);
}

int	execution_manager(t_cont *cont)
{
	int	value;

	value = exec_main(cont);
	while (wait(NULL) > 0)
		;
	if (value == -1)
	{
		ft_putstr_fd("Execution Error\n", STDERR_FILENO);
		cont->exit_status = 1;
	}
	else if (value == -2)
	{
		ft_putstr_fd("File Error\n", STDERR_FILENO);
		cont->exit_status = 1;
	}
	fd_close(cont);
	fd_reset(cont);
	return (value);
}