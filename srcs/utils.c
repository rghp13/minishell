#include "../includes/minishell.h"

int	small_malloc(void **ptr, size_t size)
{
	*ptr = malloc(size);
	if (!ptr)
		return (-1);
	return (0);
}

int	ft_error(int erno)
{
	if (erno == 1)
		write(STDERR_FILENO, ER1, ft_strlen(ER1));
	return (1);
}

int	ft_free_all_split(char **split)
{
	int	i;

	i = 0;
	if (split == NULL)
		return (0);
	while (split[i])
	{
		free(split[i]);
		i++;
	}
	free(split);
	return (0);
}
/*
**doesn't add last if head empty (no thoughts)
*/

void	add_last(t_env *head, t_env *current)
{
	t_env	*next;

	if (head == NULL || current == NULL)
		return ;
	else
	{
		next = head;
		while (next->next != NULL)
			next = next->next;
		next->next = current;
		current->prev = next;
	}
	printf("addlast complete\n");
}
