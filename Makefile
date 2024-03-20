# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/08/06 21:19:50 by kiroussa          #+#    #+#              #
#    Updated: 2024/03/20 03:17:51 by kiroussa         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

MAKE			=	make --debug=none --no-print-directory

NAME			=	$(shell $(MAKE) -f config/config.mk print_PROJECT_NAME)
VERSION			=	$(shell $(MAKE) -f config/config.mk print_PROJECT_VERSION)

CWD				?=	$(shell pwd)
SUBMODULES		=	submodules

LIBFT_DIR		=	$(CWD)/third-party/libft
LIBFT			=	$(LIBFT_DIR)/libft.so

CACHE_DIR		=	.cache
CACHE_DIR		:=	$(addprefix $(shell pwd)/, $(CACHE_DIR))

MAIN_MODULE		=	cli
MAIN_MODULE_OUT	=	$(shell $(MAKE) -C $(SUBMODULES)/$(MAIN_MODULE) print_OUTPUT)
CLI_EXEC		=	$(CWD)/$(MAIN_MODULE_OUT)

DEPENDENCY_TREE	=	$(shell $(MAKE) -C $(SUBMODULES)/$(MAIN_MODULE) printdeptree)
D_FILES			:=	$(foreach dep, $(DEPENDENCY_TREE), $(shell $(MAKE) -C $(SUBMODULES)/$(dep) printdepfiles CACHE_DIR="$(CACHE_DIR)"))

RM				=	rm -rf

# Colors
BLUE			:=	$(shell tput -Txterm setaf 4)
BOLD_WHITE		:=	$(shell tput -Txterm setaf 7)
RED				:=	$(shell tput -Txterm setaf 1)
RESET			:=	$(shell tput -Txterm sgr0)
GREEN			:=	$(shell tput -Txterm setaf 2)

AUTHORS			=	$(shell paste -s -d ':' config/author | rev | sed -e 's/\:/ \& /' -e 's/:/ ,/g' | rev) 
VG_RUN			?=

# multiline BANNER
define BANNER
 $(BLUE)               $(BOLD_WHITE)    $(RED)__  
 $(BLUE)   ____ ___  $(BOLD_WHITE)_____$(RED)/ /_ 
 $(BLUE)  / __ `__ \$(BOLD_WHITE)/ ___$(RED)/ __ \  
 $(BLUE) / / / / / $(BOLD_WHITE)(__  )$(RED) / / /
 $(BLUE)/_/ /_/ /_$(BOLD_WHITE)/____/$(RED)_/ /_/  $(RESET)v$(VERSION)
             by $(AUTHORS)

endef

_DISABLE_CLEAN_LOG := 0

all:	 _banner $(NAME) 

build:	all clean

-include $(D_FILES)

_banner:
	$(info $(BANNER))

# invalidation mechanism
$(CACHE_DIR)/%:
	@if [ $(findstring .c, $<) ]; then \
		rm -rf $@; \
	fi

$(CLI_EXEC):
	@printf "\33[2K\rMaking $(NAME)\n"
	@$(MAKE) -C $(SUBMODULES)/$(MAIN_MODULE) DEPTH="1" CACHE_DIR="$(CACHE_DIR)" LIBFT_DIR="$(LIBFT_DIR)"

$(NAME): $(LIBFT) $(CLI_EXEC)
	@printf "Linking $(CLI_EXEC) -> $(NAME)\n"
	@cp -f "$(CLI_EXEC)" "$(NAME)"
	@printf "$(GREEN)Done!$(RESET)\n"

$(LIBFT):
	@printf "Making libft\n"
	@$(MAKE) -C $(LIBFT_DIR) -j 

bonus:
	# @echo "Making $(NAME) bonus"
	@echo "TODO: Implement bonus compilation"

remake: clean all

_fclean_prelude:
	@echo "(F)Cleaning $(NAME)"
	$(eval _DISABLE_CLEAN_LOG := 1)

clean:
	@if [ $(_DISABLE_CLEAN_LOG) -eq 0 ]; then echo "Cleaning $(NAME)"; fi
	$(RM) $(CACHE_DIR)
	@if [ $(_DISABLE_CLEAN_LOG) -eq 0 ]; then $(MAKE) -C $(LIBFT_DIR) clean; fi 

fclean:			_fclean_prelude clean
	$(RM) $(NAME)
	@$(MAKE) -C $(LIBFT_DIR) fclean

re:				fclean all

valgrind:		$(NAME)
	valgrind --suppressions=config/valgrind.vsupp -s --leak-check=full --show-leak-kinds=all --track-origins=yes --track-fds=yes --trace-children=yes ./$(NAME) $(VG_RUN)

.PHONY:			all bonus remake clean fclean re valgrind _fclean_prelude _banner
