userlogin: wait_user_login.o access_to_mysql.o md5_encrypt.o
	gcc -g -Wall -std=gnu99 wait_user_login.o access_to_mysql.o md5_encrypt.o -lmysqlclient -lcrypto -o userlogin
wait_user_login.o: wait_user_login.c access_to_mysql.h
	gcc -g -Wall -std=gnu99 -c wait_user_login.c
access_to_mysql.o:access_to_mysql.c access_to_mysql.h md5_encrypt.h
	gcc -g -Wall -std=gnu99 -c access_to_mysql.c -I/usr/include/mysql -L/usr/lib/mysql
md5_encrypt.o:md5_encrypt.h md5_encrypt.c
	gcc -g -Wall -std=gnu99 -c md5_encrypt.c
.PHONY:clean
clean:
	-rm *.o userlogin

	
