/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sanitize_argv.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dimitriscr <dimitriscr@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/17 02:47:44 by dimitriscr        #+#    #+#             */
/*   Updated: 2022/02/17 16:58:11 by dimitriscr       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	remove_brackets(char *arg)
{
	int	i;
	int	j;
	int	bracket;

	i = 0;
	bracket = 0;
	while (arg[i])
	{
		if (bracket != update_bracket_status(bracket, arg[i]) || arg[i] == '\b')
		{
			bracket = update_bracket_status(bracket, arg[i]);
			j = i;
			while (arg[j + 1])
			{
				arg[j] = arg[j + 1];
				j++;
			}
			arg[j] = '\0';
		}
		else
		{
			bracket = update_bracket_status(bracket, arg[i]);
			i++;
		}
	}
}

int	sanitize_argv(char **argv)
{
	int	i;

	i = 0;
	while (argv[i])
	{
		remove_brackets(argv[i]);
		i++;
	}
	return (0);
}
