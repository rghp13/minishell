#include "../includes/minishell.h"

void	remove_brackets(char *arg)
{
	int	i;
	int	j;
	int	bracket;

	i = 0;
	bracket = 0;
	while (arg[i])
	{
		if (bracket != update_bracket_status(bracket, arg[i]))
		{
			j = i;
			while (arg[j + 1])
			{
				arg[j] = arg[j + 1];
				j++;
			}
			arg[j] = '\0';
			bracket = update_bracket_status(bracket, arg[i]);
		}
		else
		{
			bracket = update_bracket_status(bracket, arg[i]);
			i++;
		}
	}
}

int	sanitize_argv(char **argv)
{
	int	i;

	i = 0;
	while (argv[i])
	{
		remove_brackets(argv[i]);
		i++;
	}
	return (0);
}
