char command[1000];

void dispProcessKeypress();

int command_mode(){
  int i=0,gt=1;
  gotopoint(E.screenrows,0);
  write(STDOUT_FILENO, "\x1b[2K", 4); // clear line
  write(STDOUT_FILENO,":",1);
  // echomode();
  char cm;
  char pm[2];
  while(gt){
    cm = editorReadKey();
    switch(cm) {
      case 127:
        print_message("backspace pressed");
        gotopoint(E.screenrows,i+2);
        i--;
        command[i]='\0';
        write(STDOUT_FILENO, "\x1b[1D", 4);
        write(STDOUT_FILENO, " ", 1);
        write(STDOUT_FILENO, "\x1b[1D", 4);
        break;
      case '\n':
        command[i]='\0';
        gt=0;
        break;
      case '\x1b':
        gotopoint(E.screenrows,0);
        write(STDOUT_FILENO, "\x1b[2K", 4);
        print_status("NORMAL MODE");
        dispProcessKeypress();
        return 0;
      default:
        pm[0]=cm;
        pm[1]='\0';
        // write(STDOUT_FILENO, "\x1b[1C", 4);
        write(STDOUT_FILENO,pm,1);
        command[i]=cm;
        i++;
        break;
    }
  }
  break_command(command);
  if(strcmp(bmcd[0],"copy")==0){
    print_message("Do a copy");
    print_message(bmcd[1]);
    print_message(bmcd[2]);
    copy(bmcd[1],bmcd[2]);
  }
  else if(strcmp(bmcd[0],"move")==0){
    print_message("Do a move");
    copy(bmcd[1],bmcd[2]);
    remove(bmcd[1]);
  }
  else if(strcmp(bmcd[0],"move_dir")==0){
    print_message("Do a Directory move");
    copy_dir(bmcd[1],bmcd[2]);
    remove_dir(bmcd[1]);
  }
  else if(strcmp(bmcd[0],"copy_dir")==0){
    print_message("Do a directory copy");
    copy_dir(bmcd[1],bmcd[2]);
  }
  else if(strcmp(bmcd[0],"search")==0){
      print_message("Doing a search");
      sleep(1);
      print_message(bmcd[1]);
      search_buff_l=0;
      int i;
      if (search_dir(twd,bmcd[1])==1){}
      for(i=0;i<search_buff_l;i++){
          print_message(search_buff[i]);
          sleep(2);
        }
  }
  else if(strcmp(bmcd[0],"snapshot")==0){
    print_message("Do a snapshot");
    FILE *fpp  = fopen(bmcd[2], "w");
    fprintf(fpp, "%s\n",bmcd[1]);
    snap_dir(bmcd[1],fpp,1);
    fclose(fpp);
    print_message(bmcd[2]);
  }
  else if(strcmp(bmcd[0],"quit")==0){
      print_message("STATUS : quiting!");
      exitscreen();
      exit(0);
      }
  else if(strcmp(bmcd[0],"goto")==0){
      return 2;
  }
  else if(strcmp(bmcd[0],"create_file")==0){
      create_file(bmcd[1]);
  }
  else if(strcmp(bmcd[0],"delete")==0){
      print_message("Delete");
      remove(bmcd[1]);
  }
  else if(strcmp(bmcd[0],"delete_dir")==0){
      print_message("Delete a directory");
      remove_dir(bmcd[1]);
  }
  else
      print_message("nothing specified");
  if(command_mode()==0){}
    return 0;
}


void dispProcessKeypress() {
  print_message("Press q to quit");
  char c = editorReadKey();
  switch (c) {
    case 'q':
      print_message("STATUS : quiting!");
      fclose(logg);
      exitscreen();
      exit(0);
      break;
    case 'p':
      clrdisp();
      break;
    case 127:
      print_message("UP one directory");
      dir_up();
      //----
        strcpy(path_array[path_array_point],twd);
        fprintf(logg,"%d---->%s\n",path_array_point,path_array[path_array_point] );
        path_array_point++;
        present_path_point++;
        //----
      list_dir(twd);
      break;
    case 'h':
      if(list_dir(cwd)==-1) {
        print_status("NOT A DIRECTORY");
      }
      break;
    case 'w':
      print_message("UP arrow pressed");
      place_cursor(prev_row-1);
      break;
    case 'a':
      print_message("LEFT arrow pressed");
      present_path_point--;
      path_array_point--;
      fprintf(logg,"left---%d <> %d ---->%s\n",path_array_point,present_path_point,path_array[present_path_point] );
      if(present_path_point>=0){
        print_message(path_array[present_path_point]);
        strcpy(twd,path_array[present_path_point]);
        set_work_dir();
        list_dir(twd);
      }else{
        present_path_point++;
        path_array_point++;
      }
      break;
    case 'd':
      print_message("RIGHT arrow pressed");
      present_path_point++;
      path_array_point++;
      fprintf(logg,"right---%d <> %d ---->%s\n",path_array_point,present_path_point,path_array[present_path_point] );
      if(present_path_point<path_array_point && strcmp(path_array[present_path_point],"\0")!=0){
          print_message(path_array[present_path_point]);
          strcpy(twd,path_array[present_path_point]);
          set_work_dir();
          print_message(twd);
          list_dir(twd);
        }
      else{
        present_path_point--;
        path_array_point--;
      }
      break;
    case 's':
      print_message("DOWN arrow pressed");
      place_cursor(prev_row+1);
      break;
    case '\n':
      print_message("ENTER pressed");
      point=curr_start+prev_row-val_row+1;
      char pth[1000];
      strcpy(pth,path_from_disp());
      if(strcmp(pth,".")==0){
      }
      else if(strcmp(pth,"..")==0){
          dir_up();
          //----
          strcpy(path_array[path_array_point],twd);
          path_array[path_array_point][strlen(twd)]='\0';
          fprintf(logg,"%d---->%s\n",path_array_point,path_array[path_array_point] );
          path_array_point++;
          present_path_point++;
          //----
          list_dir(twd);
      }
      else if(df_flag){
        strcat(twd,"/");
        strcat(twd,pth);
        set_work_dir();
        //----
          strcpy(path_array[path_array_point],twd);
          fprintf(logg,"%d---->%s\n",path_array_point,path_array[path_array_point] );
          path_array_point++;
          present_path_point++;
        //----
        list_dir(twd);
      }
      else{
        print_message("IS A FILE");
        sleep(1);
        df_flag=1;
        char fpth[1000];
        strcpy(fpth,twd);
        strcat(fpth,"/");
        strcat(fpth,pth);
        strcat(fpth,"\0");
        print_message(fpth);
        int pid = fork();
        if (pid == 0) {
          // execl("/usr/bin/xdg-open", "xdg-open", fpth, (char *)0);
          execl("/usr/bin/open", "open", fpth, (char *)0);
          // execv("open",fpth);
          exit(1);
        }
      }
      break;
    case ':':
      print_status("COMMAND MODE");
      if(command_mode()==2){
        strcpy(twd,bmcd[1]);
        set_work_dir();
        //----
          strcpy(path_array[path_array_point],twd);
          fprintf(logg,"%d---->%s\n",path_array_point,path_array[path_array_point] );
          path_array_point++;
          present_path_point++;
        //----
        list_dir(twd);
      }
      break;
    default:
      print_message("Press a valid Key");
      break;
  }
  print_message("Press q to quit.");
}
