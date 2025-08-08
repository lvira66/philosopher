#/* ************************************************************************** */
#/*                                                                            */
#/*                                                        :::      ::::::::   */
#/*   Makefile                                           :+:      :+:    :+:   */
#/*                                                    +:+ +:+         +:+     */
#/*   By: lviravon <marvin@d42.fr>                   +#+  +:+       +#+        */
#/*                                                +#+#+#+#+#+   +#+           */
#/*   Created: 2025/08/07 22:59:41 by lviravon          #+#    #+#             */
#/*   Updated: 2025/08/07 22:59:41 by lviravon         ###   ########.fr       */
#/*                                                                            */
#/* ************************************************************************** */

NAME = philo
CFLAGS = -Wall -Wextra -Werror -pthread -g

DIR_SOURCE = ./src
DIR_HEADERS = ./inc
DIR_OBJ = ./obj

VPATH = $(shell find $(DIR_SOURCE) -type d)
SRCS = $(shell find $(DIR_SOURCE) -type f -name "*.c")
OBJ = $(patsubst $(DIR_SOURCE)/%.c, $(DIR_OBJ)/%.o, $(SRCS))

all: $(NAME)

$(NAME): $(OBJ)
	@cc $(CFLAGS) -I $(DIR_HEADERS)  -o $@ $^

$(DIR_OBJ)/%.o: $(DIR_SOURCE)/%.c $(DIR_HEADERS)/philo.h
	$(shell mkdir -p $(dir $@))
	@cc $(CFLAGS) -I $(DIR_HEADERS) -o $@ -c $<
	@echo "Compile "$<""

clean:
	@rm -rf $(DIR_OBJ)
	@echo "Supr objs"

fclean: clean
	@rm -f $(NAME)
	@echo "CLEAR !"

re: fclean all

.PHONY: all clean fclean re
