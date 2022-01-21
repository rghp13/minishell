#include "../includes/minishell.h"

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
		//ft_putstr_fd("\b\b  ", 2);
		ft_putstr_fd("\n", 2);
		ft_putstr_fd("$> ", 2);
	}
	else if (signal == SIGQUIT && !cont->child_pid)
		return (0);
		//ft_putstr_fd("\b\b", 1);
	else if (signal == SIGINT || signal == SIGQUIT)
		kill(ptr->child_pid, signal);
	return (0);
}
