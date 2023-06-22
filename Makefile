# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tel-mouh <tel-mouh@student.1337.ma>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/05/31 04:31:34 by tel-mouh          #+#    #+#              #
#    Updated: 2023/06/05 07:10:26 by tel-mouh         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SHELL := /bin/bash # Use bash syntax


# #################FLAGS#############################

OS = $(shell uname -s)
ifeq ($(OS),Linux)
	LFLAGS= 
	IFLAGS= 
	NEW_FILE = /tmp/newfile
	EMOJI = "🟩"
else
	NEW_FILE = ~/goinfre/newfile
	EMOJI = "🟩"
	LFLAGS=
	IFLAGS= 
endif


# #################HEADERS###########################
HEADERS = *.hpp
HEADERS := $(addprefix include/, $(HEADERS))
# #################HEADERS_utils###########################
UHEADERS = 
UHEADERS := $(addprefix include/, $(UHEADERS))

# ################COMMANDS###########################

RM = rm -rf
CC = g++ 
HEADERSFLAGS = -I include
CFLAG =  -Wall -Wextra -Werror -g $(HEADERSFLAGS)

# #################LOG_File##########################

LOG_FILE = lastcompiled.log

# ################SRCS_Objs##########################

SRC = 	main.cpp
OBJ = $(addprefix obj/, $(SRC:.cpp=.o))

# ################SRCS_Objs_Utils####################

# SRC_UTILS =		
# OBJ_UTILS = $(addprefix obj/utils/, $(SRC_UTILS:.cpp=.o))


# ################OBJSALL############################

OBJ_ALLS =	$(OBJ) 

# ################OBJDIR############################

OBJ_DIRS = obj 

# ################COLOR##############################

COLOR='\033[0;32m'
NC='\033[0m'
RE= '\033[0;34m'
GREEN='\033[0;32m'
YELLOW='\033[0;33m'

CODE_SAVE_CURSOR='\033[s'
CODE_RESTORE_CURSOR='\033[u'
CODE_CURSOR_IN_SCROLL_AREA="\033[1A"

# ###############executable##########################

NAME = ircserv
LIBFT = libft/library/libft.a
ILIBFT = -I libft/include


# ###################################################

lines=$(shell tput lines)
cols=$(shell tput cols)
num=$(shell echo `find ./src -type f -name "*.cpp" | wc -l`)
i_num=0
x  = 0

# ###################################################


all : $(NAME)


$(NAME):  $(OBJ_ALLS) 
	@ printf "\033[$(lines);0f"
	@ tput el
	@printf  ${CODE_RESTORE_CURSOR}""
	@tput el
	@ printf ${GREEN}"\rMaking is done ✅\n"${NC}
	@$(CC) $(CFLAG)  $(OBJ_ALLS)  -g -o $(NAME)
	@ tput cvvis
	@ echo "---------------------------------------------------" | cat -  $(LOG_FILE) > $(NEW_FILE) && mv $(NEW_FILE)  $(LOG_FILE)

curser:
	@ tput cvvis

obj/%.o : src/%.cpp  
	@ mkdir -p $(OBJ_DIRS)
	@$ nu=$x ; if [[ $$nu -eq -1 ]] ; then \
	printf ${RE}"🔷 Making the--> "${NC} \
	 ; fi
	@if  $(CC) $(CFLAG)  $(IFLAGS)   -c $< -o $@; then \
		echo -n; \
		else \
			tput cvvis; \
			exit 1; \
		fi
	@tput civis
	$(eval x = $(shell echo "$(x) + 1" | bc ))
	@ printf $(notdir $@)"\n"
	@ printf  ${CODE_SAVE_CURSOR}""
	@ printf "\033[$(lines);0f"
	@ echo $< | cat -  $(LOG_FILE) > $(NEW_FILE) && mv $(NEW_FILE)  $(LOG_FILE)
	@number=`echo "$(x) * $(cols) / $(num)" | bc | tr -d '\n'` ; while [[ $$number -ne 1 ]] ; do \
		if [[ $$(( $$number % 2 )) -eq 0 ]]; then printf ${YELLOW}"${EMOJI}"${NC} ; fi ;\
        ((number = number - 1)) ; \
    done
	@printf  ${CODE_RESTORE_CURSOR}""
	@printf  ${CODE_CURSOR_IN_SCROLL_AREA}""
	@printf  ${CODE_SAVE_CURSOR}""
	@printf ${RE}"🔷 Making the  --> "${NC} 
	@tput el

clean :
	@ $(RM) $(OBJ_ALLS)
	@ $(RM) $(LOG_FILE)
	@ touch $(LOG_FILE)
fclean : clean
	@ $(RM) $(NAME)

re : fclean all