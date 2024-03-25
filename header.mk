# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    header.mk                                          :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/03/25 15:29:36 by kiroussa          #+#    #+#              #
#    Updated: 2024/03/25 15:29:38 by kiroussa         ###   ########.fr        #
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

DISABLE_BANNER ?= 0

ifeq ($(DISABLE_BANNER), 0)
$(info $(BANNER))
$(info ⚙️ Compilation mode: $(COMP_MODE))
$(info )
endif

