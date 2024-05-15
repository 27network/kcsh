# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/08/06 21:19:50 by kiroussa          #+#    #+#              #
#    Updated: 2024/05/15 23:59:00 by kiroussa         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

MAKE			=	make --debug=none --no-print-directory

CONFIG_DIR		=	config
CONFIG_MK		=	$(CONFIG_DIR)/config.mk
NAME			=	minishell

ifdef OVERRIDE_NAME
NAME			:=	$(OVERRIDE_NAME)
endif
ifdef SUFFIX
NAME			:=	$(NAME)$(SUFFIX)
endif

VERSION			=	$(shell $(MAKE) -f $(CONFIG_MK) print_PROJECT_VERSION)
EXTRA_DEBUG		=	$(shell $(MAKE) -f $(CONFIG_MK) print_EXTRA_DEBUG)
COMP_MODE		?=	MANDATORY_MSH

CACHE_DIR_NAME	=	.cache
CACHE_DIR		=	$(addprefix $(shell pwd)/, $(CACHE_DIR_NAME))

LAST_COMP		=	$(CONFIG_DIR)/.last_comp
_LAST_COMP_DATA	:=	$(shell cat $(LAST_COMP) 2>/dev/null)
_LAST_COMP		:=	$(word 1, $(_LAST_COMP_DATA))
ifneq ($(_LAST_COMP), $(COMP_MODE))
ifeq ($(BUILD), 1)
REBUILD			:=	1
ifeq ($(_LAST_COMP), )
REBUILD			:=	0
endif
_				:=	$(shell echo "$(COMP_MODE)" > $(LAST_COMP))
_				:=	$(shell rm -rf $(CACHE_DIR) $(NAME))
endif
endif

-include header.mk

POSSIBLE_NAMES	=	minishell minishell_bonus 42sh 42sh_bonus

CWD				?=	$(shell pwd)
SUBMODULES		=	submodules

LIBFT_DIR		=	$(CWD)/third-party/libft
LIBFT			=	$(LIBFT_DIR)/libft.so

FEATURES_H		=	$(SUBMODULES)/shared/include/msh/features.h
FEATURES_H_ACTUAL=	$(CONFIG_DIR)/features.h
FEATURES_H_GEN	=	$(FEATURES_H_ACTUAL).gen.sh

MAIN_MODULE		=	cli
MAIN_MODULE_OUT	=	$(shell $(MAKE) -C $(SUBMODULES)/$(MAIN_MODULE) print_OUTPUT)
CLI_EXEC		=	$(CWD)/$(MAIN_MODULE_OUT)

DEPENDENCY_TREE	=	$(shell $(MAKE) -C $(SUBMODULES)/$(MAIN_MODULE) printdeptree)

D_FILES			:=	$(foreach dep, $(DEPENDENCY_TREE), $(shell $(MAKE) -C $(SUBMODULES)/$(dep) printdepfiles CACHE_DIR="$(CACHE_DIR)"))

RM				=	rm -rf

VG_RUN			?=
_DISABLE_CLEAN_LOG := 0

all: _hide_cursor
	@$(MAKE) SHOW_BANNER=1 BUILD=1 $(NAME); ret=$$?; \
		printf "\033[?25h"; \
		exit $$ret

_hide_cursor:
	@printf "\033[?25l"

build: clean all

-include $(D_FILES)

# invalidation mechanism
$(CACHE_DIR)/%:
ifeq ($(EXTRA_DEBUG), 1)
	@printf "Invalidate: $* $< $@\n"
endif
	@if [ $(findstring .c, $<) ]; then \
		rm -rf $@; \
	fi

$(CLI_EXEC):
	@printf "\33[2K\r🛠️  Making $(BOLD_WHITE)$(NAME)$(RESET)\n"
	@$(MAKE) -C $(SUBMODULES)/$(MAIN_MODULE) DEPTH="1" CACHE_DIR="$(CACHE_DIR)" LIBFT_DIR="$(LIBFT_DIR)" # 3>/dev/null 2>&3

$(NAME): $(LIBFT) $(CONFIG_MK) $(FEATURES_H_ACTUAL) $(FEATURES_H) $(CLI_EXEC)
	@printf "⛓  Linking $(CLI_EXEC) -> $(NAME)"
	@cp -f "$(CLI_EXEC)" "$(NAME)" # 🤓 erm acshually its not a link but a copy 🤓
	@printf "\33[2K\r✅ Linked $(BOLD_WHITE)$(NAME)$(RESET), enjoy this dumb madness.\n"

$(LIBFT):
	@printf "🛠️  Making $(BOLD_WHITE)libft$(RESET)\n"
	@$(MAKE) -C $(LIBFT_DIR) -j 
	@printf "\033[1A\33[2K\r✅ Built $(BOLD_WHITE)libft$(RESET)    \n\33[2K\r"

$(LAST_COMP):

$(FEATURES_H_ACTUAL): $(FEATURES_H_GEN) $(LAST_COMP)
	@printf "✍  Generating $(BOLD_WHITE)$(FEATURES_H_ACTUAL)$(RESET)\n"
	@$(MAKE) -C config -f features.mk gen COMP_MODE="$(COMP_MODE)"

$(FEATURES_H):
	@printf "⛓  Linking $(BOLD_WHITE)$(FEATURES_H)$(RESET)\n"
	@$(MAKE) -C config -f features.mk genlink COMP_MODE="$(COMP_MODE)"

bonus:
	@$(MAKE) COMP_MODE="BONUS_MSH" SUFFIX="_bonus"

42:
	@$(MAKE) COMP_MODE="MANDATORY_42SH" OVERRIDE_NAME="42sh"

42bonus:
	@$(MAKE) COMP_MODE="BONUS_42SH" OVERRIDE_NAME="42sh" SUFFIX="_bonus"

remake: clean all

_fclean_prelude:
	@printf "🧹 Cleaned $(BOLD_WHITE)$(NAME)$(RESET) binaries $(GRAY)(./$(NAME))$(RESET)\n"
	$(eval _DISABLE_CLEAN_LOG := 1)

clean:
	@if [ $(_DISABLE_CLEAN_LOG) -eq 0 ]; then printf "🧹 Cleaned $(BOLD_WHITE)$(NAME)$(RESET) $(GRAY)(./$(CACHE_DIR_NAME))$(RESET)\n"; fi
	@$(RM) $(CACHE_DIR)
	@if [ $(_DISABLE_CLEAN_LOG) -eq 0 ]; then $(MAKE) -C $(LIBFT_DIR) clean; fi 

oclean:
	@printf "🧹 Cleaned $(BOLD_WHITE)$(NAME)$(RESET) object files $(GRAY)(./$(CACHE_DIR))$(RESET)\n"
	@$(RM) $(CACHE_DIR)

fclean:			_fclean_prelude clean
	@$(RM) $(FEATURES_H_ACTUAL)
	@$(RM) $(FEATURES_H)

	@$(RM) $(POSSIBLE_NAMES)
	@$(MAKE) -C $(LIBFT_DIR) fclean

re: _hide_cursor
	@$(MAKE) BUILD=1 SHOW_BANNER=1 fclean $(NAME); ret=$$?; \
		printf "\033[?25h"; \
		exit $$ret

valgrind:		$(NAME)
	valgrind --suppressions=config/valgrind.vsupp -s --leak-check=full --show-leak-kinds=all --track-origins=yes --track-fds=yes --trace-children=yes -q ./$(NAME) $(VG_RUN)

.PHONY:			all bonus remake clean oclean fclean re valgrind _fclean_prelude _banner _hide_cursor
