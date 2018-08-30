#define CTRL_KEY(k) ((k) & 0x1f)

char editorReadKey() {
  int nread;
  char c;
  while ((nread = read(STDIN_FILENO, &c, 1)) != 1) {
    if (nread == -1 && errno != EAGAIN) die("read");
  }
  if (c == '\x1b') {
    char seq[3];
    if (read(STDIN_FILENO, &seq[0], 1) != 1) return '\x1b';
    if (read(STDIN_FILENO, &seq[1], 1) != 1) return '\x1b';
    if (seq[0] == '[') {
      switch (seq[1]) {
        case 'A': return 'w';
        case 'B': return 's';
        case 'C': return 'd';
        case 'D': return 'a';
      }
    }
    return '\x1b';
  }
  else {
    return c;
  }
}

void editorProcessKeypress() {
  char c = editorReadKey();
  switch (c) {
    case CTRL_KEY('q'):
      exit(0);
      break;
  }
}

void dispProcessKeypress() {
  char c = editorReadKey();
  switch (c) {
    case 'q':
      print_message("STATUS : quiting!");
      sleep(3);
      exitscreen();
      exit(0);
      break;
    case 'p':
      clrdisp();
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
      sleep(1);
      print_message("going to directory");
      break;
    case ':':
      print_status("COMMAND MODE");
      break;
    default:
      print_message("Press a valid Key");
      break;
  }
  usleep(500000);
  print_message("Press q to quit.");
}
