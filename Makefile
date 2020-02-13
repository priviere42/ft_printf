SRCS =  ft_itoas_base.c \
		utils.c      	\
		print_nbr.c		\
		print_str.c		\
		manage_flags.c	\
		print_p.c		\
		print_w_or_p.c	\
		ft_printf_utils.c \
		ft_printf.c

INCLUDES = ft_printf.h

OBJS = ${SRCS:.c=.o}

NAME = libftprintf.a

CC = cc
RM = rm -f

CFLAGS = -Wall -Werror -Wextra

all:		${NAME}

lib: 	
			make -C libft all

libcl:  
			make -C libft clean

libfcl:  
			make -C libft fclean

%.o: 		%.c ${INCLUDES}
			${CC} ${CFLAGS} -c $< -o ${<:.c=.o}

$(NAME):	lib ${OBJS}
			ar rc ${NAME} ${OBJS}

clean:		libcl
			${RM} ${OBJS}

fclean:		libfcl clean
			${RM} ${NAME}

re:			fclean all

.PHONY:		all clean fclean re
