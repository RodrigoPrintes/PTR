#Makefile de lab (main)
#Autor: André Cavalcante

#Gera o arquivo executável na pasta atual

#Cabecalho de variaveis de ambiente padrao
CFLAGS=-O2 -Wall -mtune=generic
CINCLUDE=-I. -I./include -I${HOME}/include
CLIBDIR=-L. -L./lib -L../lib -L${HOME}/lib
#libc eh inserida por padrao
CLIBS=-lpthread -lm
# -lctrl

CPPFLAGS=
CPPINCLUDE=-I${HOME}/include/cpp -I../include
CPPLIBDIR=-L../lib
CPPLIBS=

INCLUDE=${CINCLUDE} ${CPPINCLUDE}
FLAGS= ${CFLAGS} ${CPPFLAGS}
LIBDIR=${CLIBDIR} ${CPPLIBDIR}
LIBS=${CPPLIBS} ${CLIBS}

CMP= gcc
CMPFLAGS= ${FLAGS} ${INCLUDE}
LDFLAGS= ${LIBDIR} ${LIBS}

#regras

#all - faz o make de tudo
all: clock

#lab - faz make de main.c
clock: main.c  monitor.o display.o clock.o
	${CMP} ${CMPFLAGS} -o $@ main.c monitor.o display.o clock.o ${LDFLAGS}


#redefine a regra implicita de compilacao de objetos para incluir a nossa estrutra
%.o: %.c %.h
	${CMP} -c ${CMPFLAGS} -o $@ $<

#clean - remove do diretorio os objs e arquivos de backups do gedit
clean:
	rm -f *~ *.bak *.o

#install - nada faz, por enquanto, mantido por causa do padrao        
install:

#distclean - limpa toda a estrutura de pastas
distclean: clean
	rm -f clock

