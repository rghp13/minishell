/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gnl.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rponsonn <rponsonn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/13 14:52:03 by rponsonn          #+#    #+#             */
/*   Updated: 2021/12/13 17:45:56 by rponsonn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <sys/types.h>
#include "libft.h"

typedef struct s_gnl
{
	char				*ptr;
	unsigned long int	buff_size;
	int					i;
	int					nl;
	int					ret;
}				t_gnl;

int	ft_strlen(const char *str)
{
	int	index;

	index = 0;
	while (str[index] != '\0')
	{
		index++;
	}
	return (index);
}

void	*ft_memcpy(void *dest, const void *src, int n)
{
	int				index;
	unsigned char	*src_char;
	unsigned char	*dest_char;

	index = 0;
	if (dest == NULL && src == NULL)
		return (NULL);
	src_char = (unsigned char *)src;
	dest_char = (unsigned char *)dest;
	while (index < n)
	{
		dest_char[index] = src_char[index];
		index++;
	}
	return (dest);
}

void	*ft_memmove(void *str1, const void *str2, int n)
{
	int					index;
	unsigned char		*str1_char;
	const unsigned char	*str2_char;

	str1_char = (unsigned char *)str1;
	str2_char = (unsigned char *)str2;
	index = 0;
	if (str1 == NULL && str2 == NULL)
		return (NULL);
	if (str2_char < str1_char)
		while (++index <= n)
			str1_char[n - index] = str2_char[n - index];
	else
		while (n-- > 0)
			*(str1_char++) = *(str2_char++);
	return (str1);
}

void	*ft_calloc(int nitems, int size)
{
	char			*return_value;
	unsigned int	total_size;
	unsigned int	index;

	total_size = nitems * size;
	return_value = malloc(total_size);
	if (!(return_value))
		return (NULL);
	index = 0;
	while (total_size != 0)
	{
		return_value[index] = 0;
		index++;
		total_size--;
	}
	return ((void *)return_value);
}

int	first_setup(t_gnl *cont)
{
	if (cont == NULL)
		return (1);
	cont->ret = 1;
	if (cont->buff_size == 0)
		cont->buff_size = 2000;
	if (cont->ptr == NULL)
		cont->ptr = malloc(sizeof(char) * cont->buff_size + 1);
	if (cont->ptr == NULL)
		return (1);
	return (0);
}

int	error_free(t_gnl *cont)
{
	if (cont == NULL)
		return (-1);
	free(cont->ptr);
	return (-1);
}

void	pull_data(t_gnl *cont, const int fd)
{
	int	ret;

	ret = read(fd, cont->ptr + cont->i, cont->buff_size - cont->i);
	cont->ptr[ret + cont->i] = '\0';
	if (ret == 0)
		cont->ret = 0;
	return ;
}

int	next_nl(t_gnl *cont)
{
	int	i;

	while ((cont->ptr[i] != '\0' && cont->ptr[i] != '\n') && i < \
	cont->buff_size)
		i++;
	if (i >= cont->buff_size)
		return (-1);
	return (i);
}

int	double_buffer(t_gnl *cont)
{
	char	*ptr;
	int		len;

	cont->buff_size *= 2;
	len = ft_strlen(cont->ptr);
	ptr = ft_calloc(cont->buff_size + 1, sizeof(char));
	if (ptr == NULL)
		return (1);
	ft_memmove(ptr, cont->ptr, len);
	return (0);
}

char	*ft_copy(t_gnl *cont)
{
	char	*ptr;

	ptr = malloc(sizeof(char) * cont->nl);
	if (ptr == NULL)
		return (NULL);
	ft_memcpy(ptr, cont->ptr, cont->nl);
	ptr[cont->nl] = '\0';
	return (ptr);
}

void	reallign_buffer(t_gnl *cont)
{
	int	len;

	len = ft_strlen(cont->ptr);
	if (cont->nl + 1 >= len)
	{
		ft_printf("ERROR, YOU SHOULD CHECK THIS OUT\n");
		return ;
	}
	ft_memmove(cont->ptr, cont->ptr + cont->nl + 1, len - (cont->nl + 1));
	return ;
}

int	get_next_line(int fd, char **line)
{
	static t_gnl	cont;

	if (first_setup(&cont) == 1)
		return (-1);
	if (fd < 0 || line == NULL || read(fd, cont.ptr, 0) < 0)
		return (error_free(&cont));
	pull_data(&cont, fd);
	cont.nl = next_nl(cont.ptr);
	while (cont.nl == -1)
	{
		if (double_buffer(&cont) == 1)
			return (error_free(&cont));
		pull_data(&cont, fd);
		cont.nl = next_line(cont.ptr);
	}
	*line = ft_copy(&cont);
	if (*line == NULL)
		return (error_free(&cont));
	reallign_buffer(&cont);
	if (cont.ret == 0)
		free(cont.ptr);
	return (cont.ret);
}
