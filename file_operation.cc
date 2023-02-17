/*
*  Date: 2020-2-17 21:30
*  Author: qiang
*  Description: file operation example
*  
*   wb : 
*     1. if file does not exist, creat file
*     2. clear the content of the exist file, then write new content
*   ab:
*     1. if file does not exist, creat file
*     2. append content to the end of exist file 
*   b: binary mode
*
*  complie:
*        gcc file_operation.cc -o file_opt
*/
#include <stdio.h>
#include <string.h>
#include <errno.h>

void WriteFile(const char *file)
{
    FILE *fp = fopen(file, "wb");
    if (!fp) {
        printf("open file to write failed\n");
        return;
    }
    char data[] = "hello world\n";
    int size = 12;
    fwrite(data, 1, size, fp);
    fclose(fp);
}

void ReadFile(const char *file)
{
    FILE *fp = fopen(file, "rb");
    if (!fp) {
        printf("open file to read failed \n");
        return;
    }
    char data[128];
    int count = 12;
    int ret;
    int size;
    while (1) {
        ret = fread(data, 1, count, fp);
        if (ret == 0) {
            printf("read file end\n");
            break;
        }
        data[count]='\0';
        printf("%d, %s",ret, data);
    }
}

int GetFileSize(const char *file)
{
    FILE *fp = fopen(file, "rb");
    if (!fp) {
        printf("open file to read failed \n");
        return -1;
    }
    fseek(fp,0L,SEEK_END);
    int size = ftell(fp);
    printf("file size: %d\n", size);
    return size;      
}

#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

void write_device_file(const char *file) 
{
    int fd;
    fd = open(file, O_CREAT | O_APPEND | O_RDWR , S_IRUSR | S_IWUSR);
    if (fd == -1) {
        printf("open device file failed, errno: %d\n", errno);
        return;
    }
    char data[] = "hello world";
    write(fd, data, strlen(data));
    close(fd);
}

void read_device_file(const char *file) 
{
    int fd;
    fd = open(file, O_RDONLY , S_IRUSR | S_IWUSR);
    if (fd == -1) {
        printf("open device file failed, errno: %d\n", errno);
        return;
    }
    char data[64];
    // memset(data, 0, 64);
    int size = 11;
    int r_size = read(fd, data, size);
    close(fd);
    data[size] = '\0';
    printf("read : %s, %d\n", data, r_size);
}

void WriteFmtFile(const char* file)
{   
    FILE *fp = fopen(file, "wb");
    if (!fp) {
        printf("open fmt file to write faild\n");
        return;
    }
    const char *data= "hello";
    int wSize = fprintf(fp, "%s %d %s", data, 10, "hehe");
    printf("write size == %d(bytes)\n", wSize);
    fclose(fp);
}

void ReadFmtFile(const char* file)
{
    FILE *fp = fopen(file, "rb");
    if (!fp) {
        printf("open fmt file to read faild\n");
        return;
    }
    char data[64];
    int num;
    memset(data, 0, 64);
    int rBlock = fscanf(fp, "%s %d %s", data, &num, &data[32]);
    printf("read size == %d, %s, %d, %s\n", rBlock, data, num, &data[32]);
    fclose(fp);
}

int main(int argc, char *argv[]) 
{   
    const char *file = "./test.log";
    WriteFile(file);

    int size = GetFileSize(file);
    printf("file size: %d(bytes)\n", size);

    ReadFile(file);
    printf("-----------------------------\n");
    
    const char *dev_file = "dev_test.log";
    write_device_file(dev_file);
    read_device_file(dev_file);
    printf("-----------------------------\n");

    const char *fmtFile = "fmt_test.log";
    WriteFmtFile(fmtFile);
    ReadFmtFile(fmtFile);
   
    return 0;
}
