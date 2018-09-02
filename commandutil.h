char search_buff[100][1000];
int search_buff_l = 0;

void create_file(char * file_name){
    FILE *fptr;
    fptr = fopen(file_name, "w");
    fclose(fptr);
}

void createDir(char* d) {
    mkdir(d, 0777);
}

void copy(char *s, char *d)
{
    FILE *fp1, *fp2;
    char ch;
    int pos;

    if ((fp1 = fopen(s,"r")) == NULL)
    {
        printf("\nFile cannot be opened");
        return;
    }
    fp2 = fopen(d, "w");
    fseek(fp1, 0L, SEEK_END); // file pointer at end of file
    pos = ftell(fp1);
    fseek(fp1, 0L, SEEK_SET); // file pointer set at start
    while (pos--)
    {
        ch = fgetc(fp1);  // copying file character by character
        fputc(ch, fp2);
    }
    fclose (fp1);
    fclose (fp2);


}

int copy_dir(char *s_dir, char *d_dir){
    char s_path[1000];
    char d_path[1000];
    createDir(d_dir);
    struct stat FileAttrib;
    DIR *dir;
    struct dirent *ent;
    int i=0;char size[20];char f_path[1000];
    if ((dir = opendir (s_dir)) != NULL) {
        while ((ent = readdir (dir)) != NULL){
                if(strcmp(ent->d_name,".")!=0 && strcmp(ent->d_name,"..")!=0){
                        strcpy(d_path,d_dir);
                        strcat(d_path,"/");
                        strcat(d_path,ent->d_name);
                        strcat(d_path,"\0");

                        strcpy(s_path,s_dir);
                        strcat(s_path,"/");
                        strcat(s_path,ent->d_name);
                        strcat(s_path,"\0");
                        stat(s_path, &FileAttrib);
                        if (S_ISDIR(FileAttrib.st_mode)){
                            // createDir(d_path);
                            if(copy_dir(s_path,d_path)==1){
                                // printf("-->\n");
                            }
                        }
                        else{
                            copy(s_path,d_path);
                        }
                    }
        }
    closedir(dir);
    }

    return 1;
}

int remove_dir(char *s_dir){
    char s_path[1000];
    struct stat FileAttrib;
    DIR *dir;
    struct dirent *ent;
    int i=0;char size[20];char f_path[1000];
    if ((dir = opendir (s_dir)) != NULL) {
        while ((ent = readdir (dir)) != NULL){
                if(strcmp(ent->d_name,".")!=0 && strcmp(ent->d_name,"..")!=0){
                        strcpy(s_path,s_dir);
                        strcat(s_path,"/");
                        strcat(s_path,ent->d_name);
                        strcat(s_path,"\0");
                        stat(s_path, &FileAttrib);
                        if (S_ISDIR(FileAttrib.st_mode)){
                            if (remove_dir(s_path)!=1){
                                print_message("error\n");
                            }
                        }
                        else{
                            remove(s_path);
                        }
                    }
        }
    closedir(dir);
    rmdir(s_dir);
    }
    // printf("%s\n",s_dir);
    return 1;
}


int search_dir(char *s_dir, char *key){
    char s_path[1000];
    struct stat FileAttrib;
    DIR *dir;
    struct dirent *ent;
    int i=0;
    if ((dir = opendir (s_dir)) != NULL) {
        while ((ent = readdir (dir)) != NULL){
                if(strcmp(ent->d_name,".")!=0 && strcmp(ent->d_name,"..")!=0){
                        strcpy(s_path,s_dir);
                        strcat(s_path,"/");
                        strcat(s_path,ent->d_name);
                        strcat(s_path,"\0");
                        stat(s_path, &FileAttrib);
                        if(strcmp(ent->d_name,key)==0){
                                strcpy(search_buff[search_buff_l],s_path);
                                search_buff[search_buff_l][strlen(s_path)]='\0';
                                search_buff_l++;
                        }
                        if (S_ISDIR(FileAttrib.st_mode)){
                            search_dir(s_path,key);
                        }
                    }
        }
    closedir(dir);
    }
    return 1;
}
