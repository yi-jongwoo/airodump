all : airodump

airodump : main.o proto_structures.o dot11.o
	g++ main.o proto_structures.o dot11.o -lpcap -o airodump

main.o : main.cpp dot11.h proto_structures.h
	g++ -c main.cpp -o main.o -std=c++20 -Wno-multichar

proto_structures.o : proto_structures.cpp proto_structures.h
	g++ -c proto_structures.cpp -o proto_structures.o

dot11.o : dot11.cpp dot11.h proto_structures.h
	g++ -c dot11.cpp -o dot11.o

clean :
	rm -f *.o
	rm -f airodump
