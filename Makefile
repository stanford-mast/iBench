#.ONESHELL:
default:
	#$(MAKE) -C src all 
	cd src;\
	g++ -o memCap memCap.c;\
	g++ -o memBw memBw.c;\
	g++ -fopenmp -o cpu cpu.cpp -lpthread -lgomp;\
	g++ -o l1i l1i.c -lrt;\
	g++ -o l1d l1d.c -lrt;\
	g++ -o l3 l3.c -lrt;\
	g++ -o l2 l2.c -lrt;\
	#g++ -o memBench memBench.c; \
	#g++ -o memCapAlt memCapAlt.c
	#gcc -O3 -std=c99 -fopenmp memBw.c -o memBw
	#g++ -o diskCap diskCap.cpp -I/usr/include/glib-2.0 -I/usr/lib/x86_64-linux-gnu/glib-2.0/include  -lglib-2.0;\
	#g++ -o diskBw diskBw.cpp -I/usr/include/glib-2.0 -I/usr/lib/x86_64-linux-gnu/glib-2.0/include  -lglib-2.0;\

clean: 
	rm src/memCap
	rm src/memBw
	rm src/cpu
	rm src/l1i
	rm src/l1d
	rm src/l3
	rm src/l2
