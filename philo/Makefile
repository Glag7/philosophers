NAME = philo

COMP = clang
CFLAGS = -Wall -Wextra -Werror

SRC_DIR = src/
OBJ_DIR = obj/
HDR_DIR = includes/

SRC = main.c \
      start.c \
      utils.c \
      start_routine.c \
      routine.c \
      output.c

OBJ = $(SRC:.c=.o)

all : $(NAME)

$(OBJ_DIR) :
	@mkdir -p $(OBJ_DIR)

$(NAME) : $(OBJ_DIR) $(addprefix $(OBJ_DIR), $(OBJ))
	@$(COMP) $(CFLAGS) $(addprefix $(OBJ_DIR), $(OBJ)) -o $@ -lpthread

$(OBJ_DIR)%.o : $(SRC_DIR)%.c
	@$(COMP) $(CFLAGS) -c $^ -o $@ -I $(HDR_DIR)

clean :
	@rm -rf $(OBJ_DIR)

fclean : clean
	@rm -f $(NAME)

re : fclean all

.PHONY: all fclean clean re
