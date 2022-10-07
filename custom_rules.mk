ifndef CUSTOM_RULES_MK # Stay safe
 CUSTOM_RULES_MK = 1

$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR)

endif
