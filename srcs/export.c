#include "minishell.h"

/*
**export returns 1 only if key has any symbol that isn't =
**even with that the program keeps going
** ! error starts from ! till end of string//not implementing
** # is taken as a comment so anything after it is ignored
** & - cause errors
** _ is accepted do not return error
*/

int	builtin_export(char **argv, t_cont *cont)
{
	int		i;
	t_env	*new_env;
	int		flag;
	char	**split;

	i = -1;
	flag = 0;
	while (argv[++i])
	{
		if (check_valid_export(argv[i], cont, &flag) == 0)
			continue ;
		printf("Valid export\n");
		new_env = ft_calloc(1, sizeof(t_env));
		if (new_env == NULL || assign_env_to_struct(new_env, argv[i]))//test this
		{
			free_envp(new_env, NULL);
			return (1);
		}
		printf("Adding last\n");
		add_last(cont->env, new_env);
	}
	split = output_env_array(cont->env);
	if (split == NULL)
		return (1);
	ft_free_all_split(cont->envstr);
	cont->envstr = split;
	printf("generating new envstr\n");
	return (flag);
}

int	check_valid_export(const char *str, t_cont *cont, int *flag)
{
	int		i;
	int		c;
	char	*ptr;
	ptr = ft_strchr(str, '=');
	if (ptr == NULL)
		return (1);
	if (ptr == str)
	{
		*flag = 1;
		return (export_error(str));
	}
	c = ptr - str;
	while (i < c)
	{
		if (ft_isasymbol(str[i]) == 1)
		{
			*flag = 1;
			return (export_error(str));
		}
		i++;
	}
	return (0);
}

int	export_error(const char *str)
{
	write(STDOUT_FILENO, "bash: export: `", 16);
	write(STDOUT_FILENO, str, ft_strlen(str));
	write(STDOUT_FILENO, "': not a valid identifier", 26);
	return (1);
}

int	ft_isasymbol(const char str)
{
	if (str == '_')
		return (0);
	if (str >= '!' && str < '0')
		return (1);
	else if (str >= ':' && str < 'A')
		return (1);
	else if (str >= '[' && str < 'a')
		return (1);
	else if (str >= '{' && str <= '~')
		return (1);
	else
		return (0);
}