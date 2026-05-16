#include <time.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/sysmacros.h>
#include <unistd.h>
#include <stdio.h>
#include <pwd.h>
#include <grp.h>

void print_stat_info(const char* filename, struct stat file_info);

int main(int argc,char* argv[]){
    if(argc != 2){
        fprintf(stderr, "Usage: <program> <file>\n");
        return 1;
    }

    struct stat file_info = {};

    if(stat(argv[1], &file_info) == -1){
        perror("Stat error");
        return 1;
    }

    print_stat_info(argv[1], file_info);


    return 0;
}

const char* choose_file_mode(mode_t mode){
    switch (mode & S_IFMT){
         case S_IFBLK:  return "block device";           
         case S_IFCHR:  return "character device";    
         case S_IFDIR:  return "directory";          
         case S_IFIFO:  return "FIFO/pipe";       
         case S_IFLNK:  return "symlink";            
         case S_IFREG:  return "regular file";       
         case S_IFSOCK: return "socket";           
         default:       return "unknown?";            
    }
    return "unknown?";
}

void choose_file_access(mode_t mode, char access[11]){
    switch(mode & S_IFMT){
        case S_IFBLK:  access[0] = 'b';     break;      
        case S_IFCHR:  access[0] = 'c';     break;  
        case S_IFDIR:  access[0] = 'd';     break;         
        case S_IFIFO:  access[0] = 'b';     break;       
        case S_IFLNK:  access[0] = 'l';     break;            
        case S_IFREG:  access[0] = '-';     break;   
        case S_IFSOCK: access[0] = 's';     break; 
        default:       access[0] = '-';     break;
    }

    access[1] = (mode & S_IRUSR) ? 'r' : '-';
    access[2] = (mode & S_IWUSR) ? 'w' : '-';
    access[3] = (mode & S_IXUSR) ? 'x' : '-';

    access[4] = (mode & S_IRGRP) ? 'r' : '-';
    access[5] = (mode & S_IWGRP) ? 'w' : '-';
    access[6] = (mode & S_IXGRP) ? 'x' : '-';

    access[7] = (mode & S_IROTH) ? 'r' : '-';
    access[8] = (mode & S_IWOTH) ? 'w' : '-';
    access[9] = (mode & S_IXOTH) ? 'x' : '-';

    access[10] = '\0';

}

void choose_and_print_user_name(struct stat file_info){
    struct passwd* user = getpwuid(file_info.st_uid);
    struct group* group = getgrgid(file_info.st_gid);

    printf("Uid: (%5u/", file_info.st_uid);
    if(user) printf("%s", user->pw_name); 
    printf(")\n");

    printf("Gid: (%5u/", file_info.st_gid);
    if(group) printf("%s", group->gr_name); 
    printf(")\n");
}

void print_time(const char* name, struct timespec ts){
    char buffer[1000] = {};
    char timezone[100] = {};
    struct tm* tm_info = localtime(&ts.tv_sec);

    if(tm_info){
        snprintf(buffer, sizeof(buffer), "%d-%02d-%02d %02d:%02d:%02d.%09ld", tm_info->tm_year + 1900, tm_info->tm_mon + 1, tm_info->tm_mday, tm_info->tm_hour, tm_info->tm_min, tm_info->tm_sec, ts.tv_nsec);
        strftime(timezone, sizeof(timezone), "%z", tm_info);
        printf("%s: %s %s\n", name, buffer, timezone);
    }
}

void print_stat_info(const char* filename, struct stat file_info){
    printf("File: %s\n", filename);

    printf("Size: %ld\n", file_info.st_size);
    printf("Blocks: %ld\n", file_info.st_blocks);
    printf("IO Block: %ld\n", file_info.st_blksize);
    printf("%s\n", choose_file_mode(file_info.st_mode));

    printf("Device: %d,%d\n",major(file_info.st_dev),minor(file_info.st_dev));
    printf("Inode: %ld\n", file_info.st_ino);
    printf("Links: %ld\n", file_info.st_nlink);

    char access[11] = {};
    choose_file_access(file_info.st_mode, access);
    printf("Access: (%04o/%s)\n", file_info.st_mode & 0777, access);

    choose_and_print_user_name(file_info);

    print_time("Access", file_info.st_atim);
    print_time("Modify", file_info.st_mtim);
    print_time("Change", file_info.st_ctim);
}
