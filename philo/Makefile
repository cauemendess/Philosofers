.DEFAULT_GOAL: all
.DELETE_ON_ERROR:
.PHONY: all clean fclean re
HIDE = @

CC      = gcc
CFLAGS  = -Wall -Werror -Wextra -pthread -Iinclude
RM      = rm -f

NAME    = philo

SRCDIR  = src/
SRC     = main.c getters.c utils.c time.c validate.c
SRCS    = $(addprefix $(SRCDIR), $(SRC))
OBJDIR  = bin/
OBJS    = $(addprefix $(OBJDIR), $(SRC:.c=.o))

INCDIR  = include/
INC     = $(INCDIR)include.h

all: $(OBJDIR) $(NAME)

$(NAME): $(OBJS)
	$(HIDE)$(CC) $(CFLAGS) -o $@ $^

$(OBJDIR):
	$(HIDE)mkdir -p $@

$(OBJDIR)%.o: $(SRCDIR)%.c | $(OBJDIR)
	$(HIDE)$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(HIDE)$(RM) $(OBJS)

fclean: clean
	$(HIDE)$(RM) $(NAME)
	$(HIDE)$(RM) -r $(OBJDIR)

re: fclean all


