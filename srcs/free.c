/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rponsonn <rponsonn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/15 19:10:29 by rponsonn          #+#    #+#             */
/*   Updated: 2022/02/17 14:19:38 by rponsonn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
}

int	free_cmd(t_cmd *cmd)
{
	free(cmd->cmd);
	if (cmd->arg)
		ft_free_all_split(cmd->arg);
	if (cmd->abspath)
		free(cmd->abspath);
	if (cmd->input)
		free(cmd->input);
	if (cmd->output)
		free(cmd->output);
	free(cmd);
	return (0);
}
