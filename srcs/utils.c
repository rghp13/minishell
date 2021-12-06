/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dscriabi <dscriabi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/06 18:48:34 by dscriabi          #+#    #+#             */
/*   Updated: 2021/12/06 18:50:37 by dscriabi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	small_malloc(void **ptr, size_t size)
{
	*ptr = malloc(size);
	if (!ptr)
		return (-1);
	return (0);
}
