/*******************************************************************
(C) 2011 by Radu Stefan
radu124@gmail.com

This program is free software; you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation; version 2 of the License.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.
*******************************************************************/

#include "confrw.h"
#include "message.h"
#include "verbosity.h"

void confread_GLfloat(char *&s, GLfloat &v) { v=atof(s); DBG(CONFIG," value GLfloat %f (from:%s)\n" ,v ,s);}
void confread_int(char *&s, int &v)         { v=atoi(s); DBG(CONFIG," value int %d (from:%s)\n" ,v ,s);}
void confread_string(char *&s, string &v)   { v=string(s); DBG(CONFIG," value string '%s'\n" ,v);}

int hexdigit(char c)
{
	if (c>='0' && c<='9') return c-'0';
	if (c>='a' && c<='f') return c-'a'+10;
	if (c>='A' && c<='F') return c-'A'+10;
	return 0;
}

int hexbyte(const char *c)
{
	return 16*hexdigit(c[0])+hexdigit(c[1]);
}

void confread_mcolor(char *&s, mcolor &v)
{
	const char *p=s;
	if (p[0]=='#') p++;
	if (strlen(s)<6)
	{
		v=C_WHITE;
		return;
	}
	v.Red   = hexbyte(p+0)/255.0;
	v.Green = hexbyte(p+2)/255.0;
	v.Blue  = hexbyte(p+4)/255.0;
	v.Alpha = 1;
	if (strlen(s)>7) v.Alpha = hexbyte(p+6)/255.0;
	DBG(CONFIG," color(%f,%f,%f,%f) from:%s\n", v.Red, v.Green, v.Blue, v.Alpha, s);
}

int multiplechoice(const char *s, const char *choices)
{
	const char *cc=choices;
	int len;
	int cnt=0;
	const char *nc;
	while (1)
	{
		nc=strchr(cc,',');
		if (nc) {
			len=nc-cc;
		} else len=strlen(cc);
		//DBG(CONFIG,"MULTICHOICE %s %d -match:%s\n" &cc &len &s);
		if (0==strncmp(cc,s,len)) return cnt;
		cnt++;
		if (!nc) break;
		cc=nc+1;
	}
	return 0;
}


