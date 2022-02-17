/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dimitriscr <dimitriscr@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/17 02:25:49 by dimitriscr        #+#    #+#             */
/*   Updated: 2022/02/17 19:25:46 by dimitriscr       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	output_extract(t_cmd *cmd, int i, int j, int mode)
{
	int	fd;

	fd = -1;
	clear_redirect(cmd, 2);
	cmd->output_type = (cmd->cmd[mode] == cmd->cmd[mode + 1]);
	if (small_malloc((void **)&cmd->output, sizeof(char) * (j - i)))
		return (-1);
	ft_memcpy(cmd->output, &cmd->cmd[i], j - i);
	cmd->output[j - i] = '\0';
	fd = open(cmd->output, O_WRONLY | O_CREAT, 0664);
	if (fd == -1)
		return (-1);
	remove_brackets(cmd->output);
	return (0);
}

int	input_extract(t_cmd *cmd, int i, int j, int mode)
{
	int	fd;

	fd = -1;
	clear_redirect(cmd, 1);
	cmd->input_type = (cmd->cmd[mode] == cmd->cmd[mode + 1]);
	if (small_malloc((void **)&cmd->input, sizeof(char) * (j - i)))
		return (-1);
	ft_memcpy(cmd->input, &cmd->cmd[i], j - i);
	cmd->input[j - i] = '\0';
	if (cmd->input_type == 0)
	{
		fd = open(cmd->input, O_RDONLY, 0664);
		if (fd == -1)
			return (-1);
		remove_brackets(cmd->input);
	}
	return (0);
}

int	save_and_remove_redirect(t_cmd *cmd, int i)
{
	int	j;
	int	size;

	j = 0;
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
	return (i);
}
