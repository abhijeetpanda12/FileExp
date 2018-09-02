char search_buff[100][1000];
int search_buff_l = 0;

void searchKeyPress();


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

void print_search(){
    clrdisp();
    int i;
    for (i=0;i<search_buff_l;i++){
        gotopoint(val_row+i,val_col);
        printf("%d---->%s\n",i+1,search_buff[i]);
    }
    searchKeyPress();
}


void searchKeyPress() {
  print_message("Press q to quit, right arrow to go back");
  char c = editorReadKey();
  switch (c) {
    case 'q':
      print_message("STATUS : quiting!");
      fclose(logg);
      exitscreen();
      exit(0);
      break;
    case 'a':
      print_message("LEFT arrow pressed");
      fprintf(logg,"left---%d <> %d ---->%s\n",path_array_point,present_path_point,path_array[present_path_point] );
        print_message(path_array[present_path_point]);
        strcpy(twd,path_array[present_path_point]);
        set_work_dir();
        list_dir(twd);
      break;
    default:
      searchKeyPress();
      break;
    }
    print_message("Press q to quit, right arrow to go back");
  }
