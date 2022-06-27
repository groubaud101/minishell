# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jrobert <jrobert@student.s19.be>           +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/08/31 15:34:29 by user42            #+#    #+#              #
#    Updated: 2022/06/27 11:46:45 by jrobert          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	=	minishell

D_LIBFT	=	./lib/groubaud_libft/

D_INC_L	=	$(D_LIBFT)/includes/
D_INC	=	./includes/

D_EXEC	=	./exec_bin/
D_UTILS	=	./utils/
D_BUILT	=	./builtins/
D_PARS	=	./parsing/
D_TRAN	=	./transition/

LIBFT	=	-L $(D_LIBFT) -lft

INCLUDE	=	$(D_INC)minishell.h
I_INC	=	-I $(D_INC_L) -I $(D_INC)

S_EXEC	=	pipe redir_in_out
S_UTILS	=	main init convert
S_BUILT	=	env getenv cd pwd export_to_env export display_export \
			exec_builtin
S_PARS	=	jrobert utils
S_TRAN	=	choose_the_exec

SRCS	=	$(addprefix $(D_EXEC)ft_, $(addsuffix .c, $(S_EXEC))) \
			$(addprefix $(D_UTILS)ft_, $(addsuffix .c, $(S_UTILS))) \
			$(addprefix $(D_BUILT)ft_, $(addsuffix .c, $(S_BUILT))) \
			$(addprefix $(D_PARS), $(addsuffix .c, $(S_PARS))) \
			$(addprefix $(D_TRAN)ft_, $(addsuffix .c, $(S_TRAN)))

OBJS	=	$(addprefix $(D_EXEC)ft_, $(addsuffix .o, $(S_EXEC))) \
			$(addprefix $(D_UTILS)ft_, $(addsuffix .o, $(S_UTILS))) \
			$(addprefix $(D_BUILT)ft_, $(addsuffix .o, $(S_BUILT))) \
			$(addprefix $(D_PARS), $(addsuffix .o, $(S_PARS))) \
			$(addprefix $(D_TRAN)ft_, $(addsuffix .o, $(S_TRAN))) \

CFLAGS	=	-Wall -Wextra -Werror

CC		=	gcc

all		:	$(NAME)

%.o		:	%.c $(INCLUDE)
			$(CC) $(CFLAGS) $(I_INC) -c -o $@ $<

lib		:
			make -C $(D_LIBFT)

$(NAME)	:	$(OBJS) $(INCLUDE)
			make lib
			$(CC) $(CFLAGS) $(I_INC) $(OBJS) $(LIBFT) -lreadline -o $(NAME)

clean	:
			rm -rf $(OBJS)
#			make -C $(D_LIBFT) clean

fclean	:	clean
			rm -f $(NAME)
			make -C $(D_LIBFT) fclean

re		:	fclean all

.PHONY	:	all clean fclean re lib