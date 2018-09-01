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
                            createDir(d_path);
                            if(copy_dir(s_path,d_path)==1){
                                // printf("-->\n");
                            }
                        }
                        else{
                            copy(s_path,d_path);
                        }
                    }
        }
    }
    return 1;
}
