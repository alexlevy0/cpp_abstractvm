##
## Makefile for make in /home/levy_b/rendu/cpp_bomberman
## 
## Made by LEVY Alexandre
## Login   <levy_b@epitech.net>
## 
## Started on  Wed May 20 18:14:00 2015 LEVY Alexandre
## Last update Sun Jun 14 22:36:50 2015 LEVY Alexandre
##

CC      =       g++

RM      =       rm -f

NAME    =       bomberman

CPPFLAGS  +=    -I./includes/

LDFLAGS +=      -L./libs/ -lgdl_gl -lGL -lGLEW -ldl -lrt -lfbxsdk -lSDL2 -lpthread

SRCS    =       main.cpp \
		Core.cpp \
		CoreMap.cpp \
		Menu.cpp \
		Marvin.cpp \
		Slide.cpp \

OBJS    =       $(SRCS:.cpp=.o)

all:            $(NAME)

$(NAME):        $(OBJS)
		$(CC) -o $(NAME) $(OBJS) $(LDFLAGS)

clean:
		$(RM) $(OBJS)

fclean:         clean
		$(RM) $(NAME)

re:             fclean all

.PHONY:         all clean fclean re
