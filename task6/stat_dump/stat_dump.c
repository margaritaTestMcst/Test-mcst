#include "stat_dump.h"
#include <assert.h>

__attribute__((always_inline))
static inline void  print_size_blocks_io(struct stat file_info);

static void print_file_mode(mode_t mode);

__attribute__((always_inline))
static inline void  print_device_inode_links(struct stat file_info);

static void print_file_access(struct stat file_info);

static void print_user_name(struct stat file_info);

static void print_time(const char* name, struct timespec ts);

void print_stat_info(const char* filename, struct stat file_info){
    assert(filename);

    printf("File: %s\n", filename);

    print_size_blocks_io(file_info);

    print_file_mode(file_info.st_mode);

    print_device_inode_links(file_info);

    print_file_access(file_info);

    print_user_name(file_info);

    print_time("Access", file_info.st_atim);
    print_time("Modify", file_info.st_mtim);
    print_time("Change", file_info.st_ctim);
}

static  inline void  print_size_blocks_io(struct stat file_info){
    printf("Size: %ld\nBlocks: %ld\nIO Block: %ld\n", file_info.st_size, file_info.st_blocks, file_info.st_blksize);
}

static void print_file_mode(mode_t mode){
    switch (mode & S_IFMT){
         case S_IFBLK:  printf("block device\n");       break;    
         case S_IFCHR:  printf("character device\n");   break; 
         case S_IFDIR:  printf("directory\n");          break; 
         case S_IFIFO:  printf("FIFO/pipe\n");          break; 
         case S_IFLNK:  printf("symlink\n");            break; 
         case S_IFREG:  printf("regular file\n");       break; 
         case S_IFSOCK: printf("socket\n");             break; 
         default:       printf("unknown?\n");           break; 
    }
}

static inline void  print_device_inode_links(struct stat file_info){
    printf("Device: %u,%u\nInode: %lu\nLinks: %lu\n",major(file_info.st_dev),minor(file_info.st_dev), file_info.st_ino, file_info.st_nlink);
}

static void print_file_access(struct stat file_info){
    char access[11] = {};

    switch(file_info.st_mode & S_IFMT){
        case S_IFBLK:  access[0] = 'b';     break;      
        case S_IFCHR:  access[0] = 'c';     break;  
        case S_IFDIR:  access[0] = 'd';     break;         
        case S_IFIFO:  access[0] = 'b';     break;       
        case S_IFLNK:  access[0] = 'l';     break;            
        case S_IFREG:  access[0] = '-';     break;   
        case S_IFSOCK: access[0] = 's';     break; 
        default:       access[0] = '-';     break;
    }

    access[1] = (file_info.st_mode & S_IRUSR) ? 'r' : '-';
    access[2] = (file_info.st_mode & S_IWUSR) ? 'w' : '-';
    access[3] = (file_info.st_mode & S_IXUSR) ? 'x' : '-';

    access[4] = (file_info.st_mode & S_IRGRP) ? 'r' : '-';
    access[5] = (file_info.st_mode & S_IWGRP) ? 'w' : '-';
    access[6] = (file_info.st_mode & S_IXGRP) ? 'x' : '-';

    access[7] = (file_info.st_mode & S_IROTH) ? 'r' : '-';
    access[8] = (file_info.st_mode & S_IWOTH) ? 'w' : '-';
    access[9] = (file_info.st_mode & S_IXOTH) ? 'x' : '-';

    printf("Access: (%04o/%s)\n", file_info.st_mode & 0777, access);

}

static void print_user_name(struct stat file_info){
    struct passwd* user = getpwuid(file_info.st_uid);
    struct group* group = getgrgid(file_info.st_gid);

    printf("Uid: (%5u/", file_info.st_uid);
    if(user) printf("%s", user->pw_name); 
    printf(")\n");

    printf("Gid: (%5u/", file_info.st_gid);
    if(group) printf("%s", group->gr_name); 
    printf(")\n");
}

static void print_time(const char* name, struct timespec ts){
    char buffer[1000] = {};
    char timezone[100] = {};
    struct tm* tm_info = localtime(&ts.tv_sec);

    if(tm_info){
        snprintf(buffer, sizeof(buffer), "%d-%02d-%02d %02d:%02d:%02d.%09ld", tm_info->tm_year + 1900, tm_info->tm_mon + 1, tm_info->tm_mday, tm_info->tm_hour, tm_info->tm_min, tm_info->tm_sec, ts.tv_nsec);
        strftime(timezone, sizeof(timezone), "%z", tm_info);
        printf("%s: %s %s\n", name, buffer, timezone);
    }
}