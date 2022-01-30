#include "minishell.h"

//make function that outputs an array of string
char	**output_env_array(t_env *head)
{
	char	**split;
	int		i;
	int		k;

	i = calculate_env_split(head);
	k = 0;
	split = malloc(sizeof(char *) * i + 1);
	if (split == NULL)
		return (NULL);
	split[i] = NULL;
	while (head)
	{
		if (head->value && head->value[0] != '\0')
		{
			split[k] = env_str(head);
			if (split[k++] == NULL)
			{
				ft_free_all_split(split);
				return (NULL);
			}
		}
		head = head->next;
	}
	return (split);
}

/*
**pass it a link in the chain and it will return
**key=value as a string
*/

char	*env_str(t_env *env)
{
	char	*key;
	char	*value;

	key = ft_strjoin(env->key, "=");
	if (key == NULL)
		return (NULL);
	value = ft_strjoin(key, env->value);
	free(key);
	if (value == NULL)
		return (NULL);
	return (value);
}

int	calculate_env_split(t_env *head)
{
	int		i;
	t_env	*temp;

	i = 0;
	temp = head;
	while (temp)
	{
		if (temp->value)
			i++;
		temp = temp->next;
	}
	return (i);
}

/*
**IF YOU USE THIS FUNCTION BE SURE TO UPDATE THE ENVSTR
*/
int	remove_env(t_env *head, const char *key)
{
	t_env	*find;
	t_env	*prev;
	t_env	*next;

	find = find_env(key, head);
	if (find == NULL)
		return (1);
	prev = find->prev;
	next = find->next;
	if (find->value)
		free(find->value);
	if (find->key)
		free(find->key);
	if (next)
		next->prev = prev;
	if (prev)
		prev->next = next;
	else
		find->cont->env = next;
	free(find);
	return (0);
}

/*
**IF YOU USE THIS FUNCTION PLEASE UPDATE THE ENVSTR WHEN DONE
*/

t_env	*add_env(const char *key, const char *value, t_cont *cont)
{
	t_env	*new;

	if (!key || !value)
	{
		ft_putstr_fd("Unable to add new variable\n", STDERR_FILENO);
		return (NULL);
	}
	new = ft_calloc(1, sizeof(t_env));
	if (!new)
	{
		ft_putstr_fd("Malloc Error\n", STDERR_FILENO);
		return (NULL);
	}
	new->key = ft_strdup(key);
	new->value = ft_strdup(value);
	new->cont = cont;
	if (!new->key || !new->value)
	{
		free_envp(new, NULL);
		return (NULL);
	}
	return (new);
}
