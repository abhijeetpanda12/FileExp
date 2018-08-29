
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

#include "termutil.h"
#include "util.h"
#include "dirutil.h"
#include "disputil.h"




int main(int argc, char** argv){
    enableRawMode();
    initscreen();
    print_status("Normal mode");
    // set working directory
    if(argc>1){
        strcpy(cwd,argv[1]);
        set_work_dir();
    }else{
        if (getwdir()==-1) exitscreen();
    }

    if(list_dir(cwd)==-1) {
        print_status("NOT A DIRECTORY");
        return -1;
    }
    sleep(3);
    exitscreen();
    return 0;
}
