#include "../includes/minishell.h"

void	init_singals(void)
{
	struct sigaction	sa;

	// sa.sa_handler = &signal_handler;
	// sa.sa_flags = SA_RESTART;
	// sigaction(SIGQUIT, &sa, NULL);
	// sigaction(SIGINT, &sa, NULL);
	signal(SIGINT, signal_handler);
	signal(SIGQUIT, signal_handler);
	return ;
}

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
	}
	else if (signal == SIGQUIT && !cont->child_pid)
		return (0);
	else if (signal == SIGINT || signal == SIGQUIT)
		kill(cont->child_pid, signal);
	return (0);
}
