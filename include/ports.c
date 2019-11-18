
void outb(unsigned short port, unsigned char data){
asm volatile("outb %0, %1": :"a"(data), "dN"(port));
} 

unsigned char inb(unsigned short port){
	unsigned short ret;
	asm volatile("inw %1, %0" : "=a"(ret) : "dN"(port));
	return ret;
}
