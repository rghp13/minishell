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
*/

int	main(int argc, char **argv, char **envp)
{
	char	*buffer;
	char	**cmd;
	t_cont	cont;

	write(1, "$> ", 3);
	while (1)
	{
		buffer = get_next_line(1);
		if (buffer == NULL)
		{
			perror("Malloc Error\n");
			return (0);
		}
		printf("cmd = %s\n", buffer);
		cmd = ft_split(buffer, ' ');
		get_abs_path(cmd);
		exec_cmd(cmd, envp);
		free(buffer);
		write(1, "$> ", 3);
	}
	printf("BYE!\n");
	free(buffer);
}
