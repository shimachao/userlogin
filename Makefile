userlogin: wait_user_login.o access_to_mysql.o
	gcc -Wall -std=gnu99 wait_user_login.o access_to_mysql.o -lmysqlclient -o userlogin
wait_user_login.o: wait_user_login.c access_to_mysql.h
	gcc -Wall -std=gnu99 -c wait_user_login.c
access_to_mysql.o:access_to_mysql.h access_to_mysql.h
	gcc -Wall -std=gnu99 -c access_to_mysql.c -I/usr/include/mysql -L/usr/lib/mysql
.PHONY:clean
clean:
	-rm *.o userlogin

	
