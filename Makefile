#.ONESHELL:
default:
	#$(MAKE) -C src all 
	cd src;\
	g++ -o memCap memCap.c;\
	g++ -o memBw memBw.c;\
	g++ -o strided strided.c;\
	g++ -fopenmp -o cpu cpu.cpp -lpthread -lgomp;\
	g++ -o diskCap diskCap.cpp -I/usr/include/glib-2.0 -I/usr/lib/x86_64-linux-gnu/glib-2.0/include  -lglib-2.0;\
	g++ -o diskBw diskBw.cpp -I/usr/include/glib-2.0 -I/usr/lib/x86_64-linux-gnu/glib-2.0/include  -lglib-2.0;\
	g++ -o l1i l1i.c -lrt;\
	g++ -o l1d l1d.c -lrt;\
	g++ -o l3 l3.c -lrt;\
	g++ -o l2 l2.c -lrt;\
	g++ -o netIO netIO.c -lrt;\
	#g++ -o memBench memBench.c; \
	#g++ -o memCapAlt memCapAlt.c
	#gcc -O3 -std=c99 -fopenmp memBw.c -o memBw

clean: 
	rm memCap
	rm memBench
	rm memCapAlt
	rm memBw
	rm strided
	rm cpu
	rm diskCap
	rm diskBw
	rm l1i
	rm l1d
	rm l3
	rm l2
	rm netIO
