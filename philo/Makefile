.DEFAULT_GOAL: all
.DELETE_ON_ERROR:
.PHONY: all bonus clean fclean re
HIDE = @

CC      = gcc
CFLAGS  = -Wall -Werror -Wextra -pthread  -I. -I./$(INCDIR) -I../libft
RM      = rm -f
LIBFT   = ../libft/libft.a

NAME    = philo

SRCDIR  = src/
SRCS    = $(wildcard $(SRCDIR)*.c)
OBJDIR  = bin/
OBJS    = $(patsubst $(SRCDIR)%.c,$(OBJDIR)%.o,$(SRCS))

INCDIR  = include/
INC     = $(wildcard $(INCDIR)*.h)

all: $(LIBFT) $(NAME)

$(NAME): $(OBJS)
	$(HIDE)$(CC) $(CFLAGS) -o $@ $^ $(LIBFT)

$(LIBFT):
	$(HIDE)make -C ../libft

$(OBJDIR)%.o : $(SRCDIR)%.c $(INC) | $(OBJDIR)
	$(HIDE)$(CC) $(CFLAGS) -c $< -o $@

$(OBJDIR):
	$(HIDE)mkdir -p $@

clean:
	$(HIDE)$(RM) $(OBJS)
	$(HIDE)make -C ../libft clean

fclean: clean
	$(HIDE)$(RM) $(NAME)
	$(HIDE)$(RM) -r $(OBJDIR)
	$(HIDE)make -C ../libft fclean

re: fclean all

