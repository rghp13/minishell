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
