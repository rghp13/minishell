#include "minishell.h"

/*
**returns 1 if nothing is wrong
**if it fails it should return 2
*/
int	quote_check(char *cmd)
{
	int	i;
	int	quote;

	i = 0;
	quote = 0;
	if (cmd == NULL)
		return (0);
	//if (ft_isasymbol(cmd[0]) == 1)
	//	return (0);
	while (cmd[i])
	{
		quote = update_bracket_status(quote, cmd[i]);
		if ((cmd[i] == ';' || cmd[i] == '\\') && quote == 0)
			return (0);
		i++;
	}
	if (quote)
		return (0);
	return (1);
}

int	pipe_check(char *cmd)
{
	int	i;
	int	pipe;

	i = 0;
	pipe = 0;
	while (cmd[i])
	{
		if (cmd[i] == '|' && pipe)
			return (0);
		else if (cmd[i] == '|')
			pipe = 1;
		else if (cmd[i] != ' ' && cmd[i] != '|')
			pipe = 0;
		i++;
	}
	return (1);
}

int	redirector_check(char *cmd)
{
	int	i;
	int	left_red;
	int	right_red;

	i = 0;
	left_red = 0;
	right_red =	0;
	while (cmd[i])
	{
		if (cmd[i] == '|')
		{
			left_red = 0;
			right_red = 0;
		}
		else if (cmd[i] == '>')
		{
			right_red += 1;
			if (cmd[i + 1] == '>')
				i++;
		}
		else if (cmd[i] == '<')
		{
			left_red += 1;
			if (cmd[i + 1] == '<')
				i++;
		}
		if (left_red > 1 || right_red > 1)
			return (0);
		i++;
	}
	return (1);
}

int	syntax_check(char *cmd)
{
	if (quote_check(cmd) && pipe_check(cmd) && redirector_check(cmd))
		return (1);
	return (0);
}