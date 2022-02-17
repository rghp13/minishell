/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dimitriscr <dimitriscr@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/17 02:47:15 by dimitriscr        #+#    #+#             */
/*   Updated: 2022/02/17 19:28:39 by dimitriscr       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*add_slash_n(char *str)
{
	char	*temp;

	temp = ft_strjoin(str, "\n");
	free(str);
	return (temp);
}

int	get_mode(char *word)
{
	int	i;

	i = 0;
	while (word[i])
	{
		if (word[i] == '\'' || word[i] == '"')
			return (0);
		i++;
	}
	return (1);
}

char	*di_variable(char *str, t_cont *cont, int mode)
{
	int		i;

	i = 0;
	if (!mode)
		return (str);
	while (str[i])
	{
		if (str[i] == '$')
			replace_var(&str, &i, cont);
		i++;
	}
	return (str);
}

int	double_input(t_cmd *cmd, t_cont *cont)
{
	char	*ret_str;
	char	*final;
	char	*temp;
	int		mode;
	int		pipes[2];

	final = calloc(1, sizeof(char));
	mode = get_mode(cmd->input);
	remove_brackets(cmd->input);
	while (1)
	{
		ret_str = readline("> ");
		ret_str = di_variable(ret_str, cont, mode);
		if (!ft_stringcomp(ret_str, cmd->input))
			break ;
		ret_str = add_slash_n(ret_str);
		temp = ft_strjoin(final, ret_str);
		free(final);
		final = temp;
	}
	pipe(pipes);
	write(pipes[1], final, ft_strlen(final));
	close(pipes[1]);
	free(final);
	return (pipes[0]);
}

int	prepare_redirection(t_cmd *cmd, t_cont *cont)
{
	if (cmd->input_type > -1)
	{
		if (cmd->input_type == 0)
			cont->fd_in = open(cmd->input, O_RDONLY, 0664);
		else if (cmd->input_type == 1)
			cont->fd_in = double_input(cmd, cont);
		if (cont->fd_in == -1)
			return (-1);
		dup2(cont->fd_in, 0);
		close(cont->fd_in);
	}
	if (cmd->output_type > -1)
	{
		if (cmd->output_type == 0)
			cont->fd_out = open(cmd->output, O_WRONLY | \
			O_TRUNC | O_CREAT, 0664);
		else if (cmd->output_type == 1)
			cont->fd_out = open(cmd->output, O_WRONLY | \
			O_APPEND | O_CREAT, 0664);
		if (cont->fd_out == -1)
			return (-2);
		dup2(cont->fd_out, 1);
		close(cont->fd_out);
	}
	return (0);
}
