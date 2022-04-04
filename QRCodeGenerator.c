/*
    TAKE URL FROM USER AND PRINT THE QR CODE
    ALSO THE PROGRAMME GIVE COLOR QR CODE
*/
#include<stdio.h>
#include<string.h>


int qrcode(char* color){
    char input[200]={"\0"};


    printf("\e[0;37;40m\e[0;0H\e[2J");   //move the screen to top
    printf("Enter the URL: ");
    scanf("%s",input);                  // take a url
    printf("\e[2J\e[1;1H");             //move the screen to top
//=======================================================

   int len=strlen(input);     //find the url length

   if(len<=3){ //check  len is short then print error
        printf("String is too short. Not supported by available QR versions\n");
        return 0;
   }
   else if(len>=120){    //len is grater then print error
        printf("String is too long. Not supported by available QR versions\n");
        return 0;
   }

//======================================================
//define some variable wrt url length
    int c,box_size;
    if(len<=20){
        c=23-len;         //length of the hash string without first string and input url

        box_size=6;
   }
    else{
        c=131-len;        //length of the hash string without first string and input url

        box_size=12;

   }


//======================================================
//define some variable wrt length of the URL
    int n=0,bi_dig,p=0;
    char bi_co[1188]={"\0"};

    for(int k=0;k<c;k++){
        if(k%len==0){
            n=n+1;           //increase after len time loop
        }


        for(int t=8;t>=0;t--){           //change a character into binary
            bi_dig=(input[k%len]+n>>t)&1;
            if(bi_dig==0){
                bi_co[p]=48;           //digit is 0 then add 0 into the bi_code
            }
            else{
                bi_co[p]=49;           //digit is 1 then add 1 into the bi_code
            }
            p++;

        }
}

//======================================================
   //reverse binary code
   char tem[1188]={"\0"},hash_str[132]={"\0"};
   int l=0;
   for(int i=0;i<strlen(bi_co)/9;i++){
        for(int k=8;k>=0;k--){
            tem[l]=bi_co[strlen(bi_co)-1-(i*9)-k];       //add character to the tem in reverse order
            l++;
   }
}
    p=0;
    char bi_code[1296]={"\0"},bi;
    int bi_digit;
                   //add first string of the hash code

         for(int t=8;t>=0;t--){           //change a character into binary
            bi_digit=(50+len>>t)&1;
            if(bi_digit==0){
                bi_code[p]=48;           //digit is 0 then add 0 into the bi_code
            }
            else{
                bi_code[p]=49;           //digit is 1 then add 1 into the bi_code
            }
            p++;

        }



//======================================================
//change hash sting into binary code


    p=9;
    for(int m=0;m<strlen(input);m++){  //take every character in hash string
        bi=input[m];

        for(int t=8;t>=0;t--){           //change a character into binary
            bi_digit=(bi>>t)&1;
            if(bi_digit==0){
                bi_code[p]=48;           //digit is 0 then add 0 into the bi_code
            }
            else{
                bi_code[p]=49;           //digit is 1 then add 1 into the bi_code
            }
            p++;

        }

    }
    strcat(bi_code,tem);               //add tem string with bi_code string


//========================================================
//add all binary into the array
    char bi_array[3*box_size][3*box_size];
    int z=0;
    for(int i=0;i<box_size;i++){      //loop for insert position binary
        for(int j=0;j<box_size;j++){
            if((i==0&&j==0)||(i==0&&j==box_size-2)||(i==box_size-2&&j==0)){    //add part of the position array
                 int m=0;
                 for(int k=0;k<3;k++){
                    for(int l=0;l<3;l++){
                        bi_array[3*i+k][3*j+l]="111100101"[m];
                        m+=1;
                    }}}
            else if((i==0&&j==1)||(i==0&&j==box_size-1)||(i==box_size-2&&j==1)){  //add part of the position array
                 int m=0;
                 for(int k=0;k<3;k++){
                    for(int l=0;l<3;l++){
                        bi_array[3*i+k][3*j+l]="111001101"[m];
                        m+=1; }}}
            else if((i==1&&j==0)||(i==1&&j==box_size-2)||(i==box_size-1&&j==0)){   //add part of the position array
                 int m=0;
                 for(int k=0;k<3;k++){
                    for(int l=0;l<3;l++){
                        bi_array[3*i+k][3*j+l]="101100111"[m];
                        m+=1;}}}
            else if((i==1&&j==1)||(i==1&&j==box_size-1)||(i==box_size-1&&j==1)){     //add part of the position array
                 int m=0;
                 for(int k=0;k<3;k++){
                    for(int l=0;l<3;l++){
                        bi_array[3*i+k][3*j+l]="101001111"[m];
                        m+=1;}}}
    }

    }
    for(int i=2;i<box_size;i++){          //loop for insert binary code
        for(int j=2;j<box_size;j++){
            for(int k=0;k<3;k++){
                for(int l=0;l<3;l++){
                    bi_array[3*i+k][3*j+l]=bi_code[z];
                        z+=1;}}
        }
    }
    for(int i=0;i<2;i++){            //loop for insert binary code
        for(int j=2;j<box_size-2;j++){
            for(int k=0;k<3;k++){
                for(int l=0;l<3;l++){
                    bi_array[3*i+k][3*j+l]=bi_code[z];
                        z+=1;}}
        }
    }
    for(int i=2;i<box_size-2;i++){        //loop for insert binary code
        for(int j=0;j<2;j++){
            for(int k=0;k<3;k++){
                for(int l=0;l<3;l++){
                    bi_array[3*i+k][3*j+l]=bi_code[z];
                        z+=1;}}
        }
    }

//===========================================================================

    for(int i=0;i<3*box_size+2;i++){
        printf("\e[1;30;47m  ");      //print 1st white line
    }
    printf("\n\e[1;30;47m  ");        //print 2nd line first white box
    for(int i=0;i<3*box_size;i++){
        for(int j=0;j<3*box_size;j++){         //loop for all element in the array

            if(bi_array[i][j]=='0'){                //if 0 in the array print white box

                printf("\e[1;30;47m  ");
            }
            else{                              //if 1 in the arrat element then check color and print the color box
                if(strcmp(color,"black")==0){
                    printf("\e[1;30;40m  ");        //black color qrcode
                }
                else if(strcmp(color,"red")==0){
                    printf("\e[1;30;41m  ");        //red color qrcode
                }
                else if(strcmp(color,"green")==0){
                    printf("\e[1;30;42m  ");        //green color qrcode
                }
                else if(strcmp(color,"yellow")==0){
                    printf("\e[1;30;43m  ");        //yellow color qrcode
                }
                else if(strcmp(color,"blue")==0){
                    printf("\e[1;30;44m  ");        //blue color qrcode
                }
                else if(strcmp(color,"magenta")==0){
                    printf("\e[1;30;45m  ");        //magenta color qrcode
                }
                else if(strcmp(color,"cyan")==0){
                    printf("\e[1;30;46m  ");        //cyan color qrcode
                }
                else{                                         //if wrong color input print error
                    printf("Incorrect usage of arguments.\nusage :\n./proj.0 -c [black|red|green|yellow|blue|magenta|cyan]\n./proj.0 -h for the help about the program\n");

                }
            }

        }
        //printf("\x1b[0m" "\u2588\u2588\n\u2588\u2588");   //print last before row last white box
        printf("\e[1;30;47m  \n");
        printf("\e[1;30;47m  ");
    }
    for(int i=0;i<3*box_size+1;i++){                       //print last white line
        printf("\e[1;30;47m  ");
    }
   printf("\e[0m\n");
    return 0;

}
int main(int argc,char** argv) {  //take argument from console
    if(argc==1){                  //if one argument then goto black qrcode

        qrcode("black");
    }
    else if(argc==2||argc>3){             //if argument code then print error

        printf("Incorrect usage of arguments.\nusage :\n./proj.0 -c [black|red|green|yellow|blue|magenta|cyan]\n./proj.0 -h for the help about the program\n");

    }

    else if(strcmp(argv[1],"-c")==0){   //second argument is -c go to the qrcode function
        for(int k=0;argv[2][k]!='\0';k++){        //change capital to small character
            if(argv[2][k]>='A'&&argv[2][k]<='Z'){
                argv[2][k]=argv[2][k]+32;
            }
        }
           if(strcmp(argv[2],"black")==0||strcmp(argv[2],"green")==0||strcmp(argv[2],"red")==0||
           strcmp(argv[2],"cyan")==0||strcmp(argv[2],"magenta")==0||strcmp(argv[2],"yellow")==0||strcmp(argv[2],"blue")==0){    //check available color
            qrcode(argv[2]);  //argument pass with color
    }
        else //otherwise print error
        {
          printf("Incorrect usage of arguments.\nusage :\n./proj.0 -c [black|red|green|yellow|blue|magenta|cyan]\n./proj.0 -h for the help about the program\n");

        }
    }


   return 0;
}
