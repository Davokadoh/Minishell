NAME = minishell

LIBS        :=	ft readline
LIBS_TARGET :=	lib/libft/libft.a

INCS        :=	include\
				lib/libft/include

UNAME= $(shell uname -s)
ifeq ($(UNAME), Darwin)
INCS		+=	$(HOME)/.brew/Cellar/readline/8.1.2/include
LDFLAGS		+=	-L$(HOME)/.brew/Cellar/readline/8.1.2/lib
#else ifeq ($(UNAME), Linux)
#LDFLAGS		+=	-lreadline
endif

SRC_DIR     :=	src
SRCS 		:=	$(SRC_DIR)/main.c\
				$(SRC_DIR)/prompt.c\
				$(SRC_DIR)/lexer.c\
				$(SRC_DIR)/expander.c

BUILD_DIR   :=	.build
OBJS        :=	$(SRCS:$(SRC_DIR)/%.c=$(BUILD_DIR)/%.o)
DEPS        :=	$(OBJS:.o=.d)

CC          :=	gcc
CFLAGS      :=	-Wall -Wextra -Werror
CPPFLAGS    :=	$(addprefix -I,$(INCS)) -MMD -MP
LDFLAGS     +=	$(addprefix -L,$(dir $(LIBS_TARGET)))
LDLIBS      :=	$(addprefix -l,$(LIBS))

RM          := rm
MAKEFLAGS   += --silent --no-print-directory

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

# USE TPUTS INSTEAD!!!
# COLORS
R=$$(tput setaf 1)
G=$$(tput setaf 2)
Y=$$(tput setaf 3)
B=$$(tput setaf 4)
W=$$(tput setaf 7)

all: $(NAME)
	@echo $(G)
	@cat $(NAME).asciiart
	@echo $(W)

$(NAME): $(OBJS) $(LIBS_TARGET)
	$(CC) $(LDFLAGS) $(OBJS) $(LDLIBS) -o $(NAME)
	$(info CREATED $(NAME))

$(LIBS_TARGET):
	$(MAKE) -C $(@D)

$(BUILD_DIR):
	mkdir -p $@

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c | $(BUILD_DIR)
	$(CC) $(CFLAGS) $(CPPFLAGS) -c -o $@ $<
	$(info CREATED $@)

-include $(DEPS)

clean:
	for f in $(dir $(LIBS_TARGET)); do $(MAKE) -C $$f clean; done
	$(RM) -r $(BUILD_DIR)

fclean: clean
	for f in $(dir $(LIBS_TARGET)); do $(MAKE) -C $$f fclean; done
	$(RM) $(NAME)

re:
	$(MAKE) fclean
	$(MAKE) all

asan:
	CFLAGS += -g3 -fsanitize=address -fno-omit-frame-pointer
	LDFLAGS += -fsanitize=address
	all

debug:
	CFLAGS += -g3
	all
