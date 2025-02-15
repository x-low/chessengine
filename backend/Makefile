NAME = chess

SRCS =	chess.cpp \
		bitboard.cpp \
		queenGeneration.cpp \
		rookGeneration.cpp \
		bishopGeneration.cpp

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
