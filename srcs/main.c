#include "../includes/minishell.h"

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

// int    main(int argc, char const *argv[], char **envp)
// {
//     t_cont	*cont;
//     t_cont	test;
// 	char	*ptr;

//     cont = &test;
//     cont->cmd = NULL;
//     cont->env = get_env(envp);
//     parse_command("echo $TERM | echo $LESS $SHELL | echo $PAGER$COLORTERM; echo $TEST", &cont->cmd);
//     substitute_variables(cont);
//     /* run your code here */
//     free_parse(cont->cmd);
//     free_envp(NULL, cont->env);
//     return (0);
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

int	initialize_main_struct(t_cont *cont, char **envp, struct termios original)
{
	struct termios	t;

	tcgetattr(0, &original);
	t = original;
	t.c_lflag &= ~(ICANON | 512);
	tcsetattr(0, TCSANOW, &t);
	signal_redirector(cont, 0, 1);
	signal(SIGINT, &signal_handler);
	signal(SIGQUIT, &signal_handler);
	cont->child_pid = 0;
	cont->status = 0;
	cont->cmd = NULL;
	cont->env = get_env(envp);
	return (0);
}

int	cleanup(t_cont cont, struct termios original)
{
	free_envp(NULL, cont.env);
	tcsetattr(0, TCSANOW, &original);
	return (0);
}

int	main_loop(t_cont *cont)
{
	char	*parsed_line;

	while (1)
	{
		parsed_line = readline("$> ");
		if (!parsed_line)
			break ;
		parse_command(parsed_line, &cont->cmd);
		substitute_variables(cont);
		argv_loop(cont);
		print_command_list(cont->cmd); // you should replace this with your execution :)
		free_parse(cont->cmd);
		cont->cmd = NULL;
	}
	return (0);
}

int	main(int argc, char const *argv[], char **envp)
{
	struct termios	original;
	t_cont			cont;

	initialize_main_struct(&cont, envp, original);
	main_loop(&cont);
	cleanup(cont, original);
	return (0);
}
