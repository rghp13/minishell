/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dimitriscr <dimitriscr@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/17 02:55:35 by dimitriscr        #+#    #+#             */
/*   Updated: 2022/02/17 17:21:49 by dimitriscr       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
**returns 1 if nothing is wrong
**if it fails it should return 2
*/
int	quote_check(char *cmd)
{
	int	i;
	int	quote;

	i = 0;
	quote = 0;
	if (cmd == NULL)
		return (1);
	while (cmd[i])
	{
		quote = update_bracket_status(quote, cmd[i]);
		if ((cmd[i] == ';' || cmd[i] == '\\') && quote == 0)
			return (1);
		i++;
	}
	if (quote)
		return (1);
	return (0);
}

int	pipe_check(char *cmd)
{
	int	i;
	int	pipe;
	int	quote;

	i = 0;
	pipe = 1;
	quote = 0;
	while (cmd[i])
	{
		quote = update_bracket_status(quote, cmd[i]);
		if ((cmd[i] == '|') && pipe)
			return (1);
		else if (cmd[i] == '|' && !quote)
			pipe = 1;
		else if (cmd[i] != ' ' && cmd[i] != '|')
			pipe = 0;
		i++;
	}
	return (pipe && (i != 0));
}

int	redirector_check(char *cmd)
{
	int	i;
	int	quote;
	int	redirect;

	i = 0;
	quote = 0;
	redirect = 0;
	while (cmd[i])
	{
		quote = update_bracket_status(quote, cmd[i]);
		if ((cmd[i] == '>' || cmd[i] == '<') && redirect)
			return (1);
		if ((cmd[i] == '>' || cmd[i] == '<') && !quote)
		{
			redirect = 1;
			if (cmd[i + 1] == cmd[i])
				i++;
		}
		else if (cmd[i] != ' ')
			redirect = 0;
		i++;
	}
	return (redirect);
}

int	ambiguous_redirection(char *cmd, t_env *env)
{
	int		i;
	int		j;
	int		ret;
	int		quote;

	i = 0;
	ret = 0;
	quote = 0;
	while (cmd[i] && !ret)
	{
		if ((cmd[i] == '>' || cmd[i] == '<') && !quote)
		{
			j = i + 1;
			while (cmd[j] == ' ')
				j++;
			if (cmd[j] == '$')
				ret = check_var_exist(cmd, env, j);
		}
		i++;
	}
	return (ret);
}

int	syntax_check(char *cmd, t_cont *cont)
{
	if (quote_check(cmd))
	{
		ft_putstr_fd(INVACHAR, STDERR_FILENO);
		cont->exit_status = 2;
		return (-1);
	}
	if (pipe_check(cmd))
	{
		ft_putstr_fd(EMPTYPIPE, STDERR_FILENO);
		cont->exit_status = 2;
		return (-1);
	}
	if (redirector_check(cmd))
	{
		ft_putstr_fd(EMPTYRED, STDERR_FILENO);
		cont->exit_status = 2;
		return (-1);
	}
	if (ambiguous_redirection(cmd, cont->env))
	{
		ft_putstr_fd(EMBRED, STDERR_FILENO);
		cont->exit_status = 1;
		return (-1);
	}
	return (0);
}
