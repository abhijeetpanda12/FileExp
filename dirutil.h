char cwd[1000];
char twd[1000];
void set_work_dir(){
    gotopoint(E.screenrows-2,1);
    write(STDOUT_FILENO, "\x1b[2K", 4);
    printf("Current working dir: %s\n", twd);
    gotopoint(E.screenrows-1,1);
    write(STDOUT_FILENO, "\x1b[2K", 4);
    printf("HOME working dir: %s\n", cwd);
}

int getwdir(){
   if (getcwd(cwd, sizeof(cwd)) == NULL)
       return -1;
   // printf("------------------------------------------\n");
   strcpy(twd,cwd);
   set_work_dir();
   return 0;
}

int dir_up(){
    if(strcmp(twd,cwd)==0){
        return -1;
    }
    int i;
    for(i=strlen(twd)-1;i>=0;i--){
        if(twd[i]=='/'){
            twd[i]='\0';
            break;
        }
        twd[i]='\0';
    }
    set_work_dir();
    return 1;
}
