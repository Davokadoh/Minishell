
# VARIABLES & FLAGS
NAME		=	minishell
CC			=	gcc
CFLAGS		=	-Wall -Werror -Wextra
CPPFLAGS	=	-I include -I $(LIBFT_DIR)/include
LDFLAGS		=	-lreadline

LIBFT_DIR	=	libft
LIBFT		=	$(LIBFT_DIR)/libft.a
LDFLAGS		+=	$(LIBFT)

SRCS_DIR	=	src
OBJS_DIR	=	obj
OBJS 		=	$(patsubst %.c, $(OBJS_DIR)/%.o, $(SRCS))
SRCS		=	main.c \
				prompt.c \
				lexer.c \
				expander.c


UNAME= $(shell uname -s)
ifeq ($(UNAME), Darwin)
CPPFLAGS	+=	-I $(HOME)/.brew/Cellar/readline/8.1.2/include
LDFLAGS		+=	-L$(HOME)/.brew/Cellar/readline/8.1.2/lib
#else ifeq ($(UNAME), Linux)
#LDFLAGS		=	-lreadline
endif

all: $(NAME)

$(NAME): $(LIBFT) $(OBJS)
	$(CC) -o $(NAME) $(OBJS) $(LDFLAGS)

$(OBJS_DIR):
	@mkdir -p $(dir $(OBJS))

# COLORS
# USE TPUTS INSTEAD!!! 
Y = "\033[33m"
R = "\033[31m"
G = "\033[32m"
B = "\033[34m"
X = "\033[0m"
UP = "\033[A"
CUT = "\033[K"

$(OBJS_DIR)/%.o: $(SRCS_DIR)/%.c | $(OBJS_DIR)
	@echo $(Y)Compiling [$@]...$(X)
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) $(CPPFLAGS) -o $@ -c $<
	@printf $(UP)$(CUT)
	@echo $(G)Finished [$@]$(X)
	@printf $(UP)$(CUT)


$(LIBFT):
	$(MAKE) -sC $(LIBFT_DIR) #bonus

clean:
	$(MAKE) -C $(LIBFT_DIR) clean
	rm -rf $(OBJS_DIR)

fclean: clean
	$(MAKE) -C $(LIBFT_DIR) fclean
	rm -rf $(NAME)

re:	fclean all


asan:
	CFLAGS += -g3 -fsanitize=address -fno-omit-frame-pointer
	LDFLAGS += -fsanitize=address
	all

debug:
	CFLAGS += -g3
	all

.PHONY: all fclean clean re debug valgrind

