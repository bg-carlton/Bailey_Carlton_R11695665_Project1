EXECS=dcooke_analyzer

CC=gcc

MYFILE=lexical_analyzer.c


all: ${EXECS}

${EXECS}: ${MYFILE}
	${CC} -o ${EXECS} ${MYFILE}

clean:
	rm -f ${EXECS}
