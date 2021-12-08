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

typedef struct s_command
{
	char				*command;
	int					redirector;
	char				*file;
	int					separator;
	struct s_command	*next;
}				t_command;

int	main(void);
int	small_malloc(void **ptr, size_t size);
#endif
