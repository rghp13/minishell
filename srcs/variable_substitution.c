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

char	*get_var_name(char *var_start)
{
	int		i;
	int		j;
	char	*retstr;

	i = 0;
	j = 1;
	if (!var_start)
		return (NULL);
	if (var_start[0] == '$' && var_start[1] == '$')
		return (var_special_case(1));
	if (var_start[0] == '$' && var_start[1] == '?')
		return (var_special_case(2));
	while (var_start[0] == '$' && (ft_isalnum(var_start[j]) \
	|| var_start[j] == '_'))
		j++;
	while (var_start[0] == '~' && var_start[j] != '/' \
	&& var_start[j] != ' ' && var_start[j] != '\0')
		j++;
	if (small_malloc((void **)&retstr, sizeof(char) * ((j - i) + 1)))
		return (NULL);
	while (i < j)
	{
		retstr[i] = var_start[i];
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
