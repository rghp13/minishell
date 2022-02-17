/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bracket_split.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dimitriscr <dimitriscr@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/17 02:23:11 by dimitriscr        #+#    #+#             */
/*   Updated: 2022/02/17 02:23:22 by dimitriscr       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	ft_special_word_count(char const *s, char c)
{
	int		index;
	int		count;
	int		bracket;

	count = 0;
	index = 0;
	bracket = 0;
	while (s[index])
	{
		bracket = update_bracket_status(bracket, s[index]);
		if (s[index] != c && (s[index + 1] == c || \
		s[index + 1] == '\0') && !bracket)
			count++;
		index++;
	}
	return (count);
}

static int	ft_special_word_length(char const *s, char c)
{
	int		index;
	int		length;
	int		bracket;

	index = 0;
	length = 0;
	bracket = 0;
	while ((s[index] != c || bracket) && s[index] != '\0')
	{
		bracket = update_bracket_status(bracket, s[index]);
		index++;
		length++;
	}
	return (length);
}

void	*ft_special_free_split(char **split_str, int word_count)
{
	int	index;

	index = 0;
	while (index < word_count)
	{
		free(split_str[index]);
		index++;
	}
	free(split_str);
	return (NULL);
}

static char	**ft_special_fill_str(char const *s, int wc, char c, char **s_str)
{
	int		index;
	int		sub_index;
	int		length;

	index = -1;
	while (++index < wc)
	{
		while (*s == c)
			s++;
		length = ft_special_word_length(s, c);
		s_str[index] = (char *)malloc(sizeof(char) * (length + 1));
		if (!(s_str[index]))
			return (ft_special_free_split(s_str, index));
		sub_index = 0;
		while (sub_index < length)
			s_str[index][sub_index++] = *s++;
		s_str[index][sub_index] = '\0';
	}
	s_str[index] = NULL;
	return (s_str);
}

char	**ft_special_split(char	const *s, char c)
{
	char	**split_str;
	int		word_count;

	if (!s)
		return (NULL);
	word_count = ft_special_word_count(s, c);
	split_str = (char **)malloc(sizeof(char *) * (word_count + 1));
	if (!(split_str))
		return (NULL);
	split_str = ft_special_fill_str(s, word_count, c, split_str);
	return (split_str);
}
