int val_row;
int val_row_end;
int val_num_rows;
int val_col;
char c[1000];
int df_flag=1;
char bmcd[100][1000];
int bmcd_l;

void clrstring(char *cddd){
    int i;
    for(i=0;i<strlen(cddd);i++)
        cddd[i]='\0';
}

void break_command(char * cmd){
    char t[1000];
    int i,pp=0,j=0;
    for (i=0;i<strlen(cmd);i++){
        if (cmd[i]==' ' || cmd[i] == '\0'){
            bmcd[j][pp]='\0';
            j++;
            pp=0;
        }
       else{
        bmcd[j][pp]=cmd[i];
        pp++;
       }
    }
    bmcd[j][pp]='\0';
    bmcd_l=j;
}

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

char* substring(char* s,int srt, int len){
    int i,j;
    clrstring(c);
    if (len>strlen(s)) return s;
    j=0;
    for(i=srt;i<srt+len;i++){
        c[j] = s[i];
        j++;
    }
    c[j]='\0';
    return c;
}

int find_start_loc(char *s, char* cmp){
    int l1=strlen(s);
    int l2=strlen(cmp);
    if (l2>l1) return -1;
    int i,j,flg;
    for(i=0;i<l1;i++){
        flg=0;
        for(j=0;j<l2;j++){
            if(s[i+j]!=cmp[j]){
                flg=1;
            }
        }
        if (flg==0) return i;
    }
    return -1;
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
