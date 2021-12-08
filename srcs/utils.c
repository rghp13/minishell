#include "../includes/minishell.h"

int	small_malloc(void **ptr, size_t size)
{
	*ptr = malloc(size);
	if (!ptr)
		return (-1);
	return (0);
}
