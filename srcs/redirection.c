#include "../includes/minishell.h"

int	di_strcomp(char *ret_line, char *endstr)
{
	int	i;

	i = 0;
	while (ret_line[i] && endstr[i] && ret_line[i] == endstr[i])
		i++;
	if (ret_line[i] == endstr[i] || ret_line[i] == '\n')
		return (0);
	return (1);
}

int	double_input(t_cmd *cmd, t_cont *cont)
{
	char	*ret_str;
	char	*final;
	char	*temp;
	int		pipes[2];

	final = calloc(1, sizeof(char));
	final[0] = '\0';
	while (1)
	{
		ret_str = readline("> ");
		if (!di_strcomp(ret_str, cmd->input))
			break;
		temp = ft_strjoin(final, ret_str);
		free(final);
		final = temp;
	}
	pipe(pipes);
	write(pipes[1], final, ft_strlen(final));
	close(pipes[1]);
	free(final);
	return (pipes[0]);
}

int	prepare_redirection(t_cmd *cmd, t_cont *cont)
{
	if (cmd->input_type > -1)
	{
		if (cmd->input_type == 0)
			cont->fd_in = open(cmd->input, O_RDONLY, 0664);
		else if (cmd->input_type == 1)
			cont->fd_in = double_input(cmd, cont);
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
