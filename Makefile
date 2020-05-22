NAME		:= pong_bkuksa

SRC_DIR		:= ./srcs
OBJ_DIR		:= ./obj

SRC			:=	main.cpp \
				Pong.cpp \
				Controller.cpp \
				View.cpp \
				Play.cpp

OBJ			:= $(addprefix $(OBJ_DIR)/,$(SRC:.cpp=.o))

CXX			:= g++
CXXFLAGS	:= -std=c++17 -Wno-deprecated -Wall -pedantic
LINKS       := -lSDL2 -lSDL2_mixer -lSDL2_ttf

GREEN = \033[0;32m
YELLOW = \033[0;33m
RED = \033[0;31m
RESET = \033[0m

.PHONY: all clean fclean re

all: $(OBJ_DIR) $(NAME)

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)
	@echo "$(YELLOW)[INFO]:$(RESET) $(GREEN)objects was created$(RESET)"

$(OBJ_DIR)/%.o:$(SRC_DIR)/%.cpp
	@$(CXX) $(CXXFLAGS) -o $@ -c $<
	@echo "$(GREEN)...$(RESET)\c"

$(NAME): $(OBJ)
	@$(CXX) $(OBJ) $(CXXFLAGS) $(LINKS) -o $(NAME)
	@echo "\n$(YELLOW)[INFO]:$(RESET) $(GREEN)$(NAME) was created$(RESET)"

clean:
	@rm -rf $(OBJ_DIR)
	@echo "$(YELLOW)[INFO]:$(RESET)$(RED) objects removed!$(RESET)"

fclean: clean
	@rm -f $(NAME)
	@echo "$(YELLOW)[INFO]:$(RESET)$(RED) $(NAME) removed!$(RESET)"

re:
	@$(MAKE) fclean --no-print-directory
	@$(MAKE) all --no-print-directory
