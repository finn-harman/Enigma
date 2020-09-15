enigma: main.o errors.o plugboard.o rotor.o reflector.o enigma.o
	g++ -g main.o errors.o plugboard.o rotor.o reflector.o enigma.o -o enigma

main.o: main.cpp errors.h plugboard.h rotor.h reflector.h enigma.h
	g++ -Wall -g -c main.cpp

errors.o: errors.cpp errors.h
	g++ -Wall -g -c errors.cpp

plugboard.o: plugboard.cpp errors.h plugboard.h
	g++ -Wall -g -c plugboard.cpp

rotor.o: rotor.cpp errors.h rotor.h
	g++ -Wall -g -c rotor.cpp

reflector.o: reflector.cpp errors.h reflector.h
	g++ -Wall -g -c reflector.cpp

enigma.o: enigma.cpp errors.h enigma.h
	g++ -Wall -g -c enigma.cpp

clean:
	rm -f *.o execute
