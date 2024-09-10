# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ebouchet <ebouchet@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/08/06 21:19:50 by kiroussa          #+#    #+#              #
#    Updated: 2024/09/09 01:51:58 by kiroussa         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CONFIG_DIR			:=	config
CONFIG_MK			:=	$(CONFIG_DIR)/config.mk

-include $(CONFIG_MK)
ifeq ($(MAKE_TRACE), 1)
$(info Included $(CONFIG_MK))
endif

CWD					?=	$(shell pwd)
NAME				:=	minishell

ifdef OVERRIDE_NAME
NAME				:=	$(OVERRIDE_NAME)
endif
ifdef SUFFIX
NAME				:=	$(NAME)$(SUFFIX)
endif
ifeq ($(MAKE_TRACE), 1)
$(info NAME: $(NAME))
endif

NO_READLINE			?=	0
ifeq ($(NO_READLINE), 0)
VSUPP_ARG			:=	--suppressions=$(CWD)/config/valgrind.vsupp
endif

MAKE				:=	make --no-print-directory --debug=none


CACHE_DIR_NAME		:=	.cache
CACHE_DIR			:=	$(addprefix $(shell pwd)/, $(CACHE_DIR_NAME))

COMP_MODE			?=	MANDATORY_MSH

LAST_COMP			:=	$(CONFIG_DIR)/.last_comp
_LAST_COMP_DATA		:=	$(shell cat $(LAST_COMP) 2>/dev/null)
_LAST_COMP			:=	$(word 1, $(_LAST_COMP_DATA))
ifneq ($(_LAST_COMP), $(COMP_MODE))
ifeq ($(BUILD), 1)
REBUILD				:=	1
ifeq ($(_LAST_COMP), )
REBUILD				:=	0
endif
ifeq ($(MAKE_TRACE), 1)
$(info Setting new compilation mode: $(COMP_MODE))
endif
_					:=	$(shell echo "$(COMP_MODE)" > $(LAST_COMP))
_					:=	$(shell rm -rf $(CACHE_DIR) $(NAME))
endif
endif

PRINTF				?=	printf
ifeq ($(FREEZE_LOGS), 1)
PRINTF				:=	:
else
-include header.mk
endif


POSSIBLE_NAMES		:=	minishell minishell_bonus 42sh 42sh_bonus

SUBMODULES			:=	submodules

LIBFT_DIR			:=	$(CWD)/third-party/libft
LIBFT				:=	$(LIBFT_DIR)/build/output/libft.so

FEATURES_H			:=	$(SUBMODULES)/shared/include/msh/features.h
FEATURES_H_ACTUAL	:=	$(CONFIG_DIR)/features.h
FEATURES_H_GEN		:=	$(FEATURES_H_ACTUAL).gen.sh

MAIN_MODULE			:=	cli
ifeq ($(MAKE_TRACE), 1)
$(info MAIN_MODULE: $(MAIN_MODULE))
endif
MAIN_MODULE_OUT		:=	$(shell $(MAKE) -C $(SUBMODULES)/$(MAIN_MODULE) print_OUTPUT)
CLI_EXEC			:=	$(CWD)/$(MAIN_MODULE_OUT)

ifeq ($(MAKE_TRACE), 1)
$(info Fetching dependency files...)
endif

D_FILES				?=	$(shell find $(CACHE_DIR) -name "*.d" 2>/dev/null)

ifeq ($(MAKE_TRACE), 1)
$(info Found $(words $(D_FILES)) d-files)
endif

RM					:=	rm -rf

VG_RUN				?=
_DISABLE_CLEAN_LOG	:= 0

TEST_TARGET ?= 42bonus
ifeq ($(TEST_TARGET),minishell)
$(error TEST_TARGET should be one of `all`, `bonus`, `42`, `42bonus`)
endif

all: _hide_cursor
	@$(MAKE) SHOW_BANNER=1 BUILD=1 $(NAME); $(PRINTF) "\033[?25h"
ifeq ($(KCSH_TESTS), 1)
	./$(NAME)
	@rm -rf $(NAME)
	@$(MAKE) oclean
endif

_hide_cursor:
	@$(PRINTF) "\033[?25l"

build: clean all

-include $(D_FILES)

# invalidation mechanism
$(CACHE_DIR)/%:
ifeq ($(EXTRA_DEBUG), 1)
	@$(PRINTF) "Invalidate: $* $< $@\n"
endif
	@if [ $(findstring .c, $<) ]; then \
		rm -rf $@; \
	fi

$(CLI_EXEC):
	@$(PRINTF) "\33[2K\r🛠️  Making $(BOLD_WHITE)$(NAME)$(RESET)\n"
	@$(MAKE) -C $(SUBMODULES)/$(MAIN_MODULE) DEPTH="1" CACHE_DIR="$(CACHE_DIR)" LIBFT_DIR="$(LIBFT_DIR)"

$(NAME): $(LIBFT) $(CONFIG_MK) $(FEATURES_H_ACTUAL) $(FEATURES_H) $(CLI_EXEC)
	@$(PRINTF) "⛓  Linking $(CLI_EXEC) -> $(NAME)"
	@cp -f "$(CLI_EXEC)" "$(NAME)" # 🤓 erm acshually its not a link but a copy 🤓
	@$(PRINTF) "\33[2K\r✅ Linked $(BOLD_WHITE)$(NAME)$(RESET), enjoy this dumb madness.\n"

$(LIBFT): $(LIBFT_DIR)/Makefile $(LIBFT_DIR)/version
	@$(PRINTF) "🛠️  Making $(BOLD_WHITE)libft$(RESET)\n"
ifeq ($(HYPERTHREADING), 1)
	@$(MAKE) -C $(LIBFT_DIR) DEBUG=1 NO_LOG="$(FREEZE_LOGS)" -j CFLAGS="-Wall -Werror -Wextra -DGNL_BUFFER_SIZE=1" 
else
	@$(MAKE) -C $(LIBFT_DIR) DEBUG=1 NO_LOG="$(FREEZE_LOGS)" CFLAGS="-Wall -Werror -Wextra -DGNL_BUFFER_SIZE=1" 
endif

$(LAST_COMP):

$(FEATURES_H_ACTUAL): $(FEATURES_H_GEN) $(LAST_COMP)
	@$(PRINTF) "✍  Generating $(BOLD_WHITE)$(FEATURES_H_ACTUAL)$(RESET)\n"
	@$(MAKE) -C config -f features.mk gen COMP_MODE="$(COMP_MODE)"

$(FEATURES_H):
	@$(PRINTF) "⛓  Linking $(BOLD_WHITE)$(FEATURES_H)$(RESET)\n"
	@$(MAKE) -C config -f features.mk genlink COMP_MODE="$(COMP_MODE)"

bonus:
	@$(MAKE) COMP_MODE="BONUS_MSH" SUFFIX="_bonus"

42:
	@$(MAKE) COMP_MODE="MANDATORY_42SH" OVERRIDE_NAME="42sh" NO_READLINE=1

42bonus:
	@$(MAKE) COMP_MODE="BONUS_42SH" OVERRIDE_NAME="42sh" SUFFIX="_bonus" NO_READLINE=1

test: oclean
	@$(MAKE) $(TEST_TARGET) KCSH_TESTS=1

remake: clean all

_fclean_prelude:
	@$(PRINTF) "🧹 Cleaned $(BOLD_WHITE)$(NAME)$(RESET) binaries $(GRAY)(./$(NAME))$(RESET)\n"
	$(eval _DISABLE_CLEAN_LOG := 1)

clean:
	@if [ $(_DISABLE_CLEAN_LOG) -eq 0 ]; then printf "🧹 Cleaned $(BOLD_WHITE)$(NAME)$(RESET) $(GRAY)(./$(CACHE_DIR_NAME))$(RESET)\n"; fi
	@$(RM) $(CACHE_DIR)
	@if [ $(_DISABLE_CLEAN_LOG) -eq 0 ]; then $(MAKE) -C $(LIBFT_DIR) NO_LOG="$(FREEZE_LOGS)" clean; fi 

oclean:
	@$(PRINTF) "🧹 Cleaned $(BOLD_WHITE)$(NAME)$(RESET) object files $(GRAY)($(CACHE_DIR))$(RESET)\n"
	@$(RM) $(CACHE_DIR)

fclean:			_fclean_prelude clean
	@$(RM) $(FEATURES_H_ACTUAL)
	@$(RM) $(FEATURES_H)

	@$(RM) $(POSSIBLE_NAMES)
	@$(MAKE) -C $(LIBFT_DIR) NO_LOG="$(FREEZE_LOGS)" fclean

re: _hide_cursor
	@$(MAKE) BUILD=1 SHOW_BANNER=1 fclean $(NAME); ret=$$?; \
		$(PRINTF) "\033[?25h"; \
		exit $$ret

valgrind:
	@clear
	@MSH_VALGRIND=1 valgrind $(VSUPP_ARG) -s --leak-check=full --show-leak-kinds=all --track-origins=yes --track-fds=yes -q ./$(NAME) $(VG_RUN)

voidgrind:
	@clear
	@valgrind $(VSUPP_ARG) -s --leak-check=full --show-leak-kinds=all --track-origins=yes --track-fds=yes --trace-children=yes -q env -i MSH_VALGRIND=1 ./$(NAME) $(VG_RUN)

flex:
	nix-shell -p cloc --command 'cloc . --include-lang="C/C++ Header,C,D,make,Nix,Bourne Again Shell,Python,Bourne Shell"'

debug_ast: 42bonus
ifeq ($(DEBUG_AST_CMD), )
	@echo "No command defined, run \`make debug_ast DEBUG_AST_CMD=\"your | commands\"\`"
else
	@echo "Printing ast for command: \"${DEBUG_AST_CMD}\""
	@echo ""
	RANDOM_NAME="/tmp/$(shell cat /proc/sys/kernel/random/uuid)-ast.png"; ./$(NAME)_bonus --debug-ast -c "${DEBUG_AST_CMD}" 2>/dev/null | grep "DOT|" | sed 's/.*DOT|//' | dot -Tpng > $$RANDOM_NAME && xdg-open $$RANDOM_NAME
endif

.PHONY:			all bonus 42 42bonus remake clean oclean fclean re valgrind voidgrind flex _fclean_prelude _banner _hide_cursor
