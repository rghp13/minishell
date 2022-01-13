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
		/*sigint function w/o PID*/
	else if (signal == SIGQUIT && !cont->child_pid)
		/*sigquit function w/o PID*/
	else if (signal == SIGINT)
		/*sigint function for child PID*/
	else if (signal == SIGQUIT)
		/*sigquit function for child PID*/
	return (0);
}
