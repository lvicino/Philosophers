# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lvicino <lvicino@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/02/20 12:33:00 by lvicino           #+#    #+#              #
#    Updated: 2024/07/19 18:21:04 by lvicino          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	philo

BNAME		=	philo_bonus


BUILD_DIR	=	build


SRC_DIR		=	src

SRC			=	philo.c \
				philo_utils.c \
				init.c \
				check.c

SRC			:=	$(SRC:%=$(SRC_DIR)/%)
OBJ			=	$(SRC:$(SRC_DIR)/%.c=$(BUILD_DIR)/%.o)
DEP			=	$(OBJ:$(BUILD_DIR)/%.o=$(BUILD_DIR)/%.d)


BSRC_DIR		=	src_bonus

BSRC			=	philo_bonus.c \
					philo_utils_bonus.c \
					init_bonus.c \
					check_bonus.c \
					routine_bonus.c

BSRC			:=	$(BSRC:%=$(BSRC_DIR)/%)
BOBJ			=	$(BSRC:$(BSRC_DIR)/%.c=$(BUILD_DIR)/%.o)
BDEP			=	$(BOBJ:$(BUILD_DIR)/%.o=$(BUILD_DIR)/%.d)


CC			=	cc
CFLAGS		=	-Wall -Wextra -Werror -g3 -MMD -MP -I include
INCLUDE		=	-I include

MAKEFLAGS	+=	--no-print-directory
DIR_DUP		=	mkdir -p $(@D)


all		:	$(NAME)

$(NAME)		:	$(OBJ)
	$(CC) $(OBJ) -o $(NAME)


$(BUILD_DIR)/%.o		:	$(SRC_DIR)/%.c
	$(DIR_DUP)
	$(CC) $(CFLAGS) $(INCLUDE) -c -o $@ $<


bonus	:	$(BNAME)

$(BNAME)		:	$(BOBJ)
	$(CC) $(BOBJ) -o $(BNAME)


$(BUILD_DIR)/%.o		:	$(BSRC_DIR)/%.c
	$(DIR_DUP)
	$(CC) $(CFLAGS) $(INCLUDE) -c -o $@ $<


-include $(DEP) $(BDEP)

clean	:
	if [ -d "$(BUILD_DIR)" ]; then \
		rm -f $(OBJ); \
		rm -f $(DEP); \
		rm -f $(BOBJ); \
		rm -f $(BDEP); \
		rmdir $(BUILD_DIR); \
	fi

fclean	:	clean
	if [ -e "$(NAME)" ]; then \
		rm -f $(NAME); \
	fi
	if [ -e "$(BNAME)" ]; then \
		rm -f $(BNAME); \
	fi

re		:	fclean all

.PHONY	:	clean fclean re
.SILENT	:	clean fclean
