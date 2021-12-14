#include "../includes/minishell.h"

t_cmd	*init_cmd(char *cmd)
{
	t_cmd	*newcmd;

	if (small_malloc(&newcmd, sizeof(t_cmd)))
		return(NULL);
	newcmd->next = NULL;
	newcmd->prev = NULL;
	newcmd->pipechain = NULL;
	newcmd->cmd = cmd;
	return (newcmd);
}

t_cmd	*add_cmd(t_cmd *list, char *cmd)
{
	t_cmd	*current;
	t_cmd	*newcmd;

	current = list;
	newcmd = init_cmd(cmd);
	if (list == NULL)
		return (newcmd);
	while (!current->next)
		current = current->next;
	current->next = newcmd;
	return (list);
}

int	parse_command(char *line, t_cmd *list)
{
	int		i;
	char	**str;

	i = 0;
	str = ft_split(line, ';');
	while (str[++i])
		list = add_cell(list, str[i]);
	return (0);
}