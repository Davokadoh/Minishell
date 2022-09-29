NAME			=	minishell

CC				=	clang
CFLAGS			=	-Wall -Werror -Wextra
CPPFLAGS		=	-I include -I $(LIBFT_DIR)/include
LDFLAGS			=	-lreadline

LIBFT_DIR		=	libft
LIBFT			=	$(LIBFT_DIR)/libft.a
LDFLAGS			+=	$(LIBFT)

SRCS_DIR		=	src
OBJS_DIR		=	obj
OBJS 			=	$(patsubst %.c, $(OBJS_DIR)/%.o, $(SRCS))
SRCS			=	main.c

UNAME= $(shell uname -s)
ifeq ($(UNAME), Darwin)
CPPFLAGS += -I $(HOME)/.brew/Cellar/readline/8.1.2/include
LDFLAGS += -L$(HOME)/.brew/Cellar/readline/8.1.2/lib
endif

all: $(NAME)

clean:
	$(MAKE) -C $(LIBFT_DIR) clean
	rm -rf $(OBJS_DIR)

fclean: clean
	$(MAKE) -C $(LIBFT_DIR) fclean
	rm -rf $(NAME)

re:	fclean all

$(OBJS_DIR):
	@mkdir -p $(dir $(OBJS))

$(OBJS_DIR)/%.o: $(SRCS_DIR)/%.c | $(OBJS_DIR)
	$(CC) -c $(CFLAGS) $(CPPFLAGS) -o $@ $^

$(NAME): $(LIBFT) $(OBJS)
	$(CC) -o $(NAME) $(OBJS) $(LDFLAGS)

$(LIBFT):
	$(MAKE) -sC $(LIBFT_DIR) bonus

asan: CFLAGS += -g3 -fsanitize=address -fno-omit-frame-pointer
asan: LDFLAGS += -fsanitize=address
asan: all

debug: CFLAGS += -g3
debug: all

.PHONY: all fclean clean re debug valgrind

