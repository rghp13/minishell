#include "minishell.h"

char	**ret_path_split(t_env *env)
{
	char	*bin;
	char	**split;
	bin = get_key_val("$PATH", env);
	if (!bin)
		return (NULL);
	split = ft_split(bin, ':');
	free(bin);
	return (split);
}
//you are able to /bin/echo when you have no idea where you are
//
char	*find_relative_path(const char *str, t_cont *cont)
{
	char	*hold;
	char	*hold2;

	if (!str || !str[0])
		return (NULL);
	if (str[0] == '/')
	{
		if (access(str, F_OK) == 0)
			return (strdup(str));
		return (NULL);
	}
	if (cont->pwd)
	{
		hold = ft_strjoin(cont->pwd, "/");
		if (hold == NULL)
			return (NULL);
		hold2 = ft_strjoin(hold, str);
		free(hold);
		return (hold2);
	}
	ft_putstr_fd("error retrieving currentdirectory: cannot access parent directories: \
	No such file or directory\n", STDERR_FILENO);
	return (NULL);
}