int val_row;
int val_col=2;

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
    char c[E.screencols];
    for(i=0;i<E.screencols-2;i++)
        c[i]='-';
    printf("%s\n",c);
    gotopoint(E.screenrows-4,1);
    printf("%s\n",c);
    val_row = 3;

}

void exitscreen(){
    write(STDOUT_FILENO, "\x1b[2J", 4);
    write(STDOUT_FILENO, "\x1b[H", 3);
}

void print_status(char *c){
    gotopoint(E.screenrows-1,1);
    printf("%s\n",c );
}
