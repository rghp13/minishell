#include "../includes/minishell.h"

int	small_malloc(void **ptr, size_t size)
{
	*ptr = malloc(size);
	if (!ptr)
		return (-1);
	return (0);
}

int	ft_error(int erno)
{
	if (erno == 1)
		write(STDERR_FILENO, ER1, ft_strlen(ER1));
	return (1);
}