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

int	is_redirector(char c, char next)
{
	if (c == '>' && next == '>')
		return (4);
	if (c == '<' && next == '<')
		return (3);
	if (c == '>')
		return (2);
	if (c == '<')
		return (1);
	return (0);
}

int	parse_command(t_command	*command, int start, int end, char *line)
{
	int	i;
	int	j;

	i = start;
	while (line[i] && !is_redirector(line[i], line [i + 1]))
		i++;
	if (small_malloc(&command->command, sizeof(char) * ((i - start) + 1)))
		return (-1);
	ft_memcpy(command->command, &line[start], i - start);
	command->command[(i - start) - 1] = '\0';
	command->redirector = is_redirector(line[i], line[i + 1]);
	command->file = NULL;
	command->separator = is_separator(line[end], line[end + 1]);
	if (command->redirector == 0)
		return (0);
	i += 1 + (is_redirector(line[i], line [i + 1]) > 2);
	j = i;
	while (line[i] && !is_separator(line[i], line[i + 1]))
		i++;
	if (small_malloc(&command->file, sizeof(char) * ((i - j) + 1)))
		return (-1);
	ft_memcpy(command->file, &line[j], i - j);
	command->file[(i - j) - 1] = '\0';
	if (small_malloc(&command->next, sizeof(t_command) * 1))
		return (-1);
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
			parse_command(current, j, i, line);
			current->separator = is_separator(line[i], line[i + 1]);
			j = i;
			i += (is_separator(line[i], line[i + 1] > 1));
		}
		i++;
	}
	free(current->next);
	current->next = NULL;
	return (first);
}
