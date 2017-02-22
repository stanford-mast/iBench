default:
	g++ -o src/memCap src/memCap.c
	g++ -o src/memBw src/memBw.c
	g++ -fopenmp -o src/cpu src/cpu.cpp -lpthread -lgomp
	g++ -o src/l1i src/l1i.c -lrt
	g++ -o src/l1d src/l1d.c -lrt
	g++ -o src/l3 src/l3.c -lrt
	g++ -o src/l2 src/l2.c -lrt


clean:
	rm src/memCap
	rm src/memBw
	rm src/cpu
	rm src/l1i
	rm src/l1d
	rm src/l3
	rm src/l2
