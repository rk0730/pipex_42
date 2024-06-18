CC = cc
AR = ar rc
CFLAGS = -Wall -Wextra -Werror
INCLUDES = -I. -I$(LIBFT_DIR) -I$(FTPRINTF_DIR) -I$(GNL_DIR)

LIBFT_DIR = libft
LIBFT = libft.a

FTPRINTF_DIR = ft_printf
FTPRINTF = libftprintf.a

SRCDIR = src

SRCS = $(SRCDIR)/ft_main.c \
	$(SRCDIR)/ft_check_arg.c \
	$(SRCDIR)/ft_utils.c \
	$(SRCDIR)/ft_exe_cmd.c \
	$(SRCDIR)/ft_pipe.c

GNL_DIR = $(SRCDIR)/get_next_line
SRCS += $(GNL_DIR)/get_next_line.c \
	$(GNL_DIR)/get_next_line_utils.c

NAME = pipex

all: $(NAME)

bonus: $(NAME)

$(NAME): $(SRCS) $(LIBFT_DIR)/$(LIBFT) $(FTPRINTF_DIR)/$(FTPRINTF)
	$(CC) $(CFLAGS) $(INCLUDES) -o $@ $^

$(LIBFT_DIR)/$(LIBFT):
	make -C $(LIBFT_DIR) all

$(FTPRINTF_DIR)/$(FTPRINTF):
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
