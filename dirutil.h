char cwd[1000];
char twd[1000];
void set_work_dir(){
    gotopoint(E.screenrows-2,1);
    printf("Current working dir: %s\n", twd);
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
