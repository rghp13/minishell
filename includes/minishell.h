#ifndef MINISHELL_H
# define MINISHELL_H
# define _GNU_SOURCE
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
# include <stdint.h>//added for int to void* conversion in exec.c
# define ER1 "ERROR: SHELL MISSING ENV VARIABLES"
# define ERMEM "ERROR: MALLOC FAILED"

typedef struct s_cmd
{
	char			*cmd; /*The original unedited text that was inputed by the user*/
	char			**arg; /*The split command in the form of argv (doesn't contain redirecors)*/
	char			*abspath; /*You're using that*/
	char			*input; /*name of input file if there is one*/
	int				input_type; /*input mode, -1 if none, 0 if < and 1 if <<*/
	char			*output; /*name of output file if there is one*/
	int				output_type; /*output mode, -1 if none, 0 if > and 1 if >>*/
	struct s_cmd	*next; /*next function in the list that was separated with a ;*/
	struct s_cmd	*prev; /*previous function in the list that was separated with a ;*/
	struct s_cmd	*pipechain; /*function to pipe output too if there is one*/
}					t_cmd;

typedef struct s_env
{
	char			*key;
	char			*value;
	struct s_env	*prev;
	struct s_env	*next;
	struct s_cont	*cont;
}					t_env;

typedef struct s_cont
{
	int		fd_in_perm;
	int		fd_out_perm;
	int		fd_in;
	int		fd_out;
	int		pipe_in;
	int		pipe_out;
	int		child_pid;
	int		prev_ret;
	uint8_t	exit_status;
	int		exit_flag;
	char	**envstr;
	t_cmd	*cmd;
	t_env	*env;
}				t_cont;

typedef struct s_export
{
	int		i;
	t_env	*new_env;
	int		flag;
	char	**split;
}				t_export;
/*
**BUILTIN.C
*/
int		check_builtin(const char *cmd);
void	run_builtin(t_cmd *cmd, t_cont *cont);
/*
**SYNTAX.C
*/
int		syntax_check(char *cmd);
/*
**UTILS.C
*/
int		small_malloc(void **ptr, size_t size);
int		ft_error(int erno);
int		ft_free_all_split(char **split);
void	add_last(t_env *head, t_env *current);
int		update_envstr(t_cont *cont);
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
void	exec_main(t_cont *cont);
void	exec_cmd(t_cmd *cmd, t_cont *cont);
int		list_get_path(t_cmd *cmd, t_env *env);
char	*get_abs_path(const char *src, t_env *env);
int		merge_path_name(char **path, const char *name);
/*
**ENV.C
*/
t_env	*get_env(char **envp, t_cont *cont);
int		assign_env_to_struct(t_env *current, char *envp);
char	*get_key_val(const char *key, t_env *env);
t_env	*find_env(const char *key, t_env *head);
char	*strip_value(const char *key);
/*
**ENV2.C
*/
char	**output_env_array(t_env *head);
int		calculate_env_split(t_env *head);
int		remove_env(t_env *head, const char *key);
char	*env_str(t_env *env);
t_env	*add_env(const char *key, const char *value, t_cont *cont);
/*
**ENV3.C
*/
void	shell_lvl(t_cont *cont);
/*
**BUILTIN_EXPORT.C
*/
int		builtin_export(char **argv, t_cont *cont);
int		check_valid_export(const char *str, t_cont *cont, int *flag);
int		export_error(const char *str);
int		ft_isasymbol(const char str);
void	create_new_env(char *argv, t_cont *cont);

<<<<<<< HEAD
/*
**BUILTIN_UNSET.C
*/
int		builtin_unset(char **argv, t_cont *cont);
/*
**BUILTIN_ENV.C
*/
int		builtin_env(char **argv, t_cont *cont);
/*
**BUILTIN_PWD.C
*/
int		builtin_pwd(char **argv, t_cont *cont);
=======
>>>>>>> 1da7fef (removed forking for builtin, renamed export and unset file, fixed export to take into consideration if key already existed)
/*
**BUILTIN_UNSET.C
*/
int		builtin_unset(char **argv, t_cont *cont);
/*
**BUILTIN_ENV.C
*/
int		builtin_env(char **argv, t_cont *cont);
/*
**BUILTIN_PWD.C
*/
int		builtin_pwd(char **argv, t_cont *cont);
/*
**BUILTIN_CD.C
*/
int		builtin_cd(char **argv, t_cont *cont);
int		go_home(t_cont *cont);
int		cd_error_print(const char *str);
void	update_pwd_env(t_cont *cont, char *ptr);
/*
**BUILTIN_CD.C
*/
int		builtin_cd(char **argv, t_cont *cont);
int		go_home(t_cont *cont);
int		cd_error_print(const char *str);
void	update_pwd_env(t_cont *cont, char *ptr);
/*
**BUILTIN_EXIT.C
*/
int		builtin_exit(char **argv, t_cont *cont);
/*
**BUILTIN_ECHO.c
*/
int		builtin_echo(char **argv, t_cont *cont);
/*
**FREE.C
*/
void	free_envp(t_env *current, t_env *head);

int		substitute_variables(t_cont *cont);
int		create_argv(t_cmd *cmd);
int		is_word_to_replace(char *currentletter, char *word);
char	*substituestr(char *text, char *word, char *replacement, int start);
int		is_var_char(char c);
int		replace_var(char **cmd, int *i, t_env *envstart);
char	*get_var_name(char *var_start);
int		has_redirector(char *str);
int		argv_loop(t_cont *cont);
int		free_cmd(t_cmd *cmd);

void	init_singals(void);
void	signal_handler(int signal);
int		signal_redirector(t_cont *ptr, int signal, int mode);

int		update_bracket_status(int bracket, char c);
char	**ft_special_split(char	const *s, char c);

void	fd_inits(t_cont *cont);
void	fd_zero(t_cont *cont);
void	fd_close(t_cont *cont);
void	fd_reset(t_cont *cont);
#endif
