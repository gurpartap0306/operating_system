#include<unistd.h>
void main(){
	char buf[10];
	int count=10;
	read(0,buf,count);
	write(1,buf,sizeof(buf));
}
