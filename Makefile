# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mkopiika <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/07/28 21:20:29 by mkopiika          #+#    #+#              #
#    Updated: 2019/07/28 21:20:32 by mkopiika         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	:= wolf3d

CC_FLG  = -Wall -Wextra -Werror

SOURCES		:=	raycast_alg.c\
			put_texture.c\
			maze_validation.c\
			main.c\
			key_events.c\
			get_error.c\
			game_loop.c\

DIR_SRC := $(CURDIR)/src
DIR_OBJ := $(CURDIR)/obj
OBJ_SRC  := $(SOURCES:.c=.o)
OBJ_SRC  := $(addprefix $(DIR_OBJ)/, $(OBJ_SRC))
SOURCES := $(addprefix $(DIR_SRC)/, $(SOURCES))
INCL_LB   =	-I libft/ \
			-I inc/
LIBFT    = libft/libft.a

FR_SDL  	=	-F frameworks
FLG_SDL 	=	-rpath frameworks		\
				-framework SDL2_image	\
				-framework SDL2 		\
				-framework SDL2_mixer
INCL_SDL   	=	-I $(CURDIR)/frameworks/SDL2_image.framework/Headers/	\
				-I $(CURDIR)/frameworks/SDL2.framework/Headers/ 		\
				-I $(CURDIR)/frameworks/SDL2_mixer.framework/Headers/	\

all: $(NAME)

$(LIBFT):
	@make -C libft/

$(DIR_OBJ):
	@mkdir -p $(DIR_OBJ)

$(NAME): $(LIBFT) $(OBJ_SRC)
	gcc $(OBJ_SRC) $(FR_SDL) $(FLG_SDL) -L libft -lft -o $(NAME)

$(DIR_OBJ)/%.o: $(DIR_SRC)/%.c | $(DIR_OBJ)
	gcc $(CC_FLG) $(FR_SDL) $(INCL_SDL) $(INCL_LB) -c $< -o $@

clean:
	@make -C libft/ clean
	/bin/rm -rf $(OBJ_SRC)
	/bin/rm -rf $(DIR_OBJ)

fclean: clean
	@make -C libft/ fclean
	/bin/rm -rf $(NAME)

re: fclean all

.PHONY: all fclean clean re