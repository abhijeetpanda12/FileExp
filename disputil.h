char disp_buff[100][100];
int prev_row=0;

void place_cursor(int row){
    gotopoint(prev_row,0);
    printf(" \n");
    gotopoint(row+val_row,0);
    prev_row=row+val_row;
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
    clrdisp();
    int i=start;
    int temp_row=0;
    while(temp_row<val_num_rows && strcmp(disp_buff[i], "")){
        place_cursor(temp_row);
        gotopoint(val_row+temp_row,val_col);
        printf("%d->|%s\n",i+1,disp_buff[i]);
        usleep(100000);
        temp_row++;
        i++;
    }
    // printf("%d,%d\n",i,len );
    if(len>temp_row){
        gotopoint(val_row_end,val_col);
        printf("%d files remaining\n",len-temp_row+1);
        sleep(3);
        print_buff(i-1,len-i+1);
    }
}

int list_dir(char *cwd){
    struct stat FileAttrib;
    DIR *dir;
    struct dirent *ent;
    int i=0;char size[10];
    if ((dir = opendir (cwd)) != NULL) {
        /* print all the files and directories within directory */
        while ((ent = readdir (dir)) != NULL) {
            strcpy(disp_buff[i],ent->d_name);
            if (ent->d_type!=4){
                stat(ent->d_name, &FileAttrib);
                strcat(disp_buff[i],"--------->");
                // sprintf(size,"%d",ent->d_type);
                sprintf(size,"%.3f KB",FileAttrib.st_size/1000.0);
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
    // printf("%d\n",i);
    // sleep(5);
    print_buff(0,i);
    return 0;
}
