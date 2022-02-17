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

	i = 0;
	pipe = 1;
	while (cmd[i])
	{
		if ((cmd[i] == '|') && pipe)
			return (1);
		else if (cmd[i] == '|')
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
	int	redirect;

	i = 0;
	redirect = 0;
	while (cmd[i])
	{
		if ((cmd[i] == '>' || cmd[i] == '<') && redirect)
			return (1);
		if (cmd[i] == '>' || cmd[i] == '<')
		{
			redirect = 1;
			if (cmd[i + 1] == cmd[i])
				i++;
		}
		else if (cmd[i] != ' ')
			redirect = 0;
		i++;
	}
	return (0);
}

int	ambiguous_redirection(char *cmd, t_env *env)
{
	int		i;
	int		j;
	int		ret;
	char	*key;
	char	*val;

	i = 0;
	ret = 0;
	while (cmd[i] && !ret)
	{
		if (cmd[i] == '>' || cmd[i] == '<')
		{
			j = i + 1;
			while (cmd[j] == ' ')
				j++;
			if (cmd[j] == '$')
			{
				key = get_var_name(&cmd[j]);
				val = get_key_val(key, env);
				if (!ft_strlen(val))
					ret = 1;
				free(key);
				free(val);
			}
		}
		i++;
	}
	return (ret);
}

int	syntax_check(char *cmd, t_cont *cont)
{
	if (quote_check(cmd))
	{
		ft_putstr_fd("Syntax Error: Unclosed Quote or Invalid Character\n", STDERR_FILENO);
		cont->exit_status = 2;
		return (-1);
	}
	if (pipe_check(cmd))
	{
		ft_putstr_fd("Syntax Error: Empty Pipe\n", STDERR_FILENO);
		cont->exit_status = 2;
		return (-1);
	}
	if (redirector_check(cmd))
	{
		ft_putstr_fd("Syntax Error: Empty Redirector\n", STDERR_FILENO);
		cont->exit_status = 2;
		return (-1);
	}
	if (ambiguous_redirection(cmd, cont->env))
	{
		ft_putstr_fd("Syntax Error: Ambiguous Redirector\n", STDERR_FILENO);
		cont->exit_status = 2;
		return (-1);
	}
	return (0);
}