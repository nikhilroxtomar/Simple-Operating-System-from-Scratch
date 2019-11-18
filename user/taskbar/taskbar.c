#include "../../include/print.h"

void taskbar(){
print("\n");
char* user="User: root";
clearLine(ROWS-1, ROWS, 0x4f);
printLine(ROWS-1, ROWS, user, 0x4f);
}
