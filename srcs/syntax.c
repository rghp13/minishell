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
	pipe = 1;
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
	int	redirect;

	i = 0;
	redirect = 0;
	while (cmd[i])
	{
		if ((cmd[i] == '>' || cmd[i] == '<') && redirect)
			return (0);
		if (cmd[i] == '>' || cmd[i] == '<')
		{
			redirect = 1;
			if (cmd[i + 1] == cmd[i])
				i++;
		}
		else if (cmd[i] != ' ')
			redirect = 0;
		i++;
	}
	return (1);
}

int	syntax_check(char *cmd)
{
	if (quote_check(cmd) && pipe_check(cmd) && redirector_check(cmd))
		return (0);
	return (1);
}