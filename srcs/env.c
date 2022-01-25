#include "minishell.h"

t_env	*get_env(char **envp, t_cont *cont)
{
	int		i;
	t_env	*head;
	t_env	*current;

	i = 0;
	head = NULL;
	if (envp == NULL || envp[0] == NULL)
		return (NULL);
	while (envp[i])
	{
		current = ft_calloc(1, sizeof(t_env));
		if (current == NULL || assign_env_to_struct(current, envp[i]) == 1)
		{
			free_envp(current, head);
			return (NULL);
		}
		current->cont = cont;
		if (head == NULL)
			head = current;
		else
			add_last(head, current);
		i++;
	}
	return (head);
}

int	assign_env_to_struct(t_env *current, char *envp)
{
	char	*ptr;

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

char	*get_key_val(const char *key, t_env *env)
{
	const char	*ret;
	t_env		*key_struct;

	if (key[0] != '$')
		return (ft_calloc(1, sizeof(char)));
	ret = key + 1;
	if (ft_stringcomp(key, "$?") == 0)
		return (ft_itoa(env->cont->exit_status));
	key_struct = find_env(ret, env);
	if (key_struct == NULL)
		return (ft_calloc(1, sizeof(char)));
	return (ft_strdup(key_struct->value));
}

t_env	*find_env(const char *key, t_env *head)
{
	t_env	*ptr;
	int		len;

	ptr = head;
	if (key == NULL || head == NULL)
		return (NULL);
	len = ft_strlen(key);
	while (ptr)
	{
		if (len == ft_strlen(ptr->key))
		{
			if (ft_strncmp(key, ptr->key, len) == 0)
				return (ptr);
		}
		ptr = ptr->next;
	}
	return (NULL);
}
