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

int	argv_parse(t_cmd *list)
{
	t_cmd	*pipe;

	while (list)
	{
		if (list->pipechain)
		{
			pipe = list->pipechain;
			while (pipe)
			{
				create_argv(pipe);
				pipe = pipe->next;
			}
		}
		create_argv(list);
		list = list->next;
	}
	return (0);
}
