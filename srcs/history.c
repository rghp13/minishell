#include "minishell.h"

int	ft_add_history(const char *str, t_cont *cont)
{
	t_history	*new;
	char		*val;

	if (!str)
		return (1);
	val = ft_strdup(str);
	new = ft_calloc(1, sizeof(t_history));
	if (!val || !new)
	{
		if (val)
			free(val);
		if (new)
			free(new);
		ft_putstr_fd("ERROR: Unable to add history\n", STDERR_FILENO);
		return (1);
	}
	new->value = val;
	if (cont->history)
	{
		new->older = cont->history;
		cont->history->newer = new;
	}
	cont->history = new;
	return (0);
}
