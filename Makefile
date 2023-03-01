build: trade_simulator.c
	gcc -Wall -o trade_simulator trade_simulator.c

clean: trade_simulator
	rm -rf trade_simulator

run: trade_simulator
	./trade_simulator