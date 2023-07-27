# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tel-mouh <tel-mouh@student.1337.ma>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/05/31 04:31:34 by tel-mouh          #+#    #+#              #
#    Updated: 2023/07/27 03:23:35 by tel-mouh         ###   ########.fr        #
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
HEADERS = $(wildcard include/*.hpp) $(wildcard include/*.h)

# ################COMMANDS###########################

RM = rm -rf
CC = g++ -g -std=c++98  -Wall -Wextra -Werror 
# CC = g++ -g -std=c++98  -fsanitize=address
HEADERSFLAGS = -I include
CFLAG = -g $(HEADERSFLAGS)
#  -Wall -Wextra -Werror 
# #################LOG_File##########################

LOG_FILE = lastcompiled.log

# ################SRCS_Objs##########################

SRC = $(notdir $(wildcard src/*.cpp))
OBJ = $(addprefix obj/, $(SRC:.cpp=.o))

# ################SRC_COMMANDS####################

SRC_COMMANDS =	$(notdir $(wildcard src/commands/*.cpp))
OBJ_COMMANDS = $(addprefix obj/commands/, $(SRC_COMMANDS:.cpp=.o))
# ################SRCS_Objs_Utils####################

# SRC_UTILS =		
# OBJ_UTILS = $(addprefix obj/utils/, $(SRC_UTILS:.cpp=.o))


# ################OBJSALL############################

OBJ_ALLS =	$(OBJ) $(OBJ_COMMANDS)

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

obj/%.o : src/%.cpp  $(HEADERS)
	@ mkdir -p $(dir $@)
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