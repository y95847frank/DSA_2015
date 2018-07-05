CC = g++ -std=c++11 -O2 

all:final_project

final_project: main.cpp create.o transfer.o deposit.o merge.o delete.o find.o withdraw.o search.o login.o auxiliary.o md5.o bank.o
	$(CC) main.cpp auxiliary.o create.o transfer.o deposit.o merge.o delete.o find.o withdraw.o search.o login.o md5.o bank.o -o final_project

create.o: create.cpp account.h
	$(CC) -c create.cpp

login.o: login.cpp account.h
	$(CC) -c login.cpp

bank.o: bank.cpp account.h
	$(CC) -c bank.cpp

md5.o: md5.cpp
	$(CC) -c md5.cpp

delete.o: delete.cpp account.h
	$(CC) -c delete.cpp

withdraw.o: withdraw.cpp account.h
	$(CC) -c withdraw.cpp

search.o: search.cpp account.h
	$(CC) -c search.cpp

merge.o: merge.cpp account.h
	$(CC) -c merge.cpp

transfer.o: transfer.cpp account.h
	$(CC) -c transfer.cpp

auxiliary.o: auxiliary.cpp account.h
	$(CC) -c auxiliary.cpp

find.o: find.cpp account.h
	$(CC) -c find.cpp

deposit.o:deposit.cpp account.h
	$(CC) -c deposit.cpp

clean:
	rm md5.o auxiliary.o create.o transfer.o deposit.o merge.o delete.o find.o withdraw.o search.o login.o bank.o final_project
