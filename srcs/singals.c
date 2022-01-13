#include "../includes/minishell.h"

/*
Ctrl + c = sigint
*/

/*
Ctrl + d = EOF
/*

/*
Ctrl + \ = sigquit
*/

void	signal_handler(int signal)
{
	signal_redirector(NULL, signal, 0);
	return ;
}

int	signal_redirector(t_cont *ptr, int signal, int mode)
{
	static t_cont	*cont;

	if (mode)
		cont = ptr;
	if (signal == SIGINT && !cont->child_pid)
	{
		printf("\n");
	 	rl_on_new_line();
	 	rl_replace_line("", 0);
		rl_redisplay();
		//cont->status = 1;
	}
	else if (signal == SIGQUIT && !cont->child_pid)
	{
		rl_on_new_line();
		rl_redisplay();
		//write(1, "  \b\b", 4);
	}
	else if (signal == SIGINT || signal == SIGQUIT)
		kill(ptr->child_pid, signal);
	return (0);
}
