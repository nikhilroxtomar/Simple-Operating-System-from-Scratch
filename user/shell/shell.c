#include "shell.h"
#include "../../include/print.h"
#include "../../include/string.h"

#define NULL 0
char* cmdline="shell:# ";

void help(){
	print("Basic Commands:\n");
	print("about\t-\tabout the system\n");
	print("clear\t-\tclear the screen\n");
	print("help\t-\tbasic help\n");
}

void shell(){
	char *cmd;
	cmd[0]='\n';
	while(1){
	print_color(cmdline, 0xf9);
	cmd=(char*)readStr();
	print("\n");
	if(strcmp("\0", cmd)==1){ }
		
	else if(strcmp("help", cmd)==1){
		help();
		cmd[0]='\n';	
	}
	
	else if(strcmp("clear", cmd)==1){
		clear_();
		cmd[0]='\n';	
	}
	else if(strcmp("about", cmd)==1){
		print("Maya is an x86 based OS\n");			
		cmd[0]='\n';
	}

	else{
		print("command not found\n");
		cmd[0]='\n';
	}
}
}

