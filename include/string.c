void reverse(char s[]){
	int c,i,j;
	for(i=0, j=strlen(s)-1;i<j;i++,j--){
		c=s[i];
		s[i]=s[j];
		s[j]=c;
	}
}

void int_to_ascii(int n, char str[]){
	int i, sign;
	if((sign=n)<0)	n=-n;
	i=0;
	do{
		str[i++]=n%10+'0';
	}while((n/=10)>0);
	if(sign <0)	str[i++]='-';
	str[i]='\0';
	reverse(str);	
}

int strlen(char s[]){
	int i=0;
	while(s[i]!='\0')	i++;
	return i++;	
}

int strcmp(char str1[], char str2[]){
    int i=0,flag=0;
   
    while(str1[i]!='\0' && str2[i]!='\0'){
         if(str1[i]!=str2[i]){
             flag=1;
             break;
         }
         i++;
    }

    if (flag==0 && str1[i]=='\0' && str2[i]=='\0')
         return 1;
    else
         return 0;
}
/*

int strcmp(char s1[], char s2[]) {
    int i;
    for (i = 0; s1[i] == s2[i]; i++) {
        if (s1[i] == '\0') return 0;
    }
    return s1[i] - s2[i];
}
*/
void concat(char* a, char* b, char* c){
	int len = strlen(a)+strlen(b);
	int i = 0;
	while(i < strlen(a)){
		c[i] = a[i];
		i++;
	}
	i = 0;
	while(i < strlen(b)){
		c[i+strlen(a)] = b[i];
		i++;
	}
	c[len] = '\0';
}

void concatc(char* a, char b, char* c){
	int len = strlen(a)+1;
	int i = 0;
	while(i < strlen(a)){
		c[i] = a[i];
		i++;
	}
	c[i] = b;
	c[len] = '\0';
}

void remchar(char* a, char* b){
	int i = 0;
	while(i < strlen(a)-1){
		b[i] = a[i];
		i++;
	}
	b[i] = '\0';
}

int toHex(char c){
	if(c == '0'){
		return 0x0;
	}if(c == '1'){
		return 0x1;
	}if(c == '2'){
		return 0x2;
	}if(c == '3'){
		return 0x3;
	}if(c == '4'){
		return 0x4;
	}if(c == '5'){
		return 0x5;
	}if(c == '6'){
		return 0x6;
	}if(c == '7'){
		return 0x7;
	}if(c == '8'){
		return 0x8;
	}if(c == '9'){
		return 0x9;
	}if(c == 'a' || c == 'A'){
		return 0xa;
	}if(c == 'b' || c == 'B'){
		return 0xb;
	}if(c == 'c' || c == 'C'){
		return 0xc;
	}if(c == 'd' || c == 'D'){
		return 0xd;
	}if(c == 'e' || c == 'E'){
		return 0xe;
	}if(c == 'f' || c == 'F'){
		return 0xf;
	}
	return -1;
}

int strncmp(char* a, char* b, int l){
   int c = 0;
   
   while (a[c] == b[c] && c < l) {
      c++;
   }
 
   if (c == l)
      return 1;
   else
      return 0;
}

int startswith(char* a, char* b){
	return strncmp(a,b,strlen(b));
}

void strcpy(char a[], char b[]){
	int i;
	for(i = 0; i < strlen(a); i++){
		b[i] = a[i];
	}
}

char tolower(char a){
	if(a >= 'A' && a <= 'Z')
		return a+32;
	return a;
}

void strtolower(char a[], char b[]){
	int i;	
	for(i = 0; i < strlen(a); i++){
		b[i] = tolower(a[i]);
	}
}

void subchar(char a[], char b[], int index){
	int i = index;
	while(i < strlen(a)){
		b[i-index] = a[i];
		i++;
	}
	b[i-index] = '\0';
}

void append(char s[], char n){
	int len=strlen(s);
	s[len]=n;
	s[len+1]='\0';
}

void backspace(char s[]){
	int len=strlen(s);
	s[len-1]='\0';
}

void memcpy(char* src, char* dst, int nbytes){
	int i;
	for(i=0;i<nbytes;i++)
	{
		*(dst+i)=*(src+i);
	}
}
