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
	while (ft_isalnum(var_start[j]) || var_start[j] == '_')
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

int	parse_line_variable(t_cmd *cmd, t_env *envstart)
{
	int		i;
	int		bracket;

	i = 0;
	bracket = 0;
	while (cmd->cmd[i])
	{
		if (cmd->cmd[i] == '\'')
			bracket = !bracket;
		if (cmd->cmd[i] == '$' && bracket == 0 && is_var_char(cmd->cmd[i + 1]))
		{
			if (replace_var(&cmd->cmd, &i, envstart))
				return (-1);
		}
		i++;
	}
	return (0);
}

int	substitute_variables(t_cont *cont)
{
	t_cmd	*current;
	t_cmd	*pipe;

	current = cont->cmd;
	while (current)
	{
		if (parse_line_variable(current, cont->env))
			return (-1);
		pipe = current->pipechain;
		while (pipe)
		{
			if (parse_line_variable(pipe, cont->env))
				return (-1);
			pipe = pipe->next;
		}
		current = current->next;
	}
	return (0);
}
