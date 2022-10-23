wipRPG: wipRPG.o
	g++ wipRPG.o -o wipRPG

wipRPG.o: wipRPG.cpp
	g++ -c wipRPG.cpp

clean:
	rm *.o wipRPG