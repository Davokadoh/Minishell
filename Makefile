NAME = minishell

LIBS        :=	ft readline
LIBS_TARGET :=	lib/libft/libft.a

INCS        :=	include\
				lib/libft/include

UNAME= $(shell uname -s)
ifeq ($(UNAME), Darwin)
#INCS		+=	/usr/local/Cellar/readline/8.2.1/include
#LDFLAGS		+=	-L/usr/local/Cellar/readline/8.2.1/lib
INCS		+=	$(HOME)/.brew/Cellar/readline/8.2.1/include
LDFLAGS		+=	-L$(HOME)/.brew/Cellar/readline/8.2.1/lib
#else ifeq ($(UNAME), Linux)
endif

SRC_DIR		:=	src
SRCS		:=	$(SRC_DIR)/main.c \
				$(SRC_DIR)/signals.c \
				$(SRC_DIR)/prompt.c \
				$(SRC_DIR)/quotes.c \
				$(SRC_DIR)/lexer.c \
				$(SRC_DIR)/expander.c \
				$(SRC_DIR)/parser.c \
				$(SRC_DIR)/executor.c \
				$(SRC_DIR)/child.c \
				$(SRC_DIR)/io.c \
				$(SRC_DIR)/builtins.c \
				$(SRC_DIR)/ft_echo.c \
				$(SRC_DIR)/ft_env.c \
				$(SRC_DIR)/ft_cd.c \
				$(SRC_DIR)/ft_exit.c \
				$(SRC_DIR)/ft_pwd.c \
				$(SRC_DIR)/ft_export.c \
				$(SRC_DIR)/ft_unset.c \
				$(SRC_DIR)/utils.c \
				$(SRC_DIR)/exp_utils.c \

BUILD_DIR   :=	.build
OBJS        :=	$(SRCS:$(SRC_DIR)/%.c=$(BUILD_DIR)/%.o)
DEPS        :=	$(OBJS:.o=.d)

CC          :=	gcc
CFLAGS      :=	-Wall -Wextra -Werror
CPPFLAGS    :=	$(addprefix -I,$(INCS)) -MMD -MP
LDFLAGS     +=	$(addprefix -L,$(dir $(LIBS_TARGET)))
LDLIBS      :=	$(addprefix -l,$(LIBS))

RM			:= rm -rf
MAKEFLAGS   += --no-print-directory #--silent

#------------------------------------------------#
#   RECIPES                                      #
#------------------------------------------------#
# all		default goal
# $(NAME)	link .o -> archive
# $(LIBS)	build libraries
# %.o		compilation .c -> .o
# clean		remove .o
# fclean	remove .o + binary
# re		remake default goal
# asan		run with fsanitize
# debug		compile with debug info

.PHONY: all clean fclean re asan debug

R=$$(tput setaf 1)
G=$$(tput setaf 2)
Y=$$(tput setaf 3)
B=$$(tput setaf 4)
W=$$(tput setaf 7)

all: $(NAME)

$(NAME): $(OBJS) $(LIBS_TARGET)
	@$(CC) -o $(NAME) $(CPPFLAGS) $(OBJS) $(LDLIBS) $(LDFLAGS)
	@echo $(G)
	@cat $(NAME).asciiart
	@echo $(W)

$(LIBS_TARGET):
ifeq ($(MAKECMDGOALS),debug)
	@$(MAKE) debug -C $(@D)
else
	@$(MAKE) -C $(@D)
endif

$(BUILD_DIR):
	@mkdir -p $@

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c | $(BUILD_DIR)
	@$(CC) $(CFLAGS) $(CPPFLAGS) -c -o $@ $<

-include $(DEPS)

clean:
	@for f in $(dir $(LIBS_TARGET)); do $(MAKE) -C $$f clean; done
	@$(RM) $(BUILD_DIR)

fclean: clean
	@for f in $(dir $(LIBS_TARGET)); do $(MAKE) -C $$f fclean; done
	@$(RM) $(NAME)

re:
	@$(MAKE) fclean
	@$(MAKE) all

asan: CFLAGS += -g3 -fsanitize=address -fno-omit-frame-pointer
asan: LDFLAGS += -fsanitize=address
asan: all

debug: CFLAGS += -g3 -D DEBUG=1
debug: all
