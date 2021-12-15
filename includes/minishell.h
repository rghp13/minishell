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

int		small_malloc(void **ptr, size_t size);
void	exec_cmd(char **cmd, char **envp);
#endif
