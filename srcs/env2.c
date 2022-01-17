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
		if (head->value[0] != '\0')
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
		if (temp->value[0] != '\0')
			i++;
		temp = temp->next;
	}
	return (i);
}
//make function that removes an env| won't remove but will set first byte of str to NULL
int	remove_env(t_env *head, const char *key)
{
	t_env	*find;

	find = find_env(key, head);
	if (find == NULL)
		return (1);
	find->value[0] = '\0';
	return (0);
}