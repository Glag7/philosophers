NAME = philo
NAME_BONUS = philo_bonus

COMP = clang
CFLAGS = -Wall -Wextra -g #-Werror

SRC_DIR = src/
OBJ_DIR = obj/
THREAD = thread/
FORK = fork/

SRC = $(addprefix $(THREAD), \
      main.c \
      start.c \
      utils.c \
      routine.c \
      output.c \
      )
SRC_BONUS = $(addprefix $(FORK), \
	    amogus \
	    )

OBJ = $(SRC:.c=.o)
OBJ_BONUS = $(SRC_BONUS:.c=.o)

all : $(NAME)
	echo no push

bonus : $(NAME_BONUS)
	echo no push

$(OBJ_DIR) :
	@mkdir -p $(OBJ_DIR)

$(THREAD) : $(OBJ_DIR)
	@mkdir -p $(OBJ_DIR)$(THREAD)

$(FORK) : $(OBJ_DIR)
	@mkdir -p $(OBJ_DIR)$(FORK)

$(NAME) : $(OBJ_DIR) $(THREAD) $(addprefix $(OBJ_DIR), $(OBJ))
	@$(COMP) $(CFLAGS) $(addprefix $(OBJ_DIR), $(OBJ)) -o $@

$(NAME_BONUS) : $(OBJ_DIR) $(FORK) $(addprefix $(OBJ_DIR), $(OBJ_BONUS))
	@$(COMP) $(CFLAGS) $(addprefix $(OBJ_DIR), $(OBJ_BONUS)) -o $@

$(OBJ_DIR)%.o : $(SRC_DIR)%.c
	@$(COMP) $(CFLAGS) -c $^ -o $@ -I includes/

clean :
	@rm -rf $(OBJ_DIR)

fclean : clean
	@rm -f $(NAME) $(NAME_BONUS)

re : fclean all

.PHONY: all fclean clean re bonus
