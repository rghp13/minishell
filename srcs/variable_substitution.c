/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   variable_substitution.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dimitriscr <dimitriscr@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/17 02:56:04 by dimitriscr        #+#    #+#             */
/*   Updated: 2022/02/17 02:56:56 by dimitriscr       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*var_special_case(int num)
{
	char	*retstr;

	if (small_malloc((void **)&retstr, sizeof(char) * 3))
		return (NULL);
	if (num == 1)
	{
		retstr[0] = '$';
		retstr[1] = '$';
	}
	if (num == 2)
	{
		retstr[0] = '$';
		retstr[1] = '?';
	}
	retstr[2] = '\0';
	return (retstr);
}

char	*get_var_name(char *v_s)
{
	int		i;
	int		j;
	char	*retstr;

	i = 0;
	j = 1;
	if (!v_s)
		return (NULL);
	if (v_s[0] == '$' && v_s[1] == '$')
		return (var_special_case(1));
	if (v_s[0] == '$' && v_s[1] == '?')
		return (var_special_case(2));
	while (v_s[0] == '$' && (ft_isalnum(v_s[j]) || v_s[j] == '_'))
		j++;
	while (v_s[0] == '~' && v_s[j] != '/' && v_s[j] != ' ' && v_s[j] != '\0')
		j++;
	if (small_malloc((void **)&retstr, sizeof(char) * ((j - i) + 1)))
		return (NULL);
	while (i < j)
	{
		retstr[i] = v_s[i];
		i++;
	}
	retstr[i] = '\0';
	return (retstr);
}

int	parse_line_variable(t_cmd *cmd, t_cont *cont)
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
		if (cmd->cmd[i] == '$' && bracket != 1 && is_var_char(cmd->cmd[i + 1]))
		{
			if (replace_var(&cmd->cmd, &i, cont))
				return (-1);
		}
		if (cmd->cmd[i] == '~' && !bracket)
		{
			if (replace_var(&cmd->cmd, &i, cont))
				return (-1);
		}
		i++;
	}
	return (0);
}

int	substitute_variables(t_cont *cont)
{
	t_cmd	*current;

	current = cont->cmd;
	while (current)
	{
		if (parse_line_variable(current, cont))
		{
			cont->exit_status = 2;
			return (-1);
		}
		current = current->next;
	}
	return (0);
}
