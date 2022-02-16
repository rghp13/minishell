#include "../includes/minishell.h"

int	break_pipes(t_cmd *list)
{
	int		i;
	char	**str;

	if (has_pipe(list->cmd))
	{
		str = ft_special_split(list->cmd, '|');
		free(list->cmd);
		list->cmd = str[0];
		i = 1;
		while (str[i])
		{
			list->next = add_cmd(list->next, str[i]);
			i++;
		}
		free(str);
	}
	return (0);
}

int	extract_redirector(t_cmd *cmd, int i)
{
	int	j;
	int	fd;
	int	mode;

	fd = -1;
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
		clear_redirect(cmd, 2);
		cmd->output_type = (cmd->cmd[mode] == cmd->cmd[mode + 1]);
		if (small_malloc((void **)&cmd->output, sizeof(char) * (j - i)))
			return (-1);
		ft_memcpy(cmd->output, &cmd->cmd[i], j - i);
		cmd->output[j - i] = '\0';
		fd = open(cmd->output, O_WRONLY | O_CREAT, 0664);
		if (fd == -1)
			return (-1);
	}
	else if (cmd->cmd[mode] == '<')
	{
		clear_redirect(cmd, 1);
		cmd->input_type = (cmd->cmd[mode] == cmd->cmd[mode + 1]);
		if (small_malloc((void **)&cmd->input, sizeof(char) * (j - i)))
			return (-1);
		ft_memcpy(cmd->input, &cmd->cmd[i], j - i);
		cmd->input[j - i] = '\0';
		fd = open(cmd->input, O_RDONLY, 0664);
		if (fd == -1)
			return (-1);
	}
	close(fd);
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
				return (-2);
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

	i = ft_strlen(line);
	if (i >= 1 && line[i - 1] == '\n')
		line[i - 1] = '\0';
	*list = add_cmd(*list, line);
	break_pipes(*list);
	return (0);
}
