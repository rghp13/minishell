/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dscriabi <dscriabi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/19 14:37:49 by dscriabi          #+#    #+#             */
/*   Updated: 2021/09/20 11:43:07 by dscriabi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s)
{
	int		index;
	int		len;
	char	*return_value;

	index = 0;
	len = 0;
	while (s[len])
		len++;
	return_value = malloc(sizeof(char) * (len + 1));
	if (!(return_value))
		return (NULL);
	while (index < len)
	{
		return_value[index] = s[index];
		index++;
	}
	return_value[index] = '\0';
	return (return_value);
}
