SRC_DIR = src/
OBJ_DIR = obj/
INC_DIR = inc/
DEP_DIR = dep/

CFLAGS += -I $(INC_DIR)

include settings.mk

OBJ = $(SRC:$(SRC_DIR)%.c=$(OBJ_DIR)%.o)
DEP = $(SRC:$(SRC_DIR)%.c=$(DEP_DIR)%.d)

RM = rm -rf

.PHONY: all clean fclean re asan debug

# USE TPUTS INSTEAD!!!
# COLORS
Y = "\033[33m"
R = "\033[31m"
G = "\033[32m"
B = "\033[34m"
X = "\033[0m"
UP = "\033[A"
CUT = "\033[K"

all: $(NAME)
	@echo $(G)
	@cat $(NAME).asciiart
	@echo $(X)

$(NAME): $(OBJ) $(LIBFT)
	$(CC) -o $@ $(LDFLAGS) $^

$(OBJ_DIR):
	@mkdir -p $@

$(OBJ): | $(OBJ_DIR)

$(OBJ): $(OBJ_DIR)%.o: $(SRC_DIR)%.c
	$(CC) $(CFLAGS) -c $< -o $@ $(DEP)

$(DEP_DIR):
	@mkdir -p $@

$(DEP): | $(DEP_DIR)

DEP = -MMD -MF $(@:.o=.d)
#$(DEP): $(DEP_DIR)%.d: $(SRC_DIR)%.c | $(DEP_DIR)
#	$(CC) $(CFLAGS) -MM -MF $@ -MT "$(OBJ) $@" $<

cleanobj:
	$(RM) $(OBJ_DIR)

cleandep:
	$(RM) $(DEP_DIR)

clean: cleanobj cleandep

fclean: clean
	$(RM) $(NAME)

re: fclean all

asan:
	CFLAGS += -g3 -fsanitize=address -fno-omit-frame-pointer
	LDFLAGS += -fsanitize=address
	all

debug:
	CFLAGS += -g3
	all

-include $(DEP)

include custom_rules.mk
