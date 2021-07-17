# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fhamel <fhamel@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/04/25 20:20:38 by florianhame       #+#    #+#              #
#    Updated: 2021/07/17 12:26:47 by fhamel           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

################################################################################
#####                              FILES VARS                              #####
################################################################################

PIPEX		=	pipex

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

_SRC_B	=		start_pipex.c \
				path_bin.c \
				pipex.c \
				utils.c \
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

$(D_OBJS) :
	@mkdir -p $@

$(LIBFT) :
	@make -C $(D_LIBFT)

$(D_OBJS)%.o : $(D_SRCS)%.c
	$(CC) $(FLAGS) -c $< -o $@ -Iincludes -Ilibft/includes

$(PIPEX_M) : $(OBJS)
	$(CC) $(OBJS) -L$(D_LIBFT) -lft -o $(PIPEX)

$(PIPEX_B) : $(OBJS_B)
	$(CC) $(OBJS_B) -L$(D_LIBFT) -lft -o $(PIPEX)

clean :
	rm -rf $(D_OBJS)
	make clean -C $(D_LIBFT)

fclean : clean
	rm -rf $(PIPEX)
	rm -rf $(D_LIBFT)$(LIBFT)

re : fclean all
