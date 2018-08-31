void dispProcessKeypress() {
  char c = editorReadKey();
  switch (c) {
    case 'q':
      print_message("STATUS : quiting!");
      exitscreen();
      exit(0);
      break;
    case 'p':
      clrdisp();
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
    case 's':
      print_message("DOWN arrow pressed");
      place_cursor(prev_row+1);
      break;
    case 'd':
      print_message("RIGHT arrow pressed");
      point=curr_start+prev_row-val_row+1;
      char pth[1000];
      strcpy(pth,path_from_disp());
      if(df_flag){
        strcat(twd,"/");
        strcat(twd,pth);
        list_dir(twd);
      }
      else{
        print_message("IS A FILE");
        sleep(1);
        df_flag=1;
      }
      break;
    case ':':
      print_status("COMMAND MODE");
      break;
    default:
      print_message("Press a valid Key");
      break;
  }
  // usleep(500000);
  print_message("Press q to quit.");
}
