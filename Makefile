SRCS = 	ft_atoi.c \
		ft_itoas_base.c \
		ft_strdup.c \
		ft_strlen_prec.c \
		ft_strlen.c \
		main.c

INCLUDES = libft.h

OBJS = ${SRCS:.c=.o}

NAME = ft_printf.a

CC = cc
RM = rm -f

CFLAGS = -Wall -Wextra -Werror

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
