# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    header.mk                                          :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/03/25 15:29:36 by kiroussa          #+#    #+#              #
#    Updated: 2024/05/15 23:52:53 by kiroussa         ###   ########.fr        #
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
BOLD_WHITE		:=	$(RESET)$(BOLD)

AUTHORS			=	$(shell paste -s -d ':' config/author | rev | sed -e 's/\:/ \& /' -e 's/:/ ,/g' | rev) 

# multiline BANNER
define BANNER
 $(BLUE)               $(BOLD_WHITE)    $(RED)__  
 $(BLUE)   ____ ___  $(BOLD_WHITE)_____$(RED)/ /_ 
 $(BLUE)  / __ `__ \$(BOLD_WHITE)/ ___$(RED)/ __ \  
 $(BLUE) / / / / / $(BOLD_WHITE)(__  )$(RED) / / /
 $(BLUE)/_/ /_/ /_$(BOLD_WHITE)/____/$(RED)_/ /_/  $(RESET)v$(VERSION)
             by $(AUTHORS)
endef

SHOW_BANNER	?=	0
DISABLE_BANNER ?= 0

ifeq ($(SHOW_BANNER), 1)
ifeq ($(DISABLE_BANNER), 0)
$(info $(BANNER))
$(info ⚙️  Compilation mode: $(COMP_MODE))
ifeq ($(REBUILD), 1)
$(info 🔄 Rebuilding $(NAME) with $(BOLD_WHITE)$(COMP_MODE)$(RESET) mode)
endif
$(info )
endif
endif
