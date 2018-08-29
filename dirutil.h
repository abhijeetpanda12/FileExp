char cwd[1000];
void set_work_dir(){
    gotopoint(E.screenrows-3,1);
    printf("Current working dir: %s\n", cwd);
}

int getwdir(){
    // char *getcwd(char *buf, size_t size);
    // char cwd[1000];
   if (getcwd(cwd, sizeof(cwd)) == NULL)
       return -1;
   set_work_dir();
   return 0;
}
