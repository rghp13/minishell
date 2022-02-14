#include "../includes/minishell.h"

int	update_bracket_status(int bracket, char c)
{
	int	val;

	val = 0;
	if (c == '\'')
		val = 1;
	else if (c == '\"')
		val = 2;
	if (bracket && bracket == val)
		return (0);
	else if (!bracket && val)
		return (val);
	return (bracket);
}

int	has_redirector(char *str)
{
	int	i;
	int	bracket;
	int	result;

	i = 0;
	bracket = 0;
	result = 0;
	while (str[i])
	{
		bracket = update_bracket_status(bracket, str[i]);
		if (!bracket)
		{
			if (str[i] == '<' && str[i + 1] != '<' && str[i - 1] != '<')
				result |= 1UL << 0;
			else if (str[i] == '<' && str[i + 1] == '<')
				result |= 1UL << 1;
			else if (str[i] == '>' && str[i + 1] != '>' && str[i - 1] != '>')
				result |= 1UL << 2;
			else if (str[i] == '>' && str[i + 1] == '>')
				result |= 1UL << 3;
		}
		i++;
	}
	return (result);
}

int	argv_loop(t_cont *cont)
{
	t_cmd	*current;
	t_cmd	*pipe;

	current = cont->cmd;
	pipe = NULL;
	while (current)
	{
		pipe = current->pipechain;
		while (pipe)
		{
			if (create_argv(pipe))
			{
				cont->exit_status = 2;
				return (-1);
			}
			pipe = pipe->next;
		}
		if (create_argv(current))
		{
			cont->exit_status = 2;
			return (-1);
		}
		current = current->next;
	}
	return (0);
}

int	free_cmd(t_cmd *cmd)
{
	free(cmd->cmd);
	if (cmd->arg)
		ft_free_all_split(cmd->arg);
	if (cmd->abspath)
		free(cmd->abspath);
	if (cmd->input)
		free(cmd->input);
	if (cmd->output)
		free(cmd->output);
	free(cmd);
	return (0);
}
