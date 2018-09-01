char disp_buff[100][100];
int curr_start,curr_len;
int prev_row=0;
int t_files=0;
int list_dir(char *cwd);
int point=0;


void print_status(char *c){
    gotopoint(E.screenrows-1,1);
    write(STDOUT_FILENO, "\x1b[2K", 4);// clear line
    printf("%s\n",c );
}

void print_message(char *c){
    gotopoint(E.screenrows-3,1);
    write(STDOUT_FILENO, "\x1b[2K", 4);
    printf("%s\n",c );
}

void buff_clean(){
    int i;
    gotopoint(90,0);
    for(i=0;i<100;i++){
        clrstring(disp_buff[i]);
    }
    int prev_row=0;
    int t_files=0;
    int point=0;
}

void place_cursor(int row){
    if(row<val_row) return;
    if(row>val_row_end) return;
    gotopoint(prev_row,0);
    printf(" \n");
    gotopoint(row,0);
    prev_row=row;
    printf("▶\n");
}


void clrdisp(){
    int i;
    for(i=0;i<=val_num_rows;i++){
        gotopoint(val_row+i,val_col);
        write(STDOUT_FILENO, "\x1b[2K", 4);
    }
}

void print_buff(int start,int len){
    print_message("STATUS : Listing Directories");
    curr_start=start;
    curr_len=len;
    clrdisp();
    int i=start;
    int temp_row=0;
    while(temp_row<val_num_rows && strcmp(disp_buff[i], "")){
        place_cursor(temp_row+val_row);
        gotopoint(val_row+temp_row,val_col);
        printf("%d->|%s\n",i+1,disp_buff[i]);
        // usleep(100000);
        temp_row++;
        i++;
    }
    if(len>temp_row){
        gotopoint(val_row_end,val_col);
        printf("%d files remaining\n",len-temp_row+1);
        print_message("Press c to display more, k to display again, j to move here");
        char c = editorReadKey();
        if (c=='c')
        print_buff(i-1,len-i+1);
        if (c=='k')
        {   print_buff(0,t_files);
        }
    }
}

int list_dir(char *wd){
    buff_clean();
    struct stat FileAttrib;
    DIR *dir;
    struct dirent *ent;
    int i=0;char size[20];char f_path[1000];
    if ((dir = opendir (wd)) != NULL) {
        /* print all the files and directories within directory */
        while ((ent = readdir (dir)) != NULL) {
            strcpy(f_path,wd);
            strcat(f_path,"/");
            strcat(f_path,ent->d_name);
            stat(f_path, &FileAttrib);
            if(S_ISDIR(FileAttrib.st_mode)){
                strcat(disp_buff[i],"[DIR]");
            }
            strcat(disp_buff[i],ent->d_name);
            if (S_ISREG(FileAttrib.st_mode)){
                sprintf(size,"%.3f KB\n", FileAttrib.st_size/1000.0);
                strcat(disp_buff[i],"------------------------------>");
                strcat(disp_buff[i],size);
            }
            i++;
        }
        closedir (dir);
    }
    else {
        /* could not open directory */
        perror ("");
        return -1;
    }
    t_files=i;
    print_buff(0,t_files);
    return 0;
}

char* path_from_disp(){
    int d;
    if (strcmp(substring(disp_buff[point-1],0,5),"[DIR]")==0){
        d = strlen(disp_buff[point-1])-5;
        return substring(disp_buff[point-1],5,d);
    }
    df_flag=0;
    d = find_start_loc(disp_buff[point-1],"---------");
    return substring(disp_buff[point-1],0,d);
}
