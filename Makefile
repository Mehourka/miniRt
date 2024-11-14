CC	= c++
CFLAGS = -Wall -Werror -Wextra -std=c++98 -pedantic-errors

NAME := $(notdir $(shell pwd))
SRCS := $(wildcard *.cpp)

OBJDIR	:= obj/
OBJS	:= $(SRCS:%.cpp=$(OBJDIR)%.o)



all: $(NAME)

run: re
	@echo Running ./$(NAME) ... "\n"
	@./$(NAME)

$(NAME): $(OBJS)
	@echo Compiling ./$(NAME) ...
	$(CC) $(CFLAGS) -o $@ $(OBJS)
	@echo "Done !\n"

$(OBJDIR)%.o: %.cpp
	@mkdir -p $(@D);
	@$(CC) -c $(CFLAGS) -MMD -MP $< -o $@

-include $(DEPS)

clean:
	@echo Deleting Object files
	@rm -f $(OBJS)

fclean: clean
	@echo Deleting ./$(NAME)
	@rm -rf $(NAME)

re: fclean $(NAME)
