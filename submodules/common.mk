# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    common.mk                                          :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/02/12 07:14:16 by kiroussa          #+#    #+#              #
#    Updated: 2024/07/10 21:47:05 by kiroussa         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#idiot proof
ifndef NAME
	_ = $(error NAME is not set)
endif
ifndef SRC
	_ = $(error SRC is not set)
endif
ifndef MODULE_CACHE
	_ = $(error MODULE_CACHE is not set)
endif
ifndef CACHE_DIR
	_ = $(error CACHE_DIR is not set)
endif
ifndef SRC_DIR
	_ = $(error SRC_DIR is not set)
endif
ifndef OBJ_DIR
	_ = $(error OBJ_DIR is not set)
endif
ifndef D_DIR
	_ = $(error D_DIR is not set)
endif

ifeq ($(EXTRA_DEBUG), 1)
ifeq ($(IS_EXEC), 1)
	LDFLAGS		+=	-v -Wl,--verbose
endif
endif

SRC				:=	$(addprefix $(SRC_DIR)/, $(SRC))
OBJ				:=	$(SRC:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)
D_FILES			:=	$(SRC:$(SRC_DIR)/%.c=$(D_DIR)/%.d)

DISABLE_CLEAN	:=	0

PRINTF			:=	printf
ifeq ($(FREEZE_LOGS), 1)
PRINTF			:=	:
endif

all: $(LIBS)
ifeq ($(HYPERTHREADING), 1)
	@$(MAKE) $(OUTPUT) -j
else
	@$(MAKE) $(OUTPUT)
endif

-include $(D_FILES)

$(OUTPUT): $(SELF_DEP) $(LIBS) $(OBJ)
	@$(PRINTF) "$(SPACING)"
ifeq ($(IS_EXEC),1)
	@#don't ask me why but we need 2 spaces here, unicode is a nice thing
	@$(PRINTF) "🖥️  Linking executable '$(NAME)'\n"
else
	@$(PRINTF) "💼 Linking library 'lib$(NAME).so'\n"
endif
ifeq ($(EXTRA_DEBUG), 1)
	$(LD) $(OBJ) -o $(OUTPUT) $(LDFLAGS)
else
	@$(LD) $(OBJ) -o $(OUTPUT) $(LDFLAGS)  
endif

$(LIBS):
	$(eval NUMBER_OF_SLASHES := $(shell expr $(shell echo $(shell pwd) | grep -o "/" | \wc -l) + 1))
	$(eval CURRENT_LIB := $(shell echo $@ | cut -d'/' -f$(NUMBER_OF_SLASHES)))
	@$(PRINTF) "$(SPACING_TARGET)📑 Making '$(CURRENT_LIB)'\n"
ifeq ($(EXTRA_DEBUG), 1)
	$(MAKE) -C ../$(CURRENT_LIB) CACHE_DIR="$(CACHE_DIR)" DEPTH="$(shell expr $(DEPTH) + 1)"
else
	@$(MAKE) -C ../$(CURRENT_LIB) CACHE_DIR="$(CACHE_DIR)" DEPTH="$(shell expr $(DEPTH) + 1)"
endif

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	@mkdir -p $(dir $(D_DIR)/$*)
	@$(PRINTF) "$(SPACING_TARGET)🔨 $<\n"
ifeq ($(EXTRA_DEBUG), 1)
	$(CC) $(DFLAGS) $(CFLAGS) -c "$(shell pwd)/$<" -o $@
else
	@$(CC) $(DFLAGS) $(CFLAGS) -c "$(shell pwd)/$<" -o $@
endif
	@echo "$(shell pwd)/$<:" >> $(D_DIR)/$*.tmp.d
	@# dumb fixes, see https://make.mad-scientist.net/papers/advanced-auto-dependency-generation/
	@mv -f $(D_DIR)/$*.tmp.d $(D_DIR)/$*.d
	@touch $@

$(SELF_DEP):
	@mkdir -p $(dir $(SELF_DEP))
	@echo "$(OUTPUT): $(OBJ) $(LIBS)" > $(SELF_DEP)

clean_deps:
	@if [ "$(DISABLE_CLEAN)" = "0" ]; then \
		$(PRINTF) "$(SPACING)Cleaning dependencies\n"; \
		for dep in $(DEPS); do \
			$(MAKE) -C "../$$dep" clean CACHE_DIR="$(CACHE_DIR)" DEPTH="$(shell expr $(DEPTH) + 1)"; \
		done; \
	fi

clean: clean_deps
	@$(PRINTF) "$(SPACING)"
	rm -rf $(MODULE_CACHE)
	
fclean_deps:
	@$(PRINTF) "$(SPACING)(F)Cleaning dependencies\n"
	@for dep in $(DEPS); do \
		$(MAKE) -C "../$$dep" fclean CACHE_DIR="$(CACHE_DIR)" DEPTH="$(shell expr $(DEPTH) + 1)"; \
	done

__disable_clean:
	$(eval DISABLE_CLEAN := 1)

fclean: __disable_clean fclean_deps clean
	@$(PRINTF) "$(SPACING)\033[31m$(OUTPUT) cleaned\033[0m\n"
	@$(PRINTF) "$(SPACING)"
	rm -f $(OUTPUT)

re: fclean all

print_%:
	@echo "$($*)"

printdepfiles:
	@$(PRINTF) "$(D_FILES) $(SELF_DEP)\n"

.PHONY: all clean fclean re print_% clean_deps fclean_deps __disable_clean printdepfiles
