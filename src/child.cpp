#include <iostream>
#include <cstring>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <algorithm> 

void reverse_str(char* str){
    char tempo;
    int length = strlen(str);
    for (size_t i = 0; i < length; i++)
    {
        tempo = str[length - 1];
        str[length - 1] = str[i];
        str[i] = tempo;
        length--;
    }
}

int main()
{
    char a;
    
    read(0, &a, 1);
    std::string s = "";
    while (a != '\n'){
        s += a;
        read(0, &a, 1);
    }
    reverse(s.begin(), s.end());
    int len = s.length();\
    char output[100];
    sprintf(output, "%s\n", s.c_str());

    write(1, &output, len + 1);

    return 0;
}
