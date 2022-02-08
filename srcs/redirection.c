#include "../includes/minishell.h"

int	prepare_redirection(t_cmd *cmd, t_cont *cont)
{
	if (cmd->input_type > -1)
	{
		if (cmd->input_type == 0)
			cont->fd_in = open(cmd->input, O_RDONLY, 0664);
		else if (cmd->input_type == 1)
			cont->fd_in = open(cmd->input, O_RDONLY, 0664); //This needs to be changed for <<
		if (cont->fd_in == -1)
			return (-1);
		dup2(cont->fd_in, 0);
		close(cont->fd_in);
	}
	if (cmd->output_type > -1)
	{
		if (cmd->output_type == 0)
			cont->fd_out = open(cmd->output, O_WRONLY | O_TRUNC | O_CREAT, 0664);
		else if (cmd->output_type == 1)
			cont->fd_out = open(cmd->output, O_WRONLY | O_APPEND | O_CREAT, 0664);
		if (cont->fd_out == -1)
			return (-2);
		dup2(cont->fd_out, 1);
		close(cont->fd_out);
	}
	return (0);
}
