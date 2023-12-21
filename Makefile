NAME = pipex
BN = pipexbonus
CFLAGS  = -Wall -Wextra -Werror
SRCS = src/error.c src/pipex.c src/utils1.c src/utils2.c 
OBJS = $(SRCS:.c=.o)

SRCSB = bonus/error_bonus.c bonus/pipex_bonus.c bonus/utils1_bonus.c bonus/utils2_bonus.c bonus/utils3_bonus.c
OBJSB = $(SRCSB:.c=.o)

all : $(NAME)

$(NAME) : $(OBJS)
	cc -o $(NAME) $(OBJS)


clean :
	$(RM) $(OBJS) $(OBJSB)

fclean : clean
	$(RM) $(NAME) $(BN)

bonus : $(BN)

$(BN) : $(OBJSB)
	cc -o $(BN) $(OBJSB)

re : fclean all

.PHONY : all bonus clean flean re
#.SECONDARY: $(OBJS) $(OBJSB)