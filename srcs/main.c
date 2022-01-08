#include "minishell.h"

/*
**readline, rl_clear_history, rl_on_new_line,
**rl_replace_line, rl_redisplay, add_history,
**printf, malloc, free, write, access, open, read,
**close, fork, wait, waitpid, wait3, wait4, signal,
**sigaction, kill, exit, getcwd, chdir, stat,
**lstat, fstat, unlink, execve, dup, dup2, pipe,
**opendir, readdir, closedir, strerror, perror,
**isatty, ttyname, ttyslot, ioctl, getenv, tcsetattr,
**tcgetattr, tgetent, tgetflag, tgetnum, tgetstr,
**tgoto, tputs
**Start by moving all envp to a linked list
*/

// int	main(int argc, char **argv, char **envp)
// {
// 	t_cont	cont;
// 	t_env	*ptr;
// 	char	*str;

// 	(void)argc;
// 	(void)argv;
// 	cont.env = get_env(envp);
// 	if (cont.env == NULL)
// 		return (printf("ERROR\n"));
// 	ptr = cont.env;
// 	while (ptr)
// 	{
// 		printf("Key = %s\nValue = %s\n\n", ptr->key, ptr->value);
// 		ptr = ptr->next;
// 	}
// 	str = get_key_val("$LS_COLORS", cont.env);
// 	printf("%s\n", str);
// 	free(str);
// 	free_envp(NULL, cont.env);
// 	return (0);
// }

// int	main(int argc, char **argv, char **envp)
// {
// 	char	*buffer;
// 	char	**cmd;
// 	t_cont	cont;

// 	write(1, "$> ", 3);
// 	while (1)
// 	{
// 		buffer = get_next_line(1);
// 		if (buffer == NULL)
// 		{
// 			perror("Malloc Error\n");
// 			return (0);
// 		}
// 		printf("cmd = %s\n", buffer);
// 		cmd = ft_split(buffer, ' ');
// 		get_abs_path(cmd);
// 		exec_cmd(cmd, envp);
// 		free(buffer);
// 		write(1, "$> ", 3);
// 	}
// 	printf("BYE!\n");
// 	free(buffer);
// }

int	main(int argc, char const *argv[], char **envp)
{
	t_cont	*cont;
	t_cont	test;

	cont = &test;
	cont->cmd = NULL;
	cont->env = get_env(envp);
	parse_command("echo $TERM | echo $LESS $SHELL | echo $PAGER$COLORTERM; echo $TEST", &cont->cmd);
	substitute_variables(cont);
	print_command_list(cont->cmd);
	free_parse(cont->cmd);
	free_envp(NULL, cont->env);
	return (0);
}
