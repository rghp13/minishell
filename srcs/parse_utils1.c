# include "../includes/minishell.h"

int	has_pipe(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '|')
			return (1);
		i++;
	}
	return (0);
}

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
		print_command_list(list->pipechain);
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

int	free_parse(t_cmd *list)
{
	t_cmd	*next;
	t_cmd	*pipe;
	t_cmd	*temp;	

	while (list)
	{
		next = list->next;
		if (list->pipechain)
		{
			pipe = list->pipechain;
			while (pipe)
			{
				temp = pipe->next;
				free(pipe->cmd);
				free(pipe);
				pipe = temp;
			}
		}
		free(list->cmd);
		free(list);
		list = next;
	}
	return (0);
}
