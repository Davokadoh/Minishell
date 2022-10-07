ifndef SETTINGS_MK # Stay safe
 SETTINGS_MK = 1

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
#LDFLAGS		=	-lreadline
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

endif
CFLAGS = -I $(LIBFT_DIR)include
LDFLAGS += -lreadline

