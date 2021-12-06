/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dscriabi <dscriabi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/10 17:12:07 by rponsonn          #+#    #+#             */
/*   Updated: 2021/12/06 16:19:02 by dscriabi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	main(void)
{
	char	*buffer;

	write(1, "$> ", 3);
	while (1)
	{
		buffer = get_next_line(1);
		if (buffer == NULL)
		{
			perror("Malloc Error\n");
			return (0);
		}
		printf("cmd = %s\n", buffer);
		free(buffer);
		write(1, "$> ", 3);
	}
	printf("BYE!\n");
	free(buffer);
}
