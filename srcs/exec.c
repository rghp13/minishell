/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dimitriscr <dimitriscr@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/17 02:24:10 by dimitriscr        #+#    #+#             */
/*   Updated: 2022/02/17 02:24:12 by dimitriscr       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*
**main function that will run one command at a time in the list
**start by taking the first command, figuring out which is the correct path
**figure out if it needs to redirect and how to redirect
*/

int	exec_main(t_cont *cont)
{
	list_get_path(cont->cmd, cont->env);
	if (cont->cmd->next)
		return (pipe_execution(cont->cmd, cont));
	else if (cont->cmd->input_type > -1 || cont->cmd->output_type > -1)
	{
		if (prepare_redirection(cont->cmd, cont))
			return (-2);
		exec_bultin_bin_bridge(cont->cmd, cont);
	}
	else
		return (exec_bultin_bin_bridge(cont->cmd, cont));
	return (0);
}

int	exec_bultin_bin_bridge(t_cmd *cmd, t_cont *cont)
{
	struct termios	t;

	tcgetattr(0, &t);
	t.c_cc[VQUIT] = 034;
	tcsetattr(0, TCSANOW, &t);
	if (check_builtin(cmd->arg[0]) == 1)
		run_builtin(cmd, cont);
	else
		exec_cmd(cmd, cont);
	tcgetattr(0, &t);
	t.c_cc[VQUIT] = 0;
	tcsetattr(0, TCSANOW, &t);
	return (0);
}

void	child(t_cmd *cmd, t_cont *cont)
{
	close(cont->pipefd[0]);
	if (execve(cmd->abspath, cmd->arg, cont->envstr) == -1)
	{
		perror("shell");
		exit(err_ret_value(errno, cmd));
	}
	exit(EXIT_SUCCESS);
}

void	exec_cmd(t_cmd *cmd, t_cont *cont)
{
	pid_t	pid;
	int		status;

	status = 0;
	pid = fork();
	if (pid == -1)
		perror("fork");
	else if (pid > 0)
	{
		if (cmd->next == NULL)
		{
			cont->child_pid = pid;
			waitpid(pid, &status, 0);
			kill(pid, SIGTERM);
			if (WIFEXITED(status))
				cont->exit_status = WEXITSTATUS(status);
			else if (WIFSIGNALED(status))
				cont->exit_status = (128 + WTERMSIG(status));
			cont->child_pid = 0;
		}
	}
	else
		child(cmd, cont);
}
