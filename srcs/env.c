#include "minishell.h"

t_cont	*get_env(char **envp)
{
	int		i;
	t_env	*head;
	t_env	*current;
	char	**split;

	i = 0;
	head = NULL;
	while (envp[i])
	{
		current = malloc(sizeof(t_env));
		split = ft_split(envp[i], '=');
		if (split == NULL)
			perror("Malloc Error");
		current->key = split[0];
		current->value = split[1];
		split_free(split);
		add_last(head, current);
	}
}

void	split_free(char **str)
{
	int i;

	i = 0;
	while (str[i])
	{
		free(str[i++]);
	}
	free(str);
	return ;
}