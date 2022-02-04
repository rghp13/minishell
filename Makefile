define HEADER
                          _    _      _                               _                 _              _   _                      _                              _                 _    
     /\\                  | |  | |    (_)                             | |               | |            | | (_)                    | |                            (_)               | |   
    /  \\    _ __   _   _ | |_ | |__   _  _ __    __ _   _ __    ___  | |_    __ _  ___ | | __ ___   __| |  _  ___   _ __    ___  | |_   _ __  ___   __ _  _   _  _  _ __  ___   __| |   
   / /\\ \\  | '_ \\ | | | || __|| '_ \\ | || '_ \\  / _` | | '_ \\  / _ \\ | __|  / _` |/ __|| |/ // _ \\ / _` | | |/ __| | '_ \\  / _ \\ | __| | '__|/ _ \\ / _` || | | || || '__|/ _ \\ / _` |   
  / ____ \\ | | | || |_| || |_ | | | || || | | || (_| | | | | || (_) || |_  | (_| |\\__ \\|   <|  __/| (_| | | |\\__ \\ | | | || (_) || |_  | |  |  __/| (_| || |_| || || |  |  __/| (_| | _ 
 /_/    \\_\\|_| |_| \\__, | \\__||_| |_||_||_| |_| \\__, | |_| |_| \\___/  \\__|  \\__,_||___/|_|\\_\\\\___| \\__,_| |_||___/ |_| |_| \\___/  \\__| |_|   \\___| \\__, | \\__,_||_||_|   \\___| \\__,_|(_)
                    __/ |                        __/ |                                                                                                | |                               
                   |___/                        |___/                                                                                                 |_|                               
endef
export HEADER

NC = \033[0m
RED = \033[0;91m
ORANGE = \033[93m
GREEN = \033[32m
PURPLE = \033[0;95m
BLUE = \033[0;34m
BOLD = \033[1m
CYAN = \033[36m

PATH_SRC				=		./srcs
PATH_HEAD				=		./includes
PATH_LIB				=		./libft
SRC_NAME				=		env.c \
								env2.c \
								env3.c \
								exec.c \
								exec2.c \
								builtin_export.c \
								free.c \
								function_parsing.c \
								main.c \
								utils.c \
								parse_utils1.c \
								parse_utils2.c \
								variable_substitution.c \
								varsub_utils.c \
								singals.c \
								bracket_split.c \
								fd_ops.c \
								builtin.c \
								syntax.c \
								builtin_unset.c \
								builtin_env.c \
								builtin_pwd.c \
								builtin_cd.c \
								builtin_exit.c \
								builtin_echo.c

NAME					=		minishell
OBJ_NAME				=		$(SRC_NAME:.c=.o)
CC						=		clang
RM						=		rm -f
CFLAG					=		-g #-Wall -Wextra -Werror
SRC						=		$(addprefix $(PATH_SRC)/,$(SRC_NAME))
OBJ						=		$(addprefix $(PATH_SRC)/,$(OBJ_NAME))
LIBFT_A					=		libft.a
.c.o:
								@${CC} ${CFLAG} -I${PATH_HEAD} -c $< -o ${<:.c=.o}
								@echo "${GREEN}[ OK ] ${<:.s=.o}${NC}"
${NAME}:						${OBJ}
								@make -C ${PATH_LIB}
								@${CC} $^ -o $@ ${CFLAG} ${PATH_LIB}/${LIBFT_A} -lreadline
								@echo "${GREEN}[ COMPLETE ]${NC}\n"
								@echo "$$HEADER"
all:							${NAME}

clean:
								@${RM} ${OBJ}
								@make -C ${PATH_LIB} clean
								@echo "\n${GREEN}[ OK ]${RED}    *.o files deleted${NC}"
fclean:							clean
								@${RM} ${NAME}
								@make -C ${PATH_LIB} fclean
								@echo "${GREEN}[ OK ]${RED}    ${NAME}    deleted${NC}"
re:								fclean ${NAME}
.PHONY:							all clean fclean re