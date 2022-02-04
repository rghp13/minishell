#include "minishell.h"

char	*get_home_path(const char *str, t_cont *cont)
{
	char	*ptr;
	char	*hold;

	ptr = get_key_val("$HOME", cont->env);
	if (!ptr)
	{
		ft_putstr_fd("bash: HOME not set\n", STDERR_FILENO);
		return (NULL);
	}
	str++;
	hold = ft_strjoin(ptr, str);
	free(ptr);
	printf("%s\n", hold);
	return (hold);
}
