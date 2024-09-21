# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    header.mk                                          :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/03/25 15:29:36 by kiroussa          #+#    #+#              #
#    Updated: 2024/09/21 16:14:53 by kiroussa         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Colors
TPUT			:=	tput -Txterm-256color
BLUE			:=	$(shell $(TPUT) setaf 4)
GRAY			:=	$(shell $(TPUT) setaf 8)
BOLD 			:=  $(shell $(TPUT) bold)
RED				:=	$(shell $(TPUT) setaf 1)
RESET			:=	$(shell $(TPUT) sgr0)
GREEN			:=	$(shell $(TPUT) setaf 2)
MAGENTA			:=	$(shell $(TPUT) setaf 135)
BOLD_WHITE		:=	$(RESET)$(BOLD)

AUTHORS			=	$(shell paste -s -d ':' config/author | rev | sed -e 's/\:/ \& /' -e 's/:/ ,/g' | rev) 

# multiline BANNER
COL1			=	$(BOLD)$(MAGENTA)
COL2			=	$(BOLD)$(RED)
COL3			=	$(BOLD)$(GRAY)
COL4			=	$(BOLD)$(BLUE)
define BANNER
 $(COL1)    __             $(COL4)__  
 $(COL1)   / /__$(COL2)_____$(COL3)_____$(COL4)/ /_ 
 $(COL1)  / //_$(COL2)/ ___/$(COL3) ___$(COL4)/ __ \ 
 $(COL1) / ,< $(COL2)/ /__$(COL3)(__  ) $(COL4)/ / /
 $(COL1)/_/|_|$(COL2)\___/$(COL3)____/$(COL4)_/ /_/  $(RESET)v$(BOLD_WHITE)$(PROJECT_VERSION)$(RESET)
             by $(RESET)$(AUTHORS)

endef
                       

SHOW_BANNER	?=	0
DISABLE_BANNER ?= 0

ifeq ($(SHOW_BANNER), 1)
ifeq ($(DISABLE_BANNER), 0)
$(info $(BANNER))
$(info ⚙️  Compilation mode: $(COMP_MODE))
ifeq ($(KCSH_TESTS), 1)
$(info 🧪 Test runner enabled)
endif
ifeq ($(HYPERTHREADING), 1)
$(info 🚀 Hyperthreading enabled)
endif
ifeq ($(REBUILD), 1)
$(info 🔄 Rebuilding $(NAME) with $(BOLD_WHITE)$(COMP_MODE)$(RESET) mode)
endif
$(info )
endif
endif
