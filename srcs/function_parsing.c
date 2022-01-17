#include "../includes/minishell.h"

int	break_pipes(t_cmd *list)
{
	int		i;
	t_cmd	*current;
	char	**str;

	current = list;
	while (current)
	{
		if (has_pipe(current->cmd))
		{
			str = ft_special_split(current->cmd, '|');
			free(current->cmd);
			current->cmd = str[0];
			i = 1;
			while (str[i])
			{
				current->pipechain = add_cmd(current->pipechain, str[i]);
				i++;
			}
			free(str);
		}
		current = current->next;
	}
	return (0);
}

int	extract_input(t_cmd *cmd, int redirectors, int size)
{
	int		i;
	int		j;
	char	*result;

	i = 0;
	while (cmd->cmd[i] && (cmd->cmd[i - 1] != '<' || cmd->cmd[i] == '<'))
		i++;
	j = i;
	while (cmd->cmd[j] && cmd->cmd[j] != '<' && cmd->cmd[j] != '>')
		j++;
	if (!cmd->cmd[i])
		return (0);
	if (small_malloc((void **)&cmd->input, sizeof(char) * ((j - i) + 1)))
		return (0);
	ft_strlcpy(cmd->input, &cmd->cmd[i], (j - i) + 1);
	if ((redirectors >> 0) & 1U)
		cmd->input_type = 0;
	else
		cmd->input_type = 1;
	if (i < size)
		return (i - (1 + cmd->input_type));
	return (size);
}

int	extract_outputs(t_cmd *cmd, int redirectors, int size)
{
	int		i;
	int		j;
	char	*result;

	i = 0;
	while (cmd->cmd[i] && (cmd->cmd[i - 1] != '>' || cmd->cmd[i] == '>'))
		i++;
	j = i;
	while (cmd->cmd[j] && cmd->cmd[j] != '>' && cmd->cmd[j] != '<')
		j++;
	if (!cmd->cmd[i])
		return (0);
	if (small_malloc((void **)&cmd->output, sizeof(char) * ((j - i) + 1)))
		return (0);
	ft_strlcpy(cmd->output, &cmd->cmd[i], (j - i) + 1);
	if ((redirectors >> 2) & 1U)
		cmd->output_type = 0;
	else
		cmd->output_type = 1;
	if (i < size)
		return (i - (1 + cmd->output_type));
	return (size);
}

int	create_argv(t_cmd *cmd)
{
	int		redirectors;
	char	*cmd_no_red;
	int		size_arg;

	size_arg = ft_strlen(cmd->cmd);
	redirectors = has_redirector(cmd->cmd);
	if (redirectors)
	{
		if (((redirectors >> 0) & 1U) || ((redirectors >> 1) & 1U))
			size_arg = extract_input(cmd, redirectors, size_arg);
		if (((redirectors >> 2) & 1U) || ((redirectors >> 3) & 1U))
			size_arg = extract_outputs(cmd, redirectors, size_arg);
	}
	if (small_malloc((void **)&cmd_no_red, sizeof(char) * (size_arg + 1)))
		return (0);
	ft_strlcpy(cmd_no_red, cmd->cmd, size_arg + 1);
	cmd->arg = ft_special_split(cmd_no_red, ' ');
	if (cmd_no_red != cmd->cmd)
		free (cmd_no_red);
	return (0);
}

int	parse_command(char *line, t_cmd **list)
{
	int		i;
	char	**str;

	i = 0;
	str = ft_special_split(line, ';');
	while (str[i])
	{
		*list = add_cmd(*list, str[i]);
		i++;
	}
	free(str);
	free(line);
	break_pipes(*list);
	argv_parse(*list);
	return (0);
}
