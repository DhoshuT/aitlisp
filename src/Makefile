#CC=arm-linux-gnueabi-gcc
CC=gcc

GDB=-g
#GDB=

OBJ=in.o out.o eval.o func.o wtlst.o proc.o
OPT1=-static $(GDB) -Wall
OPT2=-static $(GDB) -DORIG_C -Wall

alsp: lisp_mt.c $(OBJ) lisp_mt.h proc.h
	$(CC) $(OPT1) -o $@ $(OBJ) lisp_mt.c

alspo: lisp_mt.c $(OBJ) lisp_mt.h proc.h
	$(CC) $(OPT2) -o $@ $(OBJ) lisp_mt.c

in.o: in.c  lisp_mt.h proc.h
	$(CC) -c $(OPT1) $<
out.o: out.c  lisp_mt.h
	$(CC) -c $(OPT1) $<
eval.o: eval.c  lisp_mt.h proc.h
	$(CC) -c $(OPT1) $< 
func.o: func.c  lisp_mt.h
	$(CC) -c $(OPT1) $<
wtlst.o: wtlst.c  lisp_mt.h
	$(CC) -c $(OPT1) $<
proc.o: proc.c  lisp_mt.h proc.h
	$(CC) -c $(OPT1) $<

tlisp: lisp_mt.c $(OBJ_T) lisp_mt.h
	$(CC) $(OPT1) -DTREE_EXP -o $@ $(OBJ) lisp_mt.c

clean:
	rm -f *~ *.[oais] *.core


