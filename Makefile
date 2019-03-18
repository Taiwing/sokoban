CC			=	gcc
CFLAGS		=	-g

NAME		=	sokoban

SRC_DIR		=	src

SRCS		=	editeur.c			\
				fEditeur.c			\
				fenetre.c			\
				fPartie.c			\
				main.c				\
				menus.c				\
				niveaux.c			\
				partie.c			\

INCS		=	$(SRCS:.c=.h)

SRC			=	$(addprefix $(SRC_DIR)/,$(SRCS))

OBJ_DIR		=	obj

OBJS		=	$(SRCS:.c=.o)
OBJ			=	$(addprefix $(OBJ_DIR)/,$(OBJS))

INC_DIR		=	includes
INC			=	$(addprefix $(INC_DIR)/,$(INCS))

SDL_ROOT	=	src/sdl2
SDL_BUILD	=	$(SDL_ROOT)/build
SDL_SRC		=	$(SDL_ROOT)/src
SDL_DIR		=	$(SDL_ROOT)/lib
SDL_LIB		=	$(SDL_DIR)/libSDL2.a
SDL_INC		=	$(SDL_ROOT)/include/SDL2

INC_FLAGS	=	-I $(INC_DIR) -I $(SDL_INC)
LINK_FLAGS	=	-L $(SDL_DIR) -lSDL2

all:			$(NAME)

$(NAME):		$(SDL_LIB) $(OBJ_DIR) $(OBJ)
	@$(CC) $(CFLAGS) -o $(NAME) $(OBJ) $(INC_FLAGS) $(LINK_FLAGS)

message:
	@echo compiling $(NAME)...

$(OBJ_DIR)/%.o:	$(SRC_DIR)/%.c $(INC) 
	@$(CC) $(CFLAGS) -c $< -o $@ $(INC_FLAGS)

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

$(SDL_LIB):
	mkdir -p $(SDL_BUILD) && cd $(SDL_BUILD) && ../configure --prefix=$$PWD/../
	$(MAKE) -C $(SDL_BUILD)
	$(MAKE) -C $(SDL_BUILD) install

clean:
	@echo cleaning objects...
	@rm -rf $(OBJ_DIR)

cleansdl:
	@$(MAKE) -C $(SDL_BUILD) clean && $(MAKE) -C $(SDL_BUILD) uninstall

fclean:
	@$(MAKE) clean
	@echo cleaning binaries...
	@rm -f $(NAME)

re:
	@$(MAKE) fclean
	@$(MAKE) all

.PHONY:			all clean fclean re

