all : outpimc

parsepimc.tab.c parsepimc.tab.h: parsepimc.y
	bison -d parsepimc.y

lex.yy.c: parsepimc.l parsepimc.tab.h
	flex parsepimc.l

outpimc: lex.yy.c parsepimc.tab.c parsepimc.tab.h State.h Interval.h Pimc.h algorithmics.h
	g++ parsepimc.tab.c lex.yy.c State.cc Interval.cc Pimc.cc algorithmics.cc -ll -o outpimc -lppl -lgmpxx -lgmp
	
clean:
	rm -rf *.tab.c *.tab.h outpimc