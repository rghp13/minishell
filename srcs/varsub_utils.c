/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   varsub_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dimitriscr <dimitriscr@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/17 02:57:07 by dimitriscr        #+#    #+#             */
/*   Updated: 2022/02/17 02:57:08 by dimitriscr       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	is_word_to_replace(char *currentletter, char *word)
{
	int	i;

	i = 0;
	while (currentletter[i])
	{
		if (!word[i] && ((!ft_isalnum(currentletter[i]) && \
		currentletter[i] != '_') || currentletter[i] == '\0'))
			return (1);
		if (currentletter[i] != word[i])
			return (0);
		i++;
	}
	return (currentletter[i] == word[i]);
}

int	is_var_char(char c)
{
	if (ft_isalnum(c) || c == '$' || c == '?' || c == '_')
		return (1);
	return (0);
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

int	replace_var(char **cmd, int *i, t_cont *cont)
{
	char	*var_name;
	char	*var_val;

	var_name = get_var_name(&cmd[0][*i]);
	if (!var_name)
		return (-1);
	if (cmd[0][*i] == '$')
		var_val = get_key_val(var_name, cont->env);
	else
		var_val = expand_tilde(var_name, cont);
	if (!var_val)
	{
		free (var_name);
		return (-1);
	}
	*cmd = substituestr(*cmd, var_name, var_val, *i);
	i += ft_strlen(var_val) - 1;
	free(var_name);
	free(var_val);
	if (!*cmd)
		return (-1);
	return (0);
}
