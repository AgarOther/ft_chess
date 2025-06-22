# Compilation
CC					=	c++
CFLAGS				=	-Wall -Wextra -Werror -std=c++17 -g -MP -MMD
SFML_FLAGS			=	-lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio

# Names
NAME				=	ft_chess

# Sources & Includes
SRCS				= 	srcs/main.cpp \
						srcs/Grid.cpp \
						srcs/Texture.cpp \
						srcs/utils/chess_utils.cpp
OBJ_FOLDER			=	objs
INCLUDES			=	includes

# Objects
OBJS				=	$(patsubst srcs/%, $(OBJ_FOLDER)/%, $(SRCS:.cpp=.o))
DEPS				=	$(patsubst srcs/%, $(OBJ_FOLDER)/%, $(SRCS:.cpp=.d))

# Custom Makefile Flags
MAKEFLAGS			+=	--no-print-directory --silent

# Custom Colors
PURPLE				=	\033[1;35m
LIGHT_GREEN			=	\033[1;32m
RESET				=	\033[0m

# Custom messages
EXE_DONE			=	@echo "🎉$(PURPLE) $(NAME) compiled! 🎉$(RESET)\n"
ALL_CLEAN			=	@echo "🧹$(LIGHT_GREEN) Project's objects cleaned! 🧹$(RESET)\n"
ALL_FCLEAN			=	@echo "🧹$(LIGHT_GREEN) Project's objects & Executables cleaned! 🧹$(RESET)\n"

# Rules

all :
	@make -j4 $(NAME)

$(NAME): $(OBJS)
	@$(CC) $(CFLAGS) $(OBJS) -o $(NAME) $(SFML_FLAGS)
	$(EXE_DONE)

$(OBJ_FOLDER)/%.o: srcs/%.cpp
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) -I $(INCLUDES) -c $< -o $@

clean :
	@rm -rf $(OBJ_FOLDER)
	$(ALL_CLEAN)

fclean :
	@rm -f $(NAME)
	@rm -rf $(OBJ_FOLDER)
	$(ALL_FCLEAN)

re : fclean all

debug : CFLAGS += -DELEO_DEBUG
debug :
	$(MAKE) CFLAGS="$(CFLAGS)" -j4 $(NAME)

.PHONY: all clean fclean re

-include $(DEPS)