NAME = chess

SRCS =	bitboard.cpp \
		kingGeneration.cpp

OBJS = $(SRCS:.cpp=.o)

CC = c++ -g -Wall -Werror -Wextra
RM = rm -rf

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(OBJS) -o $(NAME)

.cpp.o:
	$(CC) -c $< -o $(<:.cpp=.o)

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all
