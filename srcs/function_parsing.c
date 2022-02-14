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

int	is_redirect_separator(char c)
{
	if (c == ' ' || c == '>' || c == '<' || c == '\0')
		return (1);
	return (0);
}

int	extract_redirector(t_cmd *cmd, int i)
{
	int	j;
	int	mode;

	if (cmd->cmd[i] == ' ')
		return (0);
	mode = i;
	while (cmd->cmd[i] && is_redirect_separator(cmd->cmd[i]))
		i++;
	j = i;
	while (cmd->cmd[j] && !is_redirect_separator(cmd->cmd[j]))
		j++;
	if (cmd->cmd[mode] == '>')
	{
		cmd->output_type = (cmd->cmd[mode] == cmd->cmd[mode + 1]);
		if (small_malloc((void **)&cmd->output, sizeof(char) * (j - i)))
			return (-1);
		ft_memcpy(cmd->output, &cmd->cmd[i], j - i);
		cmd->output[j - i] = '\0';
	}
	else if (cmd->cmd[mode] == '<')
	{
		cmd->input_type = (cmd->cmd[mode] == cmd->cmd[mode + 1]);
		if (small_malloc((void **)&cmd->input, sizeof(char) * (j - i)))
			return (-1);
		ft_memcpy(cmd->input, &cmd->cmd[i], j - i);
		cmd->input[j - i] = '\0';
	}
	while (cmd->cmd[j] && is_redirect_separator(cmd->cmd[j]))
		j++;
	return (j - mode);
}

int	create_argv(t_cmd *cmd)
{
	int		i;
	int		j;
	int		size;
	int		bracket;

	i = 0;
	bracket = 0;
	if (!cmd->cmd)
		return (-1);
	while (cmd->cmd[i])
	{
		bracket = update_bracket_status(bracket, cmd->cmd[i]);
		if (!bracket && is_redirect_separator(cmd->cmd[i]))
		{
			size = extract_redirector(cmd, i);
			if (size == -1)
				printf("Argv error\n");
			j = i;
			while (cmd->cmd[j + size])
			{
				cmd->cmd[j] = cmd->cmd[j + size];
				j++;
			}
			cmd->cmd[j] = '\0';
			i += !size;
		}
		else
			i++;
	}
	cmd->arg = ft_special_split(cmd->cmd, ' ');
	if (!cmd->arg[0])
		return (-1);
	sanitize_argv(cmd->arg);
	return (0);
}

int	parse_command(char *line, t_cmd **list)
{
	int		i;
	char	**str;

	i = ft_strlen(line);
	if (i >= 1 && line[i - 1] == '\n')
		line[i - 1] = '\0';
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
	return (0);
}
