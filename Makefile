# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ohakola <ohakola@student.hive.fi>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/02/01 15:58:30 by ohakola           #+#    #+#              #
#    Updated: 2020/10/02 15:45:13 by ohakola          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = gcc
NAME = ohakola.filler
LIBFT = ./lib/libft
LIBMLX = ./lib/libmlx
DIR_SRC = ./src
DIR_OBJ = temp
HEADERS = ./incl
FLAGS = -Wall -Wextra -Werror -O2
LIBMLXFLAGS = -L$(LIBMLX) -lmlx -framework OpenGL -framework Appkit
LIBFTFLAGS = -L$(LIBFT) -lft
SOURCES = main.c \
			log.c \
			window.c \
			ui.c \
			read.c \
			read_utils.c \
			place.c \
			place_utils.c \
			board.c \
			piece.c \
			score.c \
			draw/grid.c \
			draw/score.c \
			draw/draw.c \
			draw/rectangle.c \
			draw/triangle.c \
			draw/numbers1.c \
			draw/numbers2.c \
			events/keys.c \
			events/mouse.c \
			events/loop.c \
			events/exit.c

SRCS = $(addprefix $(DIR_SRC)/,$(SOURCES))
OBJS = $(addprefix $(DIR_OBJ)/,$(SOURCES:.c=.o))
INCLUDES = -I./incl/ -I$(LIBFT)/include -I$(LIBMLX)

all: $(DIR_OBJ) $(NAME)

$(NAME): $(OBJS)
	@make -C $(LIBFT)
	@make -C $(LIBMLX)
	$(CC) $(FLAGS) $(LIBFTFLAGS) $(LIBMLXFLAGS) -o $@ $^

$(DIR_OBJ):
	@mkdir -p temp
	@mkdir -p temp/draw
	@mkdir -p temp/events

$(DIR_OBJ)/%.o: $(DIR_SRC)/%.c
	@$(CC) $(INCLUDES) $(FLAGS) -c -o $@ $<

clean:
	@/bin/rm -f $(OBJS)
	@make -C $(LIBFT) clean
	@make -C $(LIBMLX) clean
	@/bin/rm -rf $(DIR_OBJ)

fclean: clean
	@/bin/rm -f $(NAME)
	@make -C $(LIBFT) fclean
	@make -C $(LIBMLX) fclean

norm:
	norminette $(LIBFT) $(DIR_SRC) $(HEADERS)

test_quick_p1:
	./test_run.sh p1 quick

test_slow_p1:
	./test_run.sh p1 thorough

test_quick_p2:
	./test_run.sh p2 quick

test_slow_p2:
	./test_run.sh p2 thorough

re: fclean all

.PHONY: all, $(DIR_OBJ), clean, fclean, norm, test_quick_p1, test_quick_p2, test_slow_p1, test_slow_p2
