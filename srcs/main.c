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

// int	main(void)
// {
// 	t_cmd	*list;

// 	list = NULL;
// 	parse_command("echo test; echo test 2; echo last test", &list);
// 	print_command_list(list);
// 	return (0);
// }

int	main(int argc, char **argv, char **envp)
{
	int		error;
	t_cont	cont;
	char	*ptr;
	//cont.env = ft_setup_env(envp);
	//if (cont.env == NULL)
	//	return (ft_error(1, NULL));
	//return (mini_shell(cont));
	ptr = readline("Hello> ");
	printf("%s\n", ptr);

	return (0);
}
