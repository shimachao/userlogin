#include "md5_encrypt.h"
#include <stdio.h>
#include <stdlib.h>
#include <openssl/md5.h>
#include <string.h>
#include <strings.h>
char *md5_encrypt(const unsigned char *str)
{
	unsigned char md[16];
	char tmp[3] = {'\0'};
	char *buf = (char*)malloc(33);
	bzero(buf,33);
	MD5(str,strlen(str),md);
	int i = 0;
	for(i=0;i<16;i++)
	{
		sprintf(tmp,"%2.2x",md[i]);
		strcat(buf,tmp);
	}
	return buf;
}

