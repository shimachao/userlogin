#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include "access_to_mysql.h"
#include "mysql.h"

MYSQL my_connection;

int init_connect_mysql()
{
	mysql_init(&my_connection);
	if(NULL == mysql_real_connect(&my_connection,"localhost","root",
									"to writ","test",0,NULL,0))
	{
		fprintf(stderr,"connection failed\n");
		if(mysql_error(&my_connection))
		{
			fprintf(stderr,"connection error %d: %s\n",
							mysql_errno(&my_connection),
							mysql_error(&my_connection));
		}
		return -1;
	}
	return 0;
}

int user_verify(char *email,char *password)
{	
	assert(email != NULL && password != NULL) ;
	
	char query[512] = {"SELECT user_pass FROM test where user_email = \0"};
	strcat(query,email);
	int res = mysql_query(&my_connection,query);
	if(0 != res)
	{
		fprintf(stderr,"mysql query error\n");
		if(mysql_error(&my_connection))
		{
			fprintf(stderr,"mysql query error %d: %s\n",
							mysql_errno(&my_connection),
							mysql_error(&my_connection));
		}
		return -1;
	}
	MYSQL_RES *res_ptr = mysql_store_result(&my_connection);
	if(NULL == res_ptr)
	{
		if(0 == mysql_field_count(&my_connection))
		{
		}
		else
		{	
			fprintf(stderr,"mysql_store_result error\n");
			if(mysql_error(&my_connection))
			{
				fprintf(stderr,"mysql error %d: %s\n",
								mysql_errno(&my_connection),
								mysql_error(&my_connection));
			}
		}
		return -1;
	}
	MYSQL_ROW sqlrow = mysql_fetch_row(res_ptr);
	if(strcmp(password,sqlrow[0]))
	{
		return 0;
	}
	return -1;
}
