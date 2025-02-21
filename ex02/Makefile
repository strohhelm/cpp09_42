# /* ************************************************************************** */
# /*                                                                            */
# /*                                                        :::      ::::::::   */
# /*   Makefile                                           :+:      :+:    :+:   */
# /*                                                    +:+ +:+         +:+     */
# /*   By: pstrohal <pstrohal@42.heilbronn.de>        #+#  +:+       +#+        */
# /*                                                +#+#+#+#+#+   +#+           */
# /*   Created: 2024-12-19 22:07:15 by pstrohal          #+#    #+#             */
# /*   Updated: 2024-12-19 22:07:15 by pstrohal         ###   ########.fr       */
# /*                                                                            */
# /* ************************************************************************** */

NAME = PmergeMe

CC = c++


SRC_DIR := ./src/
OBJ_DIR = ./obj
INC_DIR := ./inc
DEP_DIR := $(OBJ_DIR)


vpath %.cpp $(SRC_DIR)
vpath %.hpp $(INC_DIR)
vpath %.d $(DEP_DIR)


FILES =	main.cpp\
		PmergeMe.cpp\
		PmergeMe2.cpp



SRC = $(addprefix $(SRC_DIR)/, $(FILES))
OBJ =	$(addprefix $(OBJ_DIR)/, $(FILES:%.cpp=%.o))

DEP:= $(OBJ:.o=.d)
DEPFLAGS = -MMD -MP
FLAGS =  -std=c++17 -O0 -g -Wall -Wextra -Werror
INCLUDES = -I$(INC_DIR)

all: $(NAME)
-include $(DEP)


$(NAME):$(OBJ)
	@$(CC) $^ -o $@

$(OBJ_DIR)/%.o: %.cpp
	@mkdir -p $(dir $@)
	@$(CC) $(FLAGS) $(DEPFLAGS) $(INCLUDES) -c $< -o $@ -O0 -g

clean:
	@rm -rf $(OBJ_DIR)

fclean: clean
	@rm -rf $(NAME)

re: fclean all

.PHONY: clean fclean all re


# 38 39 41 43 45 48 51 53 55 58 61 65 69 73 77 80
# 38 39 41 43 45 48 51 54 57 60 62 64 67 69 71 75 79 83 87 91 95 99 103