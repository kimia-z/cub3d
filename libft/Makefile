# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: rshaheen <rshaheen@student.42.fr>            +#+                      #
#                                                    +#+                       #
#    Created: 2023/10/22 20:15:04 by rshaheen      #+#    #+#                  #
#    Updated: 2025/03/12 15:54:26 by rshaheen      ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

CC	=	cc
CFLAGS	=	-Wall -Wextra -Werror -g

NAME	=	libft.a

RM	=	rm	-f

AR	=	ar	-rcs

INCLUDE	=	libft.h
SOURCES	=	ft_atoi.c	ft_bzero.c	ft_isalnum.c	ft_isalpha.c	ft_tolower.c	\
	ft_isascii.c	ft_isdigit.c	ft_isprint.c	ft_memchr.c	ft_memcpy.c	\
	ft_memcmp.c	ft_memset.c	ft_strchr.c	ft_strlcat.c	ft_toupper.c \
	ft_strlcpy.c	ft_strlen.c	ft_strcmp.c ft_strncmp.c	ft_calloc.c	ft_strrchr.c	\
	ft_memmove.c	ft_strdup.c	ft_strnstr.c	ft_strjoin.c	ft_putchar_fd.c	\
	ft_putstr_fd.c	ft_putendl_fd.c	ft_putnbr_fd.c	ft_isspace.c ft_strmapi.c	\
	ft_strtrim.c	ft_substr.c	ft_split.c	ft_itoa.c	ft_striteri.c  ft_atol.c \
	ft_printf.c	ft_print_unsign.c	ft_print_str.c	ft_print_pointer.c	ft_print_num.c \
	ft_print_hex.c	ft_print_convert.c	ft_print_c.c	get_next_line.c
	

OBJECTS	=	$(SOURCES:.c=.o)

all:	$(NAME)

$(NAME):	$(OBJECTS)	$(INCLUDE)
	$(AR)	$(NAME)	$(OBJECTS)

%.o:%.c
	$(CC)	$(CFLAGS)	-I.	-c	$<	-o	$@

clean:
	$(RM)	$(OBJECTS)

fclean:	clean
	$(RM)	$(NAME)

re: fclean all

.PHONY: all clean fclean re
