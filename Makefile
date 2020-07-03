NAME = wolf3d

FLAGS = -Wall -Werror -Wextra
XFLAGS = -lOpenCL -L -lmlx -lXext -lX11 -lm

HEADER_LIST = wolf3d.h\

SRC_LIST = wolf3d.c\
	read_file.c\
	utilits.c\


HEADERS = $(addprefix $(SRC_DIR), $(HEADER_LIST))
SRC = $(addprefix $(SRC_DIR), $(SRC_LIST))
SRC_DIR = ./src/
OBJ = $(addprefix $(OBJ_DIR), $(SRC_LIST:.c=.o))
OBJ_DIR = ./obj/

LIBX = $(LIBX_DIR)libmlx.a
LIBX_DIR = ./minilibx/

all: $(NAME)

$(NAME): $(OBJ_DIR) $(OBJ) $(LIBX)
	@gcc $(OBJ) $(LIBX) $(FLAGS) $(XFLAGS) -o $(NAME)

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

$(OBJ_DIR)%.o : $(SRC_DIR)%.c  $(HEADERS)
	@gcc -c $< -o $@ $(FLAGS)

$(LIBX):
	@make -C $(LIBX_DIR)

clean:
	@rm -rf $(OBJ_DIR)
	@make -C $(LIBX_DIR) clean

fclean: clean
	@rm -f $(NAME)

re: fclean all