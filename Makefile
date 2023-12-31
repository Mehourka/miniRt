
# Compiler and flags
CC		=	gcc
# CFLAGS	=	-Wall -Werror -Wextra
# CFLAGS +=	-Wunreachable-code -Ofast
RM		=	rm

#------------------------------------------------------------------------------#
#                                VARIABLES                                     #
#------------------------------------------------------------------------------#

ARGS	=	""
NAME	=	main

# Colors
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



# Sources

SRCS	:=	main.c				\
			vec_operations.c	\

B_SRCS	:=	$(SRCS:%=bonus_%)


# Objects
OBJDIR	=	obj/
OBJS		:=	$(SRCS:%.c=$(OBJDIR)%.o)
SRCS		:=	$(SRCS:%.c=$(SRCDIR)%.c)
B_OBJS	:=	$(B_SRCS:%.c=$(OBJDIR)%.o)
B_SRCS		:=	$(B_SRCS:%=$(BONDIR)%)
DEPS		:=	$(OBJS:%.o=%.d)


#------------------------------------------------------------------------------#
#                                TARGETS                                       #
#------------------------------------------------------------------------------#

all : $(NAME)

run : $(NAME)
	./$(NAME)

# Compile program
$(NAME) : $(LIBMLX) $(LIBFT) $(OBJS)
	@echo "$(GREEN)	Compiling $@ ... $(NC)"
	$(CC) $(CFLAGS) $(OBJS) $(LIBS) -o $@ -I. $(INCLUDES)

# Compile objects
$(OBJDIR)%.o : $(SRCDIR)%.c
	@mkdir -p $(OBJDIR);
	$(CC) -c $(CFLAGS) -MMD -MP $< -o $@ $(INCLUDES)

-include $(DEPS)

# Compile libft
$(LIBFT):
	@ $(MAKE) -C $(LIBDIR)/libft -s

#Compiling libmlx
$(LIBMLX):
	cmake $(MLXDIR) -B $(MLXDIR)/build && make -C $(MLXDIR)/build -j4 -s


# Compile Bonus
bonus : $(LIBMLX) $(LIBFT) $(BONUS_OBJS)
	@echo "$(GREEN)	Compiling $@ ... $(NC)"
	$(CC) $(CFLAGS) $(BONUS_OBJS) $(LIBS) -o $@ -I/bonus_src/ $(INCLUDES)

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
	clean fclean re test all leak bonus