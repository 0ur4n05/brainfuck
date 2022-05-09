CNAME = bf 
CC = gcc
CFLAGS = -Wall -Wextra -Werror 

$(CNAME) : src/* 
	cd obj/ ; $(CC) -c ../src/* $(CFLAGS)	
	cd ..
	$(CC) obj/* -o $(CNAME) 


debug : src/* 
	cd obj/ ; $(CC) -c ../src/* $(CFLAGS) -g
	cd ..
	$(CC) obj/* -o $(CNAME) 
clean :
	rm obj/*

test :
	python2 test.py

fclean : clean 
	rm $(CNAME)

re : clean all 

