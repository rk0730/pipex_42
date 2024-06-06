CC = cc
AR = ar rc
CFLAGS = -Wall -Wextra -Werror

SRCDIR = .

SRCS = $(SRCDIR)/ft_printf.c \
	$(SRCDIR)/ft_convert_cs.c \
	$(SRCDIR)/ft_convert_d.c \
	$(SRCDIR)/ft_convert_u.c \
	$(SRCDIR)/ft_convert_p.c \
	$(SRCDIR)/ft_convert_xX.c

OBJS = $(SRCS:.c=.o)

TEST_SRC = main.c

NAME = libftprintf.a

all: $(NAME)

$(NAME): $(OBJS)
	$(AR) $(NAME) $(OBJS)

%.o: %.c
	$(CC) $(CFLAGS) -I. -c $< -o $@

test: ft_printf.txt printf.txt
	diff ft_printf.txt printf.txt

%.txt: %
	./$< > $@

ft_printf: $(NAME) $(TEST_SRC)
	$(CC) $(CFLAGS) -I. $^ -D FT -o $@

printf: $(TEST_SRC)
	$(CC) $(CFLAGS) -I. $^ -o $@

clean:
	rm -f ft_printf.txt printf.txt
	rm -f $(OBJS)

fclean: clean
	rm -f printf ft_printf
	rm -f $(NAME)

re: fclean all

.PHONY: all test clean fclean re
