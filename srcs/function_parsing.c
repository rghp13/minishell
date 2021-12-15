#include "../includes/minishell.h"

void	print_command_list(t_cmd *list)
{
	while (list)
	{
		printf("---------------%p---------------\n", list);
		printf("cmd : %s\n", list->cmd);
		printf("prev : %p\n", list->prev);
		printf("next : %p\n", list->next);
		printf("pipe : %p\n", list->pipechain);
		printf("--------------------------------------\n");
		list = list->next;
	}
	return ;
}

t_cmd	*init_cmd(char *cmd)
{
	t_cmd	*newcmd;

	if (small_malloc((void *) &newcmd, sizeof(t_cmd)))
		return (NULL);
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
	while (current->next)
		current = current->next;
	current->next = newcmd;
	current->next->prev = current;
	return (list);
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
	return (0);
}
