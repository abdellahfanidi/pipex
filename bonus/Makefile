NAME = pipbonus
CFLAGS  = -Wall -Wextra -Werror
SRCS = error.c pipex.c utils1.c utils2.c 
OBJS = error.o pipex.o utils1.o utils2.o 

all : $(NAME)

$(NAME) : $(OBJS)
	cc -o $(NAME) $(OBJS)


clean :
	$(RM) $(OBJS)

fclean : clean
	$(RM) $(NAME)

re : fclean all


.SECONDARY: $(OBJS)
