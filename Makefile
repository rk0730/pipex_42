CC = cc
AR = ar rc
CFLAGS = -Wall -Wextra -Werror

SRCDIR = src

SRCS = $(SRCDIR)/ft_main.c \
	$(SRCDIR)/ft_utils.c \
	$(SRCDIR)/ft_exe_cmd.c \
	$(SRCDIR)/ft_pipe_sub.c \
	$(SRCDIR)/ft_recursive.c \

OBJS = $(SRCS:.c=.o)

LIBFT_DIR = libft
LIBFT = libft.a

FTPRINTF_DIR = ft_printf
FTPRINTF = libftprintf.a

NAME = pipex

# BONUS_DIR = $(SRCDIR)/bonus
# BONUS_SRCS = $(BONUS_DIR)/ft_main.c

# GNL_DIR = $(BONUS_DIR)/get_next_line
# BONUS_SRCS += $(GNL_DIR)/get_next_line.c \
# 	$(GNL_DIR)/get_next_line_utils.c

# BONUS_OBJS = $(BONUS_SRCS:.c=.o)

# BONUS_NAME = checker

all: $(NAME)

$(NAME): $(OBJS) $(LIBFT) $(FTPRINTF)
	$(CC) $(CFLAGS) -I. -o $(NAME) $(OBJS) $(LIBFT_DIR)/$(LIBFT) $(FTPRINTF_DIR)/$(FTPRINTF)

# bonus: $(BONUS_NAME)

# $(BONUS_NAME): $(BONUS_OBJS) $(LIST_OBJS) $(LIBFT) $(FTPRINTF)
# 	$(CC) $(CFLAGS) -I. -o $(BONUS_NAME) $(BONUS_OBJS) $(LIST_OBJS) $(LIBFT_DIR)/$(LIBFT) $(FTPRINTF_DIR)/$(FTPRINTF)

$(LIBFT):
	make -C $(LIBFT_DIR) all

$(FTPRINTF):
	make -C $(FTPRINTF_DIR) all

%.o: %.c
	$(CC) $(CFLAGS) -I. -c $< -o $@

clean:
	rm -f $(OBJS)
	make -C $(LIBFT_DIR) clean
	make -C $(FTPRINTF_DIR) clean

fclean: clean
	rm -f $(NAME)
	make -C $(LIBFT_DIR) fclean
	make -C $(FTPRINTF_DIR) fclean

re: fclean all

.PHONY: all bonus clean fclean re
