#include "minishell.h"

/*
**returns 1 if nothing is wrong
*/
int	syntax_check(char *cmd)
{
	int	i;
	int	quote;

	i = 0;
	quote = 0;
	if (cmd == NULL)
		return (0);
	if (ft_isasymbol(cmd[0]) == 1)
		return (0);
	while (cmd[i])
	{
		quote = update_bracket_status(quote, cmd[i]);
		if (cmd[i] == ';' || cmd[i] == '\\')
			return (0);
		i++;
	}
	if (quote)
		return (0);
	return (1);
}
