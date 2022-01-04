#include "minishell.h"

t_cont	*get_env(char **envp)
{
	int		i;
	t_env	*head;
	t_env	*current;

	i = 0;
	head = NULL;
	if (envp == NULL || envp[0] == NULL)
		return (ft_error(1));
	while (envp[i])
	{
		current = ft_calloc(1, sizeof(t_env));
		if (current == NULL)
			return(ft_free_envp(&current, &head));
		if (assign_env_to_struct(&current, envp[i]) == 1)
			return (ft_free_envp(&current, &head));
		add_last(&head, &current);
		i++;
	}
	return (head);
}

void	add_last(t_env *head, t_env *current)//need to test this
{
	t_env *next;

	if (head == NULL)
		*head = current;
	else
	{
		next = head;
		while (next->next != NULL)
			next = next->next;
		next->next = current;
		current->prev = next;
	}
}

int	ft_free_envp(t_env *current, t_env *head)
{
	t_env *ptr;

	if (current != NULL)
	{
		if (current->key != NULL)
			free(current->key);
		if (current->value != NULL)
			free(current->value);
		free(current);
	}
	current = NULL;
	while (head != NULL)
	{
		ptr = head->next;
		if (head->key != NULL)
			free(head->key);
		if (head->value != NULL)
			free(head->value);
		free(head);
		head = ptr;
	}
	head = NULL;
	return (1);
}

int	assign_env_to_struct(t_env *current, char *envp)
{
	char *ptr;

	ptr = ft_strchr(envp, '=');
	if (ptr == NULL)
		return (1);
	current->key = ft_calloc(((ptr - envp) + 1), sizeof(char));
	if (current->key == NULL)
		return (1);
	ft_memcpy(current->key, envp, ptr - envp);
	if (ft_strlen(ptr) < 2)
		return (1);
	current->value = ft_strdup(ptr + 1);
	if (current->value == NULL)
		return (1);
	return (0);
}