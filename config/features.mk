# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    features.mk                                        :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/03/23 00:16:42 by kiroussa          #+#    #+#              #
#    Updated: 2024/05/15 12:00:41 by kiroussa         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = features.h
SOURCE = features.h.gen.sh
TARGET = ../submodules/shared/include/msh/features.h
COMP_MODE ?= MENDATORY_MSH

all:
	@echo "Usage: make gen [COMP_MODE=MODE]"

genlink: $(TARGET)

$(TARGET):
	ln -fs $(shell pwd)/$(NAME) $(TARGET)

gen:
	bash $(SOURCE) $(COMP_MODE) > $(NAME)

.PHONY: all gen genlink
.SILENT:
