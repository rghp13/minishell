#include "../includes/minishell.h"

int	break_pipes(t_cmd *list)
{
	int		i;
	t_cmd	*current;
	char	**str;

	current = list;
	while (current)
	{
		if (has_pipe(current->cmd))
		{
			str = ft_split(current->cmd, '|');
			free(current->cmd);
			current->cmd = str[0];
			i = 1;
			while (str[i])
			{
				current->pipechain = add_cmd(current->pipechain, str[i]);
				i++;
			}
		}
		current = current->next;
	}
	return (0);
}

int	parse_command(char *line, t_cmd **list)
{
	int		i;
	char	**str;

	i = 0;
	str = ft_split(line, ';');
	while (str[i])
	{
		*list = add_cmd(*list, str[i]);
		i++;
	}
	break_pipes(*list);
	return (0);
}
