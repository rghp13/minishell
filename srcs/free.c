#include "minishell.h"

//void	main_free(void)
//{
//	call function to free your struct in a safe way here
//	free_env_strct() etc...
//}

/*
**if you only want to clear an unattached link in the env chain put it in current
**and leave head NULL
**if you want to clear the whole env chain put the head in head.
**
*/

void	free_envp(t_env *current, t_env *head)
{
	t_env	*ptr;

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
