# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jrobert <jrobert@student.s19.be>           +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/01/27 12:34:07 by jrobert           #+#    #+#              #
#    Updated: 2022/04/11 15:23:01 by jrobert          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS_FILES	= 	jrobert.c \
				utils.c \
				bi_echo.c \
				bi_env.c \
				bi_export.c
				
SRCS_DIR	= 	srcs/
SRCS		=	$(addprefix $(SRCS_DIR),$(SRCS_FILES))
OBJS		= 	$(SRCS:%.c=%.o)
NAME		=	minishell
CFLAGS		= 	-Wall -Wextra -Werror -I includes -I libft/includes
LIBFT 		= 	-L libft -lft
			
$(NAME)			:	$(OBJS)
					$(MAKE) -C ./libft/
					cc $(OBJS) -lreadline $(LIBFT) -o $(NAME)

all    			:	$(NAME)

clean 			:	
					rm -f $(OBJS)
					$(MAKE) clean -C ./libft/

fclean 			:	clean
					rm -f $(NAME)
					$(MAKE) fclean -C ./libft/
					
re				:	fclean all

.PHONY			: 	all clean fclean re
