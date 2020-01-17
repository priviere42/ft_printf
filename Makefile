SRCS =  ft_itoas_base.c \
		utils.c      	\
		print_nbr.c		\
		print_str.c		\
		ft_printf.c

INCLUDES = libft.h

OBJS = ${SRCS:.c=.o}

NAME = libftprintf.a

CC = cc
RM = rm -f

CFLAGS = -Wall -Werror -Wextra

all:		${NAME}

%.o: 	%.c ${INCLUDES}
	${CC} ${CFLAGS} -c $< -o ${<:.c=.o}

$(NAME):	${OBJS}
	ar rc ${NAME} ${OBJS}
		
clean:
	${RM} ${OBJS}

fclean:		clean
	${RM} ${NAME}

re:			fclean all

.PHONY:		all clean fclean re
