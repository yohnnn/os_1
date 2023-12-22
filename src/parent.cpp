#include <iostream>
#include <unistd.h>
#include <string>
#include <cstring>
#include <fstream>
#include <fcntl.h>

int main() {
    char c;
    const char* CHILD_PATH = "/home/yohn/labs/os_lab_1/build/child";
    std::string name = "/home/yohn/labs/os_lab_1/";
    if( read(STDIN_FILENO, &c, 1) == -1){
        perror("Reading error\n");
        return 1;
    }
    while(c != '\n'){
        name += c;
        if ( read(STDIN_FILENO, &c, 1) == -1){
            perror("Reading error\n");
            return 1;
        }
    }
    const char* file_name_1 = name.c_str();
    char c2;
    std::string name2 = "/home/yohn/labs/os_lab_1/";
    if( read(STDIN_FILENO, &c2, 1) == -1){
        perror("Reading error\n");
        return 1;
    }
    while(c2 != '\n'){
        name2 += c2;
        if ( read(STDIN_FILENO, &c2, 1) == -1){
            perror("Reading error\n");
            return 1;
        }
    }
    const char* file_name_2 = name2.c_str();
    int file_1 = open(file_name_1, O_WRONLY | O_CREAT | O_TRUNC, 0777);
    int file_2 = open(file_name_2, O_WRONLY | O_CREAT | O_TRUNC, 0777);

    if (file_1 == -1){
        perror("error");
        return 1;
    }
    if (file_2 == -1){
        perror("error");
        return 1;
    }
    int fd1[2];
    if (pipe(fd1) == -1){
        perror("Ошибка создания pipe1");
        return 1;
    }
    int fd2[2];
    if (pipe(fd2) == -1){
        perror("Ошибка создания pipe2");
        return 1;
    }
    pid_t pid1 = fork();
    if (pid1 == -1){
        perror("Ошибка создания pid1");
        return 1;
    }
    else if(pid1 > 0){
        pid_t pid2 = fork();
        if (pid2 == -1){
            perror("Ошибка создания pid2");
            return 1;
        }   
        else if(pid2 > 0){
            std::string stroka = "";
            char t;
            if( read(STDIN_FILENO, &t, 1) == -1){
                perror("Reading error\n");
                return 1;
            }
            while(t != '\n'){
                stroka += t;
                if ( read(STDIN_FILENO, &t, 1) == -1){
                    perror("Reading error\n");
                    return 1;
                }
            }
            int len = stroka.size();
            const char * str = stroka.c_str();
            if (len <= 10){
                write(fd1[1], str, len);
            }
            else{
                write(fd2[1], str, len);
            }

            char * c = new char('\n');
     
            write(fd1[1], c, 1);
            write(fd2[1], c, 1);

            close(file_1);
            close(file_2);
            close(fd1[1]);
            close(fd1[0]);
            close(fd2[1]);
            close(fd2[0]);
        }
        else{
            close(fd2[1]);
            close(fd1[1]);
            close(fd1[0]);
            close(file_1);
            if (dup2(file_2, STDOUT_FILENO) == -1)
            {
                return -1;
            }
            close(file_2);

            if (dup2(fd2[0], STDIN_FILENO) == -1)
            {
                return -1;
            }
            close(fd2[0]);

            execlp(CHILD_PATH, CHILD_PATH, NULL);
            return 0;
        }  
    }
    else{
        close(fd1[1]);
        close(fd2[1]);
        close(fd2[0]);
        close(file_2);
        if (dup2(file_1, STDOUT_FILENO) == -1){
            return -1;
        }
        close(file_1);

        if (dup2(fd1[0], STDIN_FILENO) == -1){
            return -1;
        }
        close(fd1[0]);

        execlp(CHILD_PATH, CHILD_PATH, NULL);
        return 0;
    }


    return 0;
}