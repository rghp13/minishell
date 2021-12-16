#ifndef MINISHELL_H
# define MINISHELL_H
# include "libft.h"
# include <stdarg.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <fcntl.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <sys/time.h>
# include <sys/resource.h>
# include <sys/ioctl.h>
# include <signal.h>
# include <dirent.h>
# include <termios.h>
# define ER1 "ERROR: SHELL MISSING ENV VARIABLES"

typedef struct s_cmd
{
	char			*cmd;
	struct s_cmd	*next;
	struct s_cmd	*prev;
	struct s_cmd	*pipechain;
}						t_cmd;

typedef struct s_env
{
	char			*key;
	char			*value;
	struct s_env	*prev;
	struct s_env	*next;
}					t_env;

typedef struct s_cont
{
	t_cmd	cmd;
	t_env	*env;
}				t_cont;

/*
**UTILS.C
*/
int		small_malloc(void **ptr, size_t size);
int		ft_error(int erno);
/*
**FUNCTION_PARSING.C
*/
void	exec_cmd(char **cmd, char **envp);
int		parse_command(char *line, t_cmd **list);
void	print_command_list(t_cmd *list);
t_cmd	*init_cmd(char *cmd);
t_cmd	*add_cmd(t_cmd *list, char *cmd);
/*
**EXEC.C
*/
void	exec_cmd(char **cmd, char **envp);
void	get_abs_path(char **cmd);
/*
**ENV.C
*/
t_cont	*get_env(char **envp);
void	split_free(char **str);

#endif
