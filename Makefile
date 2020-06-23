
all: compile
	
compile:
	clear 
	
	mpicc 	-o trab2 	4_primo_mpi.c -lm


	@echo "Compilaçao concluida"

clean:
	rm -rf ?
	rm -rf ??


