# Compiler and flags
CC		=	gcc -g
CFLAGS	=	-Wall -Werror -Wextra -Wunreachable-code
CFLAGS +=	-Ofast
RM		=	rm

#------------------------------------------------------------------------------#
#                                VARIABLES                                     #
#------------------------------------------------------------------------------#

ARGS	=	"./maps/cam_xyz.rt"
NAME	=	miniRt	

# Colors
YELLOW	=	\033[0;33m
GREEN	=	\033[0;32m
RED		=	\033[0;31m
BLUE	=	\033[0;34m
NC		=	\033[0m

# Directories
LIBDIR	=	lib/
INCDIR	=	include/
SRCDIR	=	src/
BONDIR	=	bonus_src/

# Libraries
LIBFT	=	$(LIBDIR)/libft/libft.a
MLXDIR	=	$(LIBDIR)/MLX42
LIBMLX	=	$(MLXDIR)/build/libmlx42.a

INCLUDES=	-I $(LIBDIR)/libft -I $(INCDIR) -I $(LIBDIR)/MLX42/include
LIBS	=	$(LIBFT) $(LIBMLX) -ldl -lglfw -pthread -lm -L$(shell brew --prefix glfw)/lib

# Dependencies 
BREW = /Users/$(USER)/.brew/bin/brew

# Sources

SRCS	:=	\
			main.c								\
			hooks.c								\
			hooks_light.c						\
			hooks_objects.c						\
			hooks_objects2.c					\
			hooks_cam.c						\
			object_matrix.c						\
			math/intersect.c					\
			math/intersect_utils.c					\
			math/obj_normals.c					\
			math/matrix.c						\
			math/inverse_matrix.c				\
			math/vec_operations.c				\
			math/vec_operations2.c				\
			math/vec_operations3.c				\
			math/vec_rotation.c					\
			math/math_utils.c					\
			parsing/parsing_attribute_utils.c	\
			parsing/parsing_attribute.c			\
			parsing/parsing_env.c				\
			parsing/parsing_objects.c			\
			parsing/parsing_utils.c				\
			parsing/parsing.c					\
			parsing/token.c						\
			render/colors.c						\
			render/render.c						\
			render/render_utils.c						\
			render/shading.c					\
			render/shading_utils.c					\
			utils/utils.c						\
			utils/atod.c						\
			utils/get_next_line_utils.c			\
			utils/get_next_line.c				\

B_SRCS	:=	$(SRCS:%.c=%_bonus.c)


# Objects
OBJDIR		:=	obj/
OBJS		:=	$(SRCS:%.c=$(OBJDIR)%.o)
SRCS		:=	$(SRCS:%.c=$(SRCDIR)%.c)
B_SRCS		:=	$(notdir $(B_SRCS))
B_OBJS		:=	$(B_SRCS:%.c=$(OBJDIR)%.o)
B_SRCS		:=	$(B_SRCS:%=$(BONDIR)%)
T_OBJS		:=	$(subst main,test,$(OBJS))
DEPS		:=	$(OBJS:%.o=%.d)


#------------------------------------------------------------------------------#
#                                TARGETS                                       #
#------------------------------------------------------------------------------#

all : $(NAME)

run : $(NAME)
	./$(NAME) $(ARGS)

# Compile Bonus
bonus : $(LIBMLX) $(LIBFT) $(B_OBJS)
	@echo "$(GREEN)	Compiling $@ ... $(NC)"
	$(CC) $(CFLAGS) $(B_OBJS) $(LIBS) -o $@ -I/bonus_src/ $(INCLUDES)

# Compile program
$(NAME) : $(LIBMLX) $(LIBFT) $(OBJS)
	@echo "$(GREEN)	Compiling $@ ... $(NC)"
	$(CC) $(CFLAGS) $(OBJS) $(LIBS) -o $@ -I. $(INCLUDES)

deps:
	@if [ ! -f $(BREW) ]; then \
		echo "Installing Homebrew"; \
		curl -fsSL https://rawgit.com/kube/42homebrew/master/install.sh | bash; \
	else \
		echo "Homebrew installed"; \
		brew update; \
	fi
	@if ! brew list | grep -q "glfw"; then \
		echo glfw not installed; \
		brew install glfw; \
	fi
	@if ! brew list | grep -q "cmake"; then \
		echo cmake not installed; \
	fi

test : $(LIBMLX) $(LIBFT) $(T_OBJS)
	@echo "$(YELLOW)	Compiling $@ ... $(NC)"
	@$(CC) $(CFLAGS) $(T_OBJS) $(LIBS) -o $@ -I. $(INCLUDES)
	./test

# Compile objects
$(OBJDIR)%.o : $(SRCDIR)%.c
	@mkdir -p $(@D);
	$(CC) -c $(CFLAGS) -MMD -MP $< -o $@ $(INCLUDES)
	
-include $(DEPS)

# Compile libftP
$(LIBFT):
	@ $(MAKE) -C $(LIBDIR)/libft -s

#Compiling libmlx
$(LIBMLX):
	cmake $(MLXDIR) -B $(MLXDIR)/build && make -C $(MLXDIR)/build -j4 -s

$(OBJDIR)%.o : $(BONDIR)%.c
	@mkdir -p $(OBJDIR);
	$(CC) -c $(CFLAGS) -MMD -MP $< -o $@ $(INCLUDES)

# Remove objects
clean :
	@$(RM) -rf $(OBJDIR)
	@$(RM) -rf $(NAME).dSYM
	@echo "$(RED)	Removed objects	$(NC)"

# Remove all
fclean : clean
	@$(RM) -f $(NAME) bonus
	@$(MAKE) fclean -C $(LIBDIR)/libft -s
	@echo "$(RED)	Removed executables and libft	$(NC)"

# Remake
re : fclean all

leak :
	echo "$(BLUE)	Checking leaks ...	$(NC)"
	valgrind --leak-check=full --show-leak-kinds=all --trace-children=no --track-fds=no ./$(NAME) $(ARGS)

.PHONY:
	clean fclean re test all leak bonus deps 
