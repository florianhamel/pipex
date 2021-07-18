# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fhamel <fhamel@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/04/25 20:20:38 by florianhame       #+#    #+#              #
#    Updated: 2021/07/18 02:23:41 by fhamel           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

################################################################################
#####                              FILES VARS                              #####
################################################################################

NAME		=	pipex

PIPEX_M		=	pipex_mandatory

PIPEX_B		=	pipex_bonus

D_INCLUDES	=	includes/

D_OBJS		=	objs/

D_SRCS		=	srcs/

_SRC_		=	main.c \
				start_pipex.c \
				path_bin.c \
				pipex.c \
				utils.c \
				free_exit.c \

_SRC_B	=		start_pipex.c \
				path_bin.c \
				pipex.c \
				utils.c \
				free_exit.c \
				main_bonus.c \
				multi_pipex_bonus.c \
				here_doc_bonus.c \
				gnl_bonus.c \
				gnl_utils_bonus.c \

SRCS		=	$(addprefix $(D_SRCS), $(_SRC_))

OBJS		=	$(addprefix $(D_OBJS), $(_SRC_:.c=.o))

SRCS_B		=	$(addprefix $(D_SRCS), $(_SRC_B))

OBJS_B		=	$(addprefix $(D_OBJS), $(_SRC_B:.c=.o))

D_LIBFT		=	libft/

LIBFT		=	libft.a

################################################################################
#####                           COMPILER OPTIONS                           #####
################################################################################

CC			=	clang

FLAGS		=	-Wall -Wextra -Werror

FSANITIZE	=	-g -fsanitize=address

################################################################################
#####                            MAKEFILE RULES                            #####
################################################################################

all	: $(D_OBJS) $(LIBFT) $(PIPEX_M)

bonus : $(D_OBJS) $(LIBFT) $(PIPEX_B)

compiling_start_m :
	@python -c 'print "\033[0;33mCompiling \033[0;34m$(NAME)\033[0;33m sources..."'

compiling_end_m :
	@python -c 'print "\033[0;32mCompiling successful \xE2\x9C\x94 \033[0m"'

compiling_start_b :
	@python -c 'print "\033[0;33mCompiling \033[0;34m$(NAME)\033[0;33m bonus sources..."'

compiling_end_b :
	@python -c 'print "\033[0;32mCompiling bonuses successful \xE2\x9C\x94 \033[0m"'

$(D_OBJS) :
	@mkdir -p $@

$(LIBFT) :
	@make -C $(D_LIBFT)

$(D_OBJS)%.o : $(D_SRCS)%.c
	$(CC) $(FLAGS) -c $< -o $@ -Iincludes -Ilibft/includes

$(PIPEX_M) : compiling_start_m $(OBJS) compiling_end_m
	@python -c 'print "\033[0;33mLinking objects for \033[0;34m$(NAME)\033[0;33m... \033[0m"'
	@$(CC) $(OBJS) -L$(D_LIBFT) -lft -o $(NAME)
	@python -c 'print "\033[0;32mLinking successful \xE2\x9C\x94 \033[0m"'

$(PIPEX_B) : compiling_start_b $(OBJS_B) compiling_end_b
	@python -c 'print "\033[0;33mLinking objects for \033[0;34m$(NAME)\033[0;33m... \033[0m"'
	@$(CC) $(OBJS_B) -L$(D_LIBFT) -lft -o $(NAME)
	@python -c 'print "\033[0;32mLinking successful \xE2\x9C\x94 \033[0m"'

clean :
	@rm -rf $(D_OBJS)
	@make clean -C $(D_LIBFT)
	@python -c 'print "\033[0;33mObjects deleted \xE2\x9C\x94 \033[0m"'

fclean : clean
	@rm -rf $(D_LIBFT)$(LIBFT)
	@rm -rf $(NAME)
	@python -c 'print "\033[0;34m$(LIBFT) \033[0;33mdeleted \xE2\x9C\x94 \033[0m"'
	@python -c 'print "\033[0;34m$(NAME) \033[0;33mdeleted \xE2\x9C\x94 \033[0m"'
re : fclean all
