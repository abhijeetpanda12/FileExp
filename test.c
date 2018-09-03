
#include <ctype.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ioctl.h>
#include <termios.h>
#include <unistd.h>
#include <dirent.h>
#include <limits.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <time.h>

char path_array[1000][1000];
int path_array_point=0;
int present_path_point=0;

// FILE *logg;


#include "termutil.h"
#include "util.h"
#include "dirutil.h"
#include "keyread.h"
#include "disputil.h"
#include "commandutil.h"
#include "searchutil.h"
#include "inpututil.h"

void file_attrib(){
    struct stat FileAttrib;
    if (stat("util.h", &FileAttrib) < 0)
        printf("File Error Message = %s\n", strerror(errno));
    else
        printf( "Permissions: %lld\n", FileAttrib.st_size );
}



int main(int argc, char** argv){
    // logg=fopen("log.txt", "w");
    enableRawMode();
    initscreen();
    print_status("NORMAL MODE");
    init_disp_var();
    print_message("Press q to exit.");
    // set working directory
    if(argc>1){
        strcpy(cwd,argv[1]);
        strcpy(twd,cwd);
        set_work_dir();
    }else{
        if (getwdir()==-1) exitscreen();
    }
    //--------
    strcpy(path_array[path_array_point],cwd);
    // fprintf(logg,"%d---->%s\n",path_array_point,path_array[path_array_point] );
    path_array_point++;
    //------------
    if(list_dir(cwd)==-1) {
        print_status("NOT A DIRECTORY");
    }
    print_message("Press q to exit, p to clear screen.");
    print_message(twd);
    while(1){
        dispProcessKeypress();
    }
    print_message("STATUS : quiting!");
    sleep(3);
    exitscreen();
    return 0;
}
