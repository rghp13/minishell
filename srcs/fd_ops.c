#include "../includes/minishell.h"

void	fd_reset(t_cont *cont)
{
	dup2(cont->fd_in_perm, 0);
	dup2(cont->fd_in_perm, 1);
}

void	fd_close(t_cont *cont)
{
	if (cont->fd_in > 0)
		close(cont->fd_in > 0);
	if (cont->fd_out)
		close(cont->fd_out);
	if (cont->pipe_in > 0)
		close(cont->pipe_in);
	if (cont->pipe_out > 0)
		close(cont->pipe_out);
}

void	fd_zero(t_cont *cont)
{
	cont->fd_in = -1;
	cont->fd_out = -1;
	cont->pipe_in = -1;
	cont->pipe_out = -1;
}

void	fd_inits(t_cont *cont)
{
	cont->fd_in_perm = dup(0);
	cont->fd_out_perm = dup(1);
	fd_zero(cont);
}
