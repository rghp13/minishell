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
**now does but a pointer to cont must be in current
*/

void	add_last(t_env *head, t_env *current)
{
	t_env	*next;

	if (current == NULL)
		return ;
	else if (head == NULL)
	{
		if (current->cont->env == NULL)
			current->cont->env = current;
		else
			return ;
	}
	else
	{
		next = head;
		while (next->next != NULL)
			next = next->next;
		next->next = current;
		current->prev = next;
	}
}

int	update_envstr(t_cont *cont)
{
	char	**arr;

	arr = output_env_array(cont->env);
	if (arr)
	{
		ft_free_all_split(cont->envstr);
		cont->envstr = arr;
		return (0);
	}
	return (1);
}
