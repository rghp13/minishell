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
**ERRORS NEED TO GO TO STDERR, TRACK SHELL LVL, IMPLEMENT HISTORY, 
**check that a env value string set to null doesn't break anything
**typing a command then pressing CTRL+D twice executes it (shouldn't happen)
*/

int	initialize_main_struct(t_cont *cont, char **envp, struct termios *original)
{
	struct termios	t;

	tcgetattr(0, original);
	t = *original;
	t.c_lflag &= (ICANON | ~ECHOCTL); // | NOFLSH | ~ECHOK
	t.c_cc[VQUIT] = 0;
	tcsetattr(0, TCSANOW, &t);
	signal_redirector(cont, 0, 1);
	init_singals();
	fd_inits(cont);
	cont->exit_status = 0;
	cont->child_pid = 0;
	cont->cmd = NULL;
	cont->env = get_env(envp, cont);
	cont->envstr = output_env_array(cont->env);
	return (0);
}

int	cleanup(t_cont cont, struct termios original)
{
	free_envp(NULL, cont.env);
	fd_close(&cont);
	tcsetattr(0, TCSANOW, &original);
	return (0);
}

int	main_loop(t_cont *cont)
{
	char	*parsed_line;

	while (1)
	{
		ft_putstr_fd("$> ", 2);
		parsed_line = get_next_line(0);
		if (!parsed_line)
			break ;
		parse_command(parsed_line, &cont->cmd);
		substitute_variables(cont);
		argv_loop(cont);
		//print_command_list(cont->cmd); // you should replace this with your execution :)
		exec_main(cont);
		free_parse(cont->cmd);
		cont->cmd = NULL;
	}
	return (0);
}

int	main(int argc, char const *argv[], char **envp)
{
	struct termios	original;
	t_cont			cont;

	initialize_main_struct(&cont, envp, &original);
	main_loop(&cont);
	cleanup(cont, original);
	return (0);
}
