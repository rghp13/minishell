#include "../includes/minishell.h"

int	is_separator(char c, char cnext)
{
	if (c == '&' && cnext == '&')
		return (3);
	if (c == '|' && cnext == '|')
		return (2);
	if (c == '|')
		return (1);
	return (0);
}

t_command	*function_parse(char *line)
{
	int			i;
	int			j;
	t_command	*first;
	t_command	*current;

	if (!line || line[0] == '\0')
		return (NULL);
	i = 0;
	j = 0;
	if (small_malloc(&first, sizeof(t_command) * 1))
		return (NULL);
	current = first;
	while (line[i])
	{
		if (is_separator(line[i], line[i + 1]))
		{
			/*do the thing*/
			j = i;
			i += (is_separator(line[i], line[i + 1] > 1));
		}
		i++;
	}
	return (first);
}
