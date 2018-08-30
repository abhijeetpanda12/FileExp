int val_row;
int val_row_end;
int val_num_rows;
int val_col;

void gotopoint(int x,int y){
    char buff[50];
    strcpy(buff,"");
    char temp[50];
    strcpy(temp,"\x1b[");
    strcat(buff,temp);
    char row[5];strcpy(row,"");
    char col[5];strcpy(col,"");
    sprintf(row,"%d",x);
    sprintf(col,"%d",y);
    strcat(buff,row);
    strcat(buff,";");
    strcat(buff,col);
    strcat(buff,"H");
    write(STDOUT_FILENO,buff,strlen(buff));
}

void initscreen(){
    write(STDOUT_FILENO, "\x1b[2J", 4);
    int x = getWindowSize(&E.screenrows, &E.screencols);
    gotopoint(1,E.screencols/2-7);
    printf("File Explorer \n");
    int i;
    char c[E.screencols-2];
    for(i=0;i<E.screencols-2;i++)
        c[i]='-';
    printf("%s\n",c);
    gotopoint(E.screenrows-4,1);
    printf("%s\n",c);
}

void exitscreen(){
    write(STDOUT_FILENO, "\x1b[2J", 4);
    write(STDOUT_FILENO, "\x1b[H", 3);
}


void init_disp_var() {
	E.cx = 0;
	E.cy = 0;
	E.rowoff = 0;
	E.numrows = 0;
	val_row=3;
	val_row_end=E.screenrows-5;
	val_col=2;
	val_num_rows = val_row_end - val_row;
  if (getWindowSize(&E.screenrows, &E.screencols) == -1) die("getWindowSize");
}
