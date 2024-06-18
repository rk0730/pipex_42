CC = cc
CFLAGS = -Wall -Wextra -Werror

LIBFT_DIR = libft
LIBFT = $(LIBFT_DIR)/libft.a

FTPRINTF_DIR = ft_printf
FTPRINTF = $(FTPRINTF_DIR)/libftprintf.a

SRCDIR = src
SRCS = $(SRCDIR)/ft_main.c \
	$(SRCDIR)/ft_check_arg.c \
	$(SRCDIR)/ft_utils.c \
	$(SRCDIR)/ft_exe_cmd.c \
	$(SRCDIR)/ft_pipe.c

GNL_DIR = $(SRCDIR)/get_next_line
SRCS += $(GNL_DIR)/get_next_line.c \
	$(GNL_DIR)/get_next_line_utils.c

INCLUDES = -I. -I$(LIBFT_DIR) -I$(FTPRINTF_DIR) -I$(GNL_DIR)

NAME = pipex

all: $(NAME)

bonus: $(NAME)

$(NAME): $(SRCS) $(LIBFT) $(FTPRINTF)
	$(CC) $(CFLAGS) $(INCLUDES) -o $@ $^

$(LIBFT):
	make -C $(LIBFT_DIR) all

$(FTPRINTF):
	make -C $(FTPRINTF_DIR) all

clean:
	make -C $(LIBFT_DIR) clean
	make -C $(FTPRINTF_DIR) clean

fclean: clean
	rm -f $(NAME)
	make -C $(LIBFT_DIR) fclean
	make -C $(FTPRINTF_DIR) fclean

re: fclean all

.PHONY: all bonus clean fclean re
