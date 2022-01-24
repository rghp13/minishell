#include "../includes/minishell.h"

void	init_singals(void)
{
	struct sigaction	sa;
	struct sigaction	sb;

	sa.sa_handler = &signal_handler;
	sa.sa_flags = ~SA_RESTART;
	sb.sa_handler = &signal_handler;
	sb.sa_flags = 0;
	sigaction(SIGQUIT, &sa, NULL);
	sigaction(SIGINT, &sa, NULL);
	return ;
}

void	signal_handler(int signal)
{
	if (signal == SIGQUIT)
		return ;
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
		ft_putstr_fd("\n", 2);
		ft_putstr_fd("$> ", 2);
	}
	else if (signal == SIGQUIT && !cont->child_pid)
		return (0);
	else if (signal == SIGINT || signal == SIGQUIT)
		kill(ptr->child_pid, signal);
	return (0);
}
