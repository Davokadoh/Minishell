ifndef SETTINGS_MK # Stay safe
 SETTINGS_MK = 1

NAME = minishell
SRC = $(SRC_DIR)main.c \
      $(SRC_DIR)prompt.c \
      $(SRC_DIR)lexer.c \
      $(SRC_DIR)expander.c

LIBFT_DIR = libft/
LIBFT = $(LIBFT_DIR)/libft.a

CC = gcc
CFLAGS += -Wall -Wextra -Werror
CFLAGS = -I $(LIBFT_DIR)/include
LDFLAGS += $(LIBFT)
LDFLAGS += -lreadline

endif
