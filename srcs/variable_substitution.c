#include "../includes/minishell.h"

int	substitute_variables(t_cont *cont)
{
	t_cmd *current;
	t_cmd *pipe;

	current = cont->cmd;
	while (current)
	{
		parse_line_variable(current, cont->env);
		pipe = current->pipechain;
		while (pipe)
		{
			parse_line_variable(pipe, cont->env)
			pipe = pipe->next;
		}
		current = current->next;
	}
	return (0);
}

int	parse_line_variable(t_cmd *cmd, t_env *envstart)
{
	int	i;

	i = 0;
	while (cmd->cmd[i])
	{
		if (cmd->cmd[i] == '$')
			//find the name of the environment variable
			//find it's value in the array
			//substitute
			//free old char pointers
		i++;
	}
}

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

char *substituestr(char *text, char *word, char *replacement, int start)
{
	int		i;
	int		j;
	int		k;
	int		len;
	char	*retstr;

	i = 0;
	j = 0;
	len = ft_strlen(text) + ft_strlen(replacement) - ft_strlen(word);
	if (small_malloc(&retstr, sizeof(char) * (len + 1)))
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
	return (retstr);
}