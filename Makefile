include settings.mk

#------------------------------------------------#
#   RECIPES                                      #
#------------------------------------------------#
# all       default goal
# $(NAME)   link .o -> archive
# $(LIBS)   build libraries
# %.o       compilation .c -> .o
# clean     remove .o
# fclean    remove .o + binary
# re        remake default goal
# run       run the program
# info      print the default goal recipe

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
	$(RM) $(OBJS) $(DEPS)

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

include custom_rules.mk
