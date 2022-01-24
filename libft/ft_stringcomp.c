/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_stringcomp.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romain <romain@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/24 16:33:31 by romain            #+#    #+#             */
/*   Updated: 2022/01/24 16:44:30 by romain           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
**returns 0 if identical
*/

int	ft_stringcomp(const char *str1, const char *str2)
{
	if (!str1 && !str2)
		return (0);
	if (str1 || str2)
	if (ft_strlen(str1) != ft_strlen(str2))
		return (-1);
	return (ft_strncmp(str1, str2, ft_strlen(str1)));
}