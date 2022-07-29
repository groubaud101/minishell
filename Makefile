# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: groubaud <groubaud@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/08/31 15:34:29 by user42            #+#    #+#              #
#    Updated: 2022/07/29 12:34:02 by groubaud         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	=	minishell

D_LIBFT	=	./lib/groubaud_libft/

D_INC_L	=	$(D_LIBFT)/includes/
D_INC	=	./includes/

D_EXEC	=	./exec/
D_UTILS	=	./utils/
D_BUILT	=	./builtins/
D_PARS	=	./parsing/

LIBFT	=	-L $(D_LIBFT) -lft -lreadline

INCLUDE	=	$(D_INC)minishell.h
I_INC	=	-I $(D_INC_L) -I $(D_INC) -I.

LIBFT	+=	-L $(shell brew --prefix readline)/lib
I_INC	+=	-I $(shell brew --prefix readline)/include

S_EXEC	=	pipe exec choose_the_exec redir_in_out
S_UTILS	=	main init convert signal exit_error check_syntax
S_BUILT	=	env getenv cd pwd export_to_env export display_export \
			exec_builtin unset echo exit
S_PARS	=	envars init parse quotes_utils quotes save_chev save \
			token utils check_no_word

SRCS	=	$(addprefix $(D_EXEC)ft_, $(addsuffix .c, $(S_EXEC))) \
			$(addprefix $(D_UTILS)ft_, $(addsuffix .c, $(S_UTILS))) \
			$(addprefix $(D_BUILT)ft_, $(addsuffix .c, $(S_BUILT))) \
			$(addprefix $(D_PARS), $(addsuffix .c, $(S_PARS)))

OBJS	=	$(addprefix $(D_EXEC)ft_, $(addsuffix .o, $(S_EXEC))) \
			$(addprefix $(D_UTILS)ft_, $(addsuffix .o, $(S_UTILS))) \
			$(addprefix $(D_BUILT)ft_, $(addsuffix .o, $(S_BUILT))) \
			$(addprefix $(D_PARS), $(addsuffix .o, $(S_PARS)))

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
			make -C $(D_LIBFT) clean

fclean	:	clean
			rm -f $(NAME)
			make -C $(D_LIBFT) fclean

re		:	fclean all

.PHONY	:	all clean fclean re lib
