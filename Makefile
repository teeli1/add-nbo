all: main

#오브젝트 파일
main.o: main.cpp
	g++ -c -o main.o main.cpp

#실행 파일
main: main.o
	g++ -o main main.o

clean:
	rm -f *.o main