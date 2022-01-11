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
	t_cmd	*cmd;
	t_env	*env;
}				t_cont;

/*
**UTILS.C
*/
int		small_malloc(void **ptr, size_t size);
int		ft_error(int erno);
int		ft_free_all_split(char **split);

/*
**FUNCTION_PARSING.C
*/
int		parse_command(char *line, t_cmd **list);
void	print_command_list(t_cmd *list);
t_cmd	*init_cmd(char *cmd);
t_cmd	*add_cmd(t_cmd *list, char *cmd);
int		free_parse(t_cmd *list);
int		has_pipe(char *str);
/*
**EXEC.C
*/
void	exec_cmd(char **cmd, char **envp);
void	get_abs_path(char **cmd);
/*
**ENV.C
*/
t_env	*get_env(char **envp);
void	add_last(t_env *head, t_env *current);
int		assign_env_to_struct(t_env *current, char *envp);
char	*get_key_val(const char *key, t_env *env);
t_env	*find_env(const char *key, t_env *head);

/*
**FREE.C
*/
void	free_envp(t_env *current, t_env *head);

int		substitute_variables(t_cont *cont);

#endif
