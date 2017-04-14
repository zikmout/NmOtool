# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ssicard <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/04/10 16:25:02 by ssicard           #+#    #+#              #
#    Updated: 2017/04/14 10:54:19 by ssicard          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = ft_nm
CCLIB = -Llibft -lft
CCFLAGS = -Wall -Werror -Wextra
SRCDIR = src
OBJDIR = obj
INCDIR = includes libft printf/includes

SRC =	main.c\
		utils.c\
		header.c\
		sections.c\
		sections2.c\
		symtab.c\
		list.c\
		list2.c\
		fat.c

SRCS = $(addprefix $(SRCDIR)/, $(SRC))
OBJS = $(addprefix $(OBJDIR)/, $(SRC:.c=.o))
INCS = $(addprefix -I , $(INCDIR))

all: $(NAME)
$(NAME): build $(OBJS)
	@make -C libft
	@gcc $(CCLIB) -o $(NAME) $(OBJS)

build:
	@mkdir -p $(OBJDIR)

clean:
	@make -C libft clean
	@rm -f $(OBJS)

fclean: clean
	@make -C libft fclean
	@rm -f $(NAME)

re: fclean all

dev : all
	@./$(NAME)

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	@gcc -c $(CCFLAGS) $(INCS) -o $@ $<
