# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: minsunki <minsunki@student.42seoul.kr>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/04/22 23:04:25 by minsunki          #+#    #+#              #
#    Updated: 2021/05/07 19:07:54 by minsunki         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	cub3D

SRCF		=	sources
INCF		=	includes

SRCS_R		=	main.c \
				cub_parse.c \
				map_parse.c \
				error.c \
				cubd.c \
				map_validate.c 
SRCS		=	$(addprefix $(SRCF)/, $(SRCS_R))

OBJS		=	$(SRCS:.c=.o)
CC			=	gcc
CFLAG		=	#-Wall -Wextra -Werror
RM			=	rm -f


$(NAME)		:	$(OBJS)
			make all -C $(SRCF)/libft
			$(CC) $(OBJS) -L$(SRCF)/mlx_linux -lmlx \
			-L/usr/lib -lXext -lX11 -lm -lz \
			-L$(SRCF)/libft -lft \
			-o $(NAME)

clean		:
			$(RM) $(OBJS)
			make clean -C $(SRCF)/libft

all			:	$(NAME)

fclean		:	clean
			$(RM) $(NAME)
			make fclean -C $(SRCF)/libft

re			:	fclean all

bonus		:	all

.PHONY		:	.c.o all clean fclean re bonus
