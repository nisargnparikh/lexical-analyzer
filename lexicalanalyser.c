#include<stdio.h>
#include<string.h>
#include<stdlib.h>
// LEXICAL ANALYZER
void removeduplicate();
void final();
int Isiden(char ch); // is identifier
int Isop(char ch); // is constant
int Isdel(char ch); // is delimiter
int Iskey(char * str);// is keyword
void removeduplicate();

char op[8]={'+','-','*','/','=','<','>','%'};
char del[9]={'}','{',';','(',')','[',']',',','#'}; 
char *key[]={"auto","break","case","char","const","continue","default",
            "do","double","else","enum","extern","float","for","goto",
            "if","int","long","register","return","short","signed",
            "sizeof","static","struct","switch","typedef","union",
            "unsigned","void","volatile","while"};  

char *operato[]={"+","-","/","*","<",">","=","%","<=",">=","++"};

int idi=0,idj=0,k,opi=0,opj=0,deli=0,uqdi=0,uqidi=0,uqoperi=0,kdi=0,lite=0,ci=0;
int uqdeli[20],uqopi[20],uqideni[20],l=0,j;
char uqdel[20],uqiden[20][20],uqop[20][20],keyword[20][20];
char iden[20][20],oper[20][20],delim[20],literal[20][20],lit[20],constant[20][20];

void lexanalysis(char *str)
 {
   int i=0;
   while(str[i]!='\0')
    {
     if(Isiden(str[i]))     //for identifiers
       {
          while(Isiden(str[i]))
        {
            iden[idi][idj++]=str[i++];
        }
          iden[idi][idj]='\0';
          idi++;idj=0;
       }
      else
      if(str[i]=='"')         //for literals
         {
         lit[l++]=str[i];
         for(j=i+1;str[j]!='"';j++)
           {
            lit[l++]=str[j];
           }
         lit[l++]=str[j];lit[l]='\0';
         strcpy(literal[lite++],lit);
         i=j+1;
         }
      else
      if(Isop(str[i]))        // for operators
          {
         while(Isop(str[i]))
            {
             oper[opi][opj++]=str[i++];
            }
         oper[opi][opj]='\0';
         opi++;opj=0;
          }
       else
       if(Isdel(str[i]))     //for delimiters
          {
          while(Isdel(str[i]))
            {
              delim[deli++]=str[i++];
            }
           }
        else
           {
            i++;
        }
     }

   removeduplicate();
   final();
}

int Isiden(char ch)
 {
   if(isalpha(ch)||ch=='_'||isdigit(ch)||ch=='.')
   return 1;
   else
   return 0;
 }

int Isop(char ch)
 {
  int f=0,i;
  for(i=0;i<8&&!f;i++)
   {
    if(ch==op[i])
     f=1;
   }
 return f;
}

int Isdel(char ch)
 {
  int f=0,i;
  for(i=0;i<8&&!f;i++)
   {
    if(ch==del[i])
     f=1;
   }
 return f;
 }

int Iskey(char * str)
{
  int i,f=0;
  for(i=0;i<5;i++)
   {
    if(!strcmp(key[i],str))
      f=1;
    }
  return f;
}

void removeduplicate()
 {
   int i,j;
   for(i=0;i<20;i++)
    {
     uqdeli[i]=0;
     uqopi[i]=0;
     uqideni[i]=0;
    }
   for(i=1;i<deli+1;i++)  //removing duplicate delimiters
     {
       if(uqdeli[i-1]==0)
     {
           uqdel[uqdi++]=delim[i-1];
           for(j=i;j<deli;j++)
          {
               if(delim[i-1]==delim[j])
                uqdeli[j]=1;
          }
      }
     }

    for(i=1;i<idi+1;i++)  //removing duplicate  identifiers
       {
      if(uqideni[i-1]==0)
         {
        strcpy(uqiden[uqidi++],iden[i-1]);
        for(j=i;j<idi;j++)
         {
            if(!strcmp(iden[i-1],iden[j]))
               uqideni[j]=1;
         }
          }
    }

     for(i=1;i<opi+1;i++)  //removing duplicate  operators
     {
        if(uqopi[i-1]==0)
           {
           strcpy(uqop[uqoperi++],oper[i-1]);
           for(j=i;j<opi;j++)
             {
               if(!strcmp(oper[i-1],oper[j]))
                 uqopi[j]=1;
             }
           }
     }

 }
void final()
 {
  int i=0;
  idi=0;
  for(i=0;i<uqidi;i++)
   {
     if(Iskey(uqiden[i]))        //identifying keywords
     strcpy(keyword[kdi++],uqiden[i]);
     else
      if(isdigit(uqiden[i][0]))    //identifying constants
     strcpy(constant[ci++],uqiden[i]);
     else
     strcpy(iden[idi++],uqiden[i]);
   }

// printing the outputs

printf("\n\tdelimiter are : \n");
for(i=0;i<uqdi;i++)
printf("\t%c\n",uqdel[i]);

printf("\n\tOperators are : \n");
for(i=0;i<uqoperi;i++)
 {
 printf("\t");
 puts(uqop[i]);
 }

printf("\n\tIdentifiers are : \n");
for(i=0;i<idi;i++)
 {
  printf("\t");
  puts(iden[i]);
 }

printf("\n\tKeywords are : \n");
for(i=0;i<kdi;i++)
 {
  printf("\t");
  puts(keyword[i]);
 }

printf("\n\tConstants are :\n");
for(i=0;i<ci;i++)
  {
  printf("\t");
  puts(constant[i]);
  }

printf("\n\tLiterals are :\n");
for(i=0;i<lite;i++)
 {
   printf("\t");
   puts(literal[i]);
 }
}
void main()
{ char choice;
  char str[2000];
  FILE *fptr;
  char filename[100], c;
  int i=0;
  //clrscr();
  printf("\n\t\t\t_____LEXICAL ANALYZER_____\t\t\t");
  printf("\n\nHow would you like to analyse the program? ");
  printf("\n A.By entering filename of the given program to analyse ");
  printf("\n B.Typing the program on the screen");
  printf("\nEnter your choice: ");
  scanf("%c",&choice);
  
 
  
  if(choice == 'A')
    {
    printf("Enter the filename to open \n"); // file name : nisarg.txt
    scanf("%s", filename);

    // Open file
    fptr = fopen(filename, "r");
    if (fptr == NULL)
    {
        printf("Cannot open file \n");
        exit(0);
    }

    // Read contents from file
    c = fgetc(fptr);
    while (c != EOF)
    {
       //printf ("%c ", c);


        str[i]=c;
        c= fgetc(fptr);
        i++;
    }

    lexanalysis(str);

    fclose(fptr);
    }
 
  else if(choice == 'B')
    {printf("\n--->Important instruction : Press tab and then enter to end the program.");
        printf("\nEnter the program : ");
        //gets(str);
        scanf("%[^150\t]c",str); 
        lexanalysis(str);
    }



else
  //default:
      {

          exit(0);
      }
  }

    //lexanalysis(str);
  //getch();


/* //can use this type ofcode bock to give command line arguments
int main(int argc, char *argv[]) {
    FILE *filePtr;

    switch (argc) {
        case 1: // No parameters, use stdin
                // printf("NO argument provided\n");
                filePtr = stdin;
                break;

        case 2: // One parameter, use .lan file supplied
                if ( (filePtr = fopen(strcat(argv[1], ".lan"), "r")) == NULL ) {
                        printf("Cannot open input file.\n");
                        exit(1);
                }
                break;

        default:
                printf("Syntax: scanner [file] (.lan is implicit)\n");
                exit(0);
    }
} */
// visit this sites for more information
// http://www.coders-hub.com/2013/05/c-code-for-lexical-analysis.html#.WWPM4oiGPIV
// http://www.fresherscampus.com/programming/cdelimitres-and-c-keywords/238/
// http://www.thecrazyprogrammer.com/2017/02/lexical-analyzer-in-c.html
// http://www.c4learn.com/c-programs/accept-paragraph-using-scanf-in-c.html
// https://www.codeproject.com/articles/833206/lexical-analyzer-an-example

