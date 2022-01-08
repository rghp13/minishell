#include "../includes/minishell.h"

int	is_word_to_replace(char *currentletter, char *word)
{
	int	i;

	i = 0;
	while (currentletter[i])
	{
		if (!word[i] && (currentletter[i] == ' ' || \
		currentletter[i] == '$' || currentletter[i] == '\0'))
			return (1);
		if (currentletter[i] != word[i])
			return (0);
		i++;
	}
	return (currentletter[i] == word[i]);
}

char	*substituestr(char *text, char *word, char *replacement, int start)
{
	int		i;
	int		j;
	int		k;
	int		len;
	char	*retstr;

	i = 0;
	j = 0;
	len = ft_strlen(text) + ft_strlen(replacement) - ft_strlen(word);
	if (small_malloc((void **)&retstr, sizeof(char) * (len + 1)))
		return (NULL);
	while (i < start || !is_word_to_replace(&text[i], word))
	{
		retstr[i] = text[i];
		i++;
	}
	k = i + ft_strlen(word);
	while (replacement[j])
		retstr[i++] = replacement[j++];
	while (text[k])
		retstr[i++] = text[k++];
	retstr[i] = '\0';
	free(text);
	return (retstr);
}

char	*get_var_name(char *var_start)
{
	int		i;
	int		j;
	char	*retstr;

	i = 0;
	j = 1;
	while (var_start[j] != '$' && var_start[j] != ' ' && var_start)
		j++;
	if (small_malloc((void **)&retstr, sizeof(char) * ((j - i) + 1)))
		return (NULL);
	while (i < j)
	{
		retstr[i] = var_start[i];
		i++;
	}
	retstr[i] = '\0';
	return (retstr);
}

int	parse_line_variable(t_cmd *cmd, t_env *envstart)
{
	int		i;
	int		bracket;
	char	*var_name;
	char	*var_val;

	i = 0;
	bracket = 0;
	while (cmd->cmd[i])
	{
		if (cmd->cmd[i] == '\'')
			bracket = !bracket;
		if (cmd->cmd[i] == '$' && bracket == 0)
		{
			var_name = get_var_name(&cmd->cmd[i]);
			var_val = get_key_val(var_name, envstart);
			cmd->cmd = substituestr(cmd->cmd, var_name, var_val, i);
			free(var_name);
			free(var_val);
		}
		i++;
	}
	return (0);
}

int	substitute_variables(t_cont *cont)
{
	t_cmd	*current;
	t_cmd	*pipe;

	current = cont->cmd;
	while (current)
	{
		parse_line_variable(current, cont->env);
		pipe = current->pipechain;
		while (pipe)
		{
			parse_line_variable(pipe, cont->env);
			pipe = pipe->next;
		}
		current = current->next;
	}
	return (0);
}
