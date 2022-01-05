#include "../includes/minishell.h"

int	substitute_variables(t_cont *cont)
{
	return (0);
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

char *substituestr(char *text, char *word, char *replacement)
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
	while (!is_word_to_replace(&text[i], word))
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