# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jleroux <marvin@42lausanne.ch>             +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/10/13 16:15:54 by jleroux           #+#    #+#              #
#    Updated: 2022/11/10 10:20:15 by jleroux          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


.PHONY:		all clean fclean re bonus

NAME = libft.a

INCS        :=	include

UNAME= $(shell uname -s)
ifeq ($(UNAME), Darwin)
else ifeq ($(UNAME), Linux)
endif

SRC_DIR     :=	src
SRC			:=	ft_append.c\
				ft_realloc.c\
				ft_atoi.c\
				ft_atol.c\
				ft_bzero.c\
				ft_calloc.c\
				ft_isalnum.c\
				ft_isalpha.c\
				ft_isascii.c\
				ft_isdigit.c\
				ft_isprint.c\
				ft_memchr.c\
				ft_memcmp.c\
				ft_memcpy.c\
				ft_memmove.c\
				ft_memset.c\
				ft_strchr.c\
				ft_strdup.c\
				ft_strlcat.c\
				ft_strlcpy.c\
				ft_strlen.c\
				ft_strncmp.c\
				ft_strnstr.c\
				ft_strrchr.c\
				ft_tolower.c\
				ft_toupper.c\
				ft_substr.c\
				ft_strjoin.c\
				ft_strtrim.c\
				ft_split.c\
				ft_itoa.c\
				ft_strmapi.c\
				ft_striteri.c\
				ft_putchar_fd.c\
				ft_putstr_fd.c\
				ft_putendl_fd.c\
				ft_putendl.c\
				ft_putnbr_fd.c\
				ft_free.c\
				ft_free_tab.c\
				ft_str_array_size.c\
				ft_push_str.c
SRC			:=	$(addprefix $(SRC_DIR)/,$(SRC))

BONUS_DIR	:=	bonus
BONUS_SRC	:=	ft_lstnew.c\
				ft_lstadd_front.c\
				ft_lstsize.c\
				ft_lstlast.c\
				ft_lstadd_back.c\
				ft_lstdelone.c\
				ft_lstclear.c\
				ft_lstiter.c\
				ft_lstmap.c
BONUS_SCR	:=	$(addprefix $(BONUS_DIR)/,$(BONUS_SRC))

BUILD_DIR	:=	.build
OBJS		:=	$(SRC:$(SRC_DIR)/%.c=$(BUILD_DIR)/%.o)
BONUS_OBJS	:=	$(BONUS_SRC:$(BONUS_DIR)/%.c=$(BUILD_DIR)/%.o)
DEPS        :=	$(OBJS:.o=.d)
BONUS_DEPS	:=	$(BONUS_OBJS:.o=.d)

CC          :=	gcc
CFLAGS      :=	-Wall -Wextra -Werror
CPPFLAGS    :=	$(addprefix -I,$(INCS)) -MMD -MP

AR			:=	ar
ARFLAGS		:=	rcs

RM			:= rm -rf
MAKEFLAGS	+= --no-print-directory #--silent

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

$(NAME): $(OBJS)
	@$(AR) $(ARFLAGS) $(NAME) $(OBJS)
	@echo $(G)
	@cat $(NAME).asciiart
	@echo $(W)

bonus: $(OBJS) $(BONUS_OBJS) $(LIBS_TARGET)
	@$(AR) $(ARFLAGS) $(NAME) $(OBJS)

$(BUILD_DIR):
	@mkdir -p $@

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c | $(BUILD_DIR)
	@$(CC) $(CFLAGS) $(CPPFLAGS) -c -o $@ $<

-include $(DEPS)

clean:
	@$(RM) $(BUILD_DIR)

fclean: clean
	@$(RM) $(NAME)

re:
	@$(MAKE) fclean
	@$(MAKE) all

asan: CFLAGS += -g3 -fsanitize=address -fno-omit-frame-pointer
asan: all

debug: CFLAGS += -g3
debug: all
