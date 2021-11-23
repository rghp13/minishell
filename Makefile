# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rponsonn <rponsonn@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/11/10 15:37:19 by dscriabi          #+#    #+#              #
#    Updated: 2021/11/23 13:23:28 by rponsonn         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

Motto = ascii.txt

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
SRC_NAME				=		main.c

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
								${CC} $^ -o $@ ${CFLAG} ${PATH_LIB}/${LIBFT_A}
								@echo "${GREEN}[ COMPLETE ]${NC}\n"
								@cat "${Motto}"
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