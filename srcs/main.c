/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rponsonn <rponsonn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/17 02:44:29 by dimitriscr        #+#    #+#             */
/*   Updated: 2022/02/17 14:19:21 by rponsonn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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
		parsed_line = readline("$> ");
		if (!parsed_line)
		{
			rl_clear_history();
			ft_putstr_fd("exit\n", STDERR_FILENO);
			break ;
		}
		add_history(parsed_line);
		if (!parsing_manager(parsed_line, cont))
			execution_manager(cont);
		free_parse(cont->cmd);
		cont->cmd = NULL;
	}
	return (0);
}

int	main(int argc, char const *argv[], char **envp)
{
	struct termios	original;
	t_cont			cont;

	(void)argc;
	(void)argv;
	initialize_main_struct(&cont, envp, &original);
	main_loop(&cont);
	cleanup(cont, original);
	return (cont.exit_status);
}
