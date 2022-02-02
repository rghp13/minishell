#include "../includes/minishell.h"

int	prepare_redirection(t_cmd *cmd, t_cont *cont)
{
	if (cmd->input_type > -1)
	{
		if (cmd->input_type == 0)
			cont->fd_in = open(cmd->input, O_RDONLY);
		else if (cmd->input_type == 1)
			cont->fd_in = open(cmd->input, O_RDONLY); //This needs to be changed for <<
		if (cont->fd_in == -1)
			return (-1);
		dup2(cont->fd_in, 0);
		close(cont->fd_in);
	}
	if (cmd->output_type > -1)
	{
		if (cmd->output_type == 0)
			cont->fd_out = open(cmd->output, O_WRONLY | O_TRUNC | O_CREAT);
		else if (cmd->output_type == 1)
			cont->fd_out = open(cmd->output, O_WRONLY | O_APPEND | O_CREAT);
		if (cont->fd_out == -1)
			return (-2);
		dup2(cont->fd_out, 1);
		close(cont->fd_out);
	}
	if (check_builtin(cmd->arg[0]) == 1)
		run_builtin(cmd, cont);
	else
		exec_cmd(cmd, cont);
	fd_close(cont);
	fd_reset(cont);
	return (0);
}