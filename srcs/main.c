#include "../includes/minishell.h"

/*
**ERRORS NEED TO GO TO STDERR, TRACK SHELL LVL, IMPLEMENT HISTORY, 
**'' not disappearing in echo, -n flag being printed
**bash should say "home not set"
**$SHELL might need to say minishell
**shell should error out if no environment
**typing a command then pressing CTRL+D twice executes it (shouldn't happen)
**implement ~/ execution
**test what happens with ~/ if it's after a pipe
**"hi.txt" ctrl+d
*/

int	initialize_main_struct(t_cont *cont, char **envp, struct termios *original)
{
	struct termios	t;

	ft_bzero(cont, sizeof(t_cont));
	tcgetattr(0, original);
	t = *original;
	t.c_lflag &= (ICANON | ECHO | ~ECHOCTL);
	t.c_cc[VQUIT] = 0;
	tcsetattr(0, TCSANOW, &t);
	signal_redirector(cont, 0, 1);
	init_singals();
	fd_inits(cont);
	errno = 0;
	cont->pwd = getcwd(NULL, 0);
	if (errno)
		perror("init: pwd");
	cont->env = get_env(envp, cont);
	shell_lvl(cont);
	cont->envstr = output_env_array(cont->env);
	return (0);
}

int	cleanup(t_cont cont, struct termios original)
{
	free_envp(NULL, cont.env);
	ft_free_all_split(cont.envstr);
	fd_close(&cont);
	tcsetattr(0, TCSANOW, &original);
	if (cont.pwd)
		free(cont.pwd);
	return (0);
}

int	main_loop(t_cont *cont)
{
	char	*parsed_line;

	while (cont->exit_flag == 0)
	{
		// ft_putstr_fd("$> ", 2);
		// parsed_line = get_next_line(0);
		parsed_line = readline("$> ");
		if (!parsed_line)
		{
			rl_clear_history();
			ft_putstr_fd("exit\n", STDERR_FILENO);
			break ;
		}
		add_history(parsed_line);
		if (syntax_check(parsed_line))
		{
			parse_command(parsed_line, &cont->cmd);
			substitute_variables(cont);
			if (!argv_loop(cont))
				exec_main(cont);
		}
		else
			ft_putstr_fd("Parsing Error\n", 3);
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
	return (cont.exit_status);
}
