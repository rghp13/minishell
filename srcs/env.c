/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rponsonn <rponsonn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/15 19:01:47 by rponsonn          #+#    #+#             */
/*   Updated: 2022/02/15 19:01:49 by rponsonn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
		current->value = ft_calloc(1, sizeof(char));
	else
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

/*
**expects at least key with no $
*/

t_env	*find_env(const char *key, t_env *head)
{
	t_env	*ptr;
	char	*str;

	str = strip_value(key);
	ptr = head;
	if (str == NULL || head == NULL)
		return (NULL);
	while (ptr)
	{
		if (ft_stringcomp(str, ptr->key) == 0)
		{
			free(str);
			return (ptr);
		}
		ptr = ptr->next;
	}
	free(str);
	return (NULL);
}
/*
**takes a "KEY=VALUE" string, dups it
**removes the value so only the key remains
*/

char	*strip_value(const char *key)
{
	char	*hold;
	int		i;

	i = 0;
	if (key == NULL)
		return (NULL);
	hold = ft_strdup(key);
	if (hold == NULL)
		return (NULL);
	while (hold[i])
	{
		if (hold[i] == '=')
		{
			hold[i] = '\0';
			break ;
		}
		i++;
	}
	return (hold);
}
