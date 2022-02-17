/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dimitriscr <dimitriscr@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/17 02:46:27 by dimitriscr        #+#    #+#             */
/*   Updated: 2022/02/17 02:46:28 by dimitriscr       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
	int		val;
	t_cmd	*current;

	current = cont->cmd;
	while (current)
	{
		val = create_argv(current);
		if (val)
		{
			cont->exit_status = 2;
			return (val);
		}
		current = current->next;
	}
	return (0);
}

int	clear_redirect(t_cmd *cmd, int mode)
{
	if (mode == 1 || mode == 0)
	{
		if (cmd->input)
			free(cmd->input);
		cmd->input = NULL;
		cmd->input_type = -1;
	}
	if (mode == 2 || mode == 0)
	{
		if (cmd->output)
			free(cmd->output);
		cmd->output = NULL;
		cmd->output_type = -1;
	}
	return (0);
}

int	is_redirect_separator(char c)
{
	if (c == ' ' || c == '>' || c == '<' || c == '\0')
		return (1);
	return (0);
}
