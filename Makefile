# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: minsunki <minsunki@student.42seoul.kr>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/04/22 23:04:25 by minsunki          #+#    #+#              #
#    Updated: 2021/05/28 23:34:22 by minsunki         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	cub3D

SRCF		=	sources
SRCF_B		=	$(SRCF)/bonus
INCF		=	includes

FIL_M		=	main \
				cub_parse \
				cub_parse_util \
				map_parse \
				map_validate \
				map_validate_util \
				mmlx \
				render \
				meta \
				hook \
				player \
				mexit 

FIL_B		=	bitmap

SRCS_M		=	$(addsuffix .c, $(addprefix $(SRCF)/, $(FIL_M)))
SRCS_B		=	$(addsuffix _bonus.c, $(addprefix $(SRCF_B)/, $(FIL_M) $(FIL_B)))

OBJS_M		=	$(SRCS_M:.c=.o)
OBJS_B		=	$(SRCS_B:.c=.o)

CC			=	gcc
CFLAGS		=	-O3 -Wall -Wextra -Werror
CFLAG_EXT	=	-L$(SRCF)/mlx_linux -lmlx \
				-L/usr/lib -lXext -lX11 -lm -lz \
				-L$(SRCF)/libft -lft 
RM			=	rm -f

%.o			:	%.c
			$(CC) $(CFLAGS) -c $< -o $@

$(NAME)		:	$(OBJS_M)
			make all -C $(SRCF)/libft -j16
			$(CC) $(OBJS_M) $(CFLAG) $(CFLAG_EXT) -o $(NAME)

bonus		:	$(OBJS_B)
			make all -C $(SRCF)/libft
			$(CC) $(OBJS_B) $(CFLAG) $(CFLAG_EXT) -o $(NAME)

clean		:
			$(RM) $(OBJS_M) $(OBJS_B)
			make clean -C $(SRCF)/libft

all			:	$(NAME)

fclean		:	clean
			$(RM) $(NAME)
			make fclean -C $(SRCF)/libft

re			:	fclean all


.PHONY		:	.c.o all clean fclean re bonus
