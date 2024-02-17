CC	= clang++
INSTDIR = ./
CFLAGS	= -w -I. -DDEBUG -O3
LIBDIR  = 
LIB     = 
SOURCES	= main.cpp
HEADERS	= matrix.h
OBJS	= main.o
TARGET	= doit
RM      = rm

all: $(OBJS)
	$(CC) $(LIBDIR) -o ${TARGET} $(OBJS) $(LIB)

$(OBJS): $(SOURCES) $(HEADERS)
	$(CC) $(CFLAGS) -c $(SOURCES)

clean: 
	@-$(RM) *.o *.core $(TARGET)
install:
	cp ${TARGET} ${INSTDIR}
