# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: groubaud <groubaud@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/08/31 15:34:29 by user42            #+#    #+#              #
#    Updated: 2021/12/05 15:06:18 by groubaud         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	=	minishell

D_LIBFT	=	./lib/groubaud_libft/

D_INC_L	=	$(D_LIBFT)/includes/
D_INC	=	./includes/

D_EXEC	=	./exec_bin/
D_UTILS	=	./utils/
D_BUILT	=	./builtins/

LIBFT	=	-L $(D_LIBFT) -lft

INCLUDE	=	$(D_INC)minishell.h
I_INC	=	-I $(D_INC_L) -I $(D_INC)

S_EXEC	=	pipe redir_in_out
S_UTILS	=	main init convert free
S_BUILT	=	env getenv

SRCS	=	$(addprefix $(D_EXEC)ft_, $(addsuffix .c, $(S_EXEC))) \
			$(addprefix $(D_UTILS)ft_, $(addsuffix .c, $(S_UTILS))) \
			$(addprefix $(D_BUILT)ft_, $(addsuffix .c, $(S_BUILT)))

OBJS	=	$(addprefix $(D_EXEC)ft_, $(addsuffix .o, $(S_EXEC))) \
			$(addprefix $(D_UTILS)ft_, $(addsuffix .o, $(S_UTILS))) \
			$(addprefix $(D_BUILT)ft_, $(addsuffix .o, $(S_BUILT)))

CFLAGS	=	-Wall -Wextra -Werror

CC		=	gcc

all		:	$(NAME)

%.o		:	%.c $(INCLUDE)
			$(CC) $(CFLAGS) $(I_INC) -c -o $@ $<

lib		:
			make -C $(D_LIBFT)

$(NAME)	:	$(OBJS) $(INCLUDE)
			make lib
			$(CC) $(CFLAGS) $(I_INC) $(OBJS) $(LIBFT) -o $(NAME)

clean	:
			rm -rf $(OBJS)
#			make -C $(D_LIBFT) clean

fclean	:	clean
			rm -f $(NAME)
			make -C $(D_LIBFT) fclean

re		:	fclean all

.PHONY	:	all clean fclean re lib