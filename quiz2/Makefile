size = 0
code = 0

plot:
	gcc -o $(code).out $(code).c
	./$(code).out $(size)
	gnuplot $(code).gp

clean:
	rm -f *.out *.s *.txt *.data *.old *.png