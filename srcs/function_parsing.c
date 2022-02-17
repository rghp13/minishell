/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   function_parsing.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dimitriscr <dimitriscr@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/17 02:25:23 by dimitriscr        #+#    #+#             */
/*   Updated: 2022/02/17 19:36:28 by dimitriscr       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
	ret = 0;
	if (cmd->cmd[i] == ' ')
		return (0);
	mode = i;
	while (cmd->cmd[i] && is_redirect_separator(cmd->cmd[i]))
		i++;
	j = i;
	while (cmd->cmd[j] && !is_redirect_separator(cmd->cmd[j]))
		j++;
	if (cmd->cmd[mode] == '>')
		output_extract(cmd, i, j, mode);
	else if (cmd->cmd[mode] == '<')
		input_extract(cmd, i, j, mode);
	close(fd);
	return (j - mode);
}

int	create_argv(t_cmd *cmd)
{
	int		i;
	int		bracket;

	i = 0;
	bracket = 0;
	if (!cmd->cmd)
		return (-1);
	while (cmd->cmd[i])
	{
		bracket = update_bracket_status(bracket, cmd->cmd[i]);
		if (!bracket && is_redirect_separator(cmd->cmd[i]))
			i = save_and_remove_redirect(cmd, i);
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
