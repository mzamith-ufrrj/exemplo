################################################################################
#
#
#  Universidade Federal Rural do Rio de Janeiro
#  por: Marcelo Zamith - mzamith@ufrrj.br
#
################################################################################
CPUCC     = gcc
CPPFLAGS  = -g
DEFS      = 

INCLUDES  = -I.
LIBDIR   =  
LIBS     =   
LINK     =  $(LIBDIR) $(LIBS)
C_COMPILE = $(CPUCC) $(DEFS) $(INCLUDES) $(CPPFLAGS) 


all: minimax main
	$(C_COMPILE) minimax.o main.o -o minimax.bin

lib: minimax
	$(C_COMPILE) -fPIC -shared -o minimax.so minimax.o

minimax:
	$(C_COMPILE) -c minimax.c

main:
	$(C_COMPILE) -c main.c
    
clean:
	rm *.so *.o *.bin
