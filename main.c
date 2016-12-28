#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

struct directory
{
    char x[10];
    struct directory *_prev;
    struct directory *_firstChield;
    struct directory *_nextChield;
};

char a[10][10]={"/root","/usr","/local","/sbin","/lib","/dev","/bin","/etc","/passwd","/group"};
struct directory *root=NULL;
struct directory *ilk=NULL;
struct directory *createDirectory(struct directory *temp,int x);
void createFolder();
void createFile();
struct directory *cd(struct directory *temp);
struct directory *cdUp(struct directory *temp);
void pwd(struct directory *temp);
void ls();
void information();
void rmfolder();
void rmfile();
void vim();

int main()
{
    char _choose[20];
    struct directory *root=NULL;
    int i;

    information();

    for (i=0; i<10; i++)
    {
        root = createDirectory(root,i);
    }

    while(1)
    {
        printf("root@ereborlugimli:~$ ");
        scanf("%s",_choose);

        if (strcmp(_choose,"cd")==0)
        {
            root=cd(root);
        }
        else if (strcmp(_choose,"pwd")==0)
        {
            pwd(root);
        }
        else if (strcmp(_choose,"cd../")==0)
        {
            root=cdUp(root);
        }
        else if (strcmp(_choose,"ls")==0)
        {
            ls();
        }
        else if (strcmp(_choose,"rm-f/")==0) //dizin siler
        {
            rmfolder();
        }
        else if (strcmp(_choose,"rm-f")==0) //dosya siler
        {
            rmfile();
        }
        else if (strcmp(_choose,"touch")==0)
        {
            createFile();
        }
        else if (strcmp(_choose,"mkdir")==0)
        {
            createFolder();
        }
        else if (strcmp(_choose,"vim")==0)
        {
            vim();
        }
        else if (strcmp(_choose,"help")==0)
        {
            information();
        }
        else
        {
            printf("command not found\n");
        }

    }
}
void information()
{
    printf("root@ereborlugimli:~$ help\n\n");
    printf("[HELP]\n\nName\n\tHelp\nDescription\n\n\tHi ! Welcome to the help section.\n\n");
    printf("\t[ cd ] -- Go to most top directory\n");
    printf("\t[ pwd ] -- Lists the current directory\n");
    printf("\t[ cd../ ] -- Go to  top directory\n");
    printf("\t[ ls ] -- List directories\n");
    printf("\t[ rm-f/ ] -- Delete folder\n");
    printf("\t[ rm-f ] -- Delete file\n");
    printf("\t[ touch ] -- Creating a file\n");
    printf("\t[ mkdir ] -- Creating a folder\n\n");
    printf("\t[ vim ] -- Write to file\n\n");
    printf("If you type help, you can see help options again\n\n");
}
struct directory * createDirectory(struct directory *temp,int x)
{
    struct directory *temp2 = (struct directory*)malloc(sizeof(struct directory));

    if (temp != NULL)
        {
            sprintf(temp2->x,"%s",a[x]);
            temp2->_firstChield=NULL;
            temp2->_nextChield=NULL;

            switch(x) //1den 9 kadar 9 dahil
            {
                case 1: //usr
                        temp->_firstChield =temp2;
                        temp->_firstChield->_prev = temp;
                        break;
                case 2: //dev
                        temp->_firstChield->_nextChield =temp2;
                        temp->_firstChield->_nextChield->_prev = temp;
                        break;
                case 3: //bin
                        temp->_firstChield->_nextChield->_nextChield =temp2;
                        temp->_firstChield->_nextChield->_nextChield->_prev=temp;
                        break;
                case 4: //etc
                        temp->_firstChield->_nextChield->_nextChield->_nextChield =temp2;
                        temp->_firstChield->_nextChield->_nextChield->_nextChield->_prev = temp;
                        break;
                case 5: //local
                        temp->_firstChield->_firstChield =temp2;
                        temp->_firstChield->_firstChield->_prev = temp->_firstChield;
                        break;
                case 6: //sbin
                        temp->_firstChield->_firstChield->_nextChield =temp2;
                        temp->_firstChield->_firstChield->_nextChield->_prev =temp->_firstChield;
                        break;
                case 7: //lib
                        temp->_firstChield->_firstChield->_nextChield->_nextChield =temp2;
                        temp->_firstChield->_firstChield->_nextChield->_nextChield->_prev = temp->_firstChield;
                        break;
                case 8: //passwd
                        temp->_firstChield->_nextChield->_nextChield->_nextChield->_firstChield =temp2;
                        temp->_firstChield->_nextChield->_nextChield->_nextChield->_firstChield->_prev = temp->_firstChield->_nextChield->_nextChield->_nextChield;
                        break;
                case 9: //group
                        temp->_firstChield->_nextChield->_nextChield->_nextChield->_firstChield->_nextChield =temp2;
                        temp->_firstChield->_nextChield->_nextChield->_nextChield->_firstChield->_nextChield->_prev = temp->_firstChield->_nextChield->_nextChield->_nextChield;
                        break;
            }
                mkdir(a[x],777);
                        //burda klasörü oluşturmalı
            return ilk;
        }
        else
        {
            temp = (struct directory*)malloc(sizeof(struct directory));
            sprintf(temp->x,"%s",a[x]);
            temp->_prev=NULL;
            temp->_firstChield=NULL;
            temp->_nextChield=NULL;
            ilk=temp;
            mkdir(a[x],777);
            return ilk;
        }

}
void rmfolder()
{
    char folderName[25];
    printf("Enter the folder name : ");
    scanf("%s",folderName);
    int c=rmdir(folderName);
    if (c==1)
    {
        printf("rm: cannot remove ‘%s’: No such file or directory",folderName);
    }
}
void rmfile()
{
    char fileName[25];
    printf("Enter the file name : ");
    scanf("%s",fileName);
    int ret=remove(fileName);
    if (ret !=0 )
    {
        printf("rm: cannot remove ‘%s’: No such file or directory",fileName);
    }
}
void vim()
{
    char fileName[25];
    printf("Enter the file name : ");
    scanf("%s",fileName);

    FILE *dosya = fopen(fileName,"w");
    if (dosya == NULL)
    {
        printf("command not found\n");
        exit(1);
    }
    char sentence[255];
    printf("Enter a sentence : ");
    scanf("%s",sentence);
    fprintf(dosya,"%s",sentence);
    fclose(dosya);
}
struct directory * cd(struct directory *temp) //yarım çünkü cd /etc/passwd için ayrı bir fonksiyon lazım
{
    if (temp->_firstChield != NULL)
    {
        temp=temp->_firstChield;
    }
    else if (temp->_nextChield != NULL )
    {
        temp=temp->_nextChield;
    }
    pwd(temp);
    return temp;
}
void pwd(struct directory *temp)
{
    printf("%s\n",temp->x);
}
struct directory *cdUp(struct directory *temp)
{
    temp = temp->_prev;
    return temp;
}
void ls()
{
    int i;
    struct directory *temp=ilk;
    for (i=0; i<10; i++)
    {
        if (temp != NULL)
        {
            switch(i)
            {
                case 0:
                        printf("%s ",temp->x);
                        break;
                case 1:
                        printf("%s ",temp->_firstChield->x);
                        break;
                case 2:
                        printf("%s ",temp->_firstChield->_nextChield->x);
                        break;
                case 3:
                        printf("%s ",temp->_firstChield->_nextChield->_nextChield->x);
                        break;
                case 4:
                        printf("%s ",temp->_firstChield->_nextChield->_nextChield->_nextChield->x);
                        break;
                case 5:
                        printf("%s ",temp->_firstChield->_firstChield->x);
                        break;
                case 6:
                        printf("%s ",temp->_firstChield->_firstChield->_nextChield->x);
                        break;
                case 7:
                        printf("%s ",temp->_firstChield->_firstChield->_nextChield->_nextChield->x);
                        break;
                case 8:
                        printf("%s ",temp->_firstChield->_nextChield->_nextChield->_nextChield->_firstChield->x);
                        break;
                case 9:
                        printf("%s \n",temp->_firstChield->_nextChield->_nextChield->_nextChield->_firstChield->_nextChield->x);
                        break;
            }
        }
        else
        {
            printf("command not found");
        }
    }
}
void createFolder() //mkdir
{
    char folderName[25];
    printf("Enter the folder name : ");
    scanf("%s",folderName);

    if (1 == mkdir(folderName,777))
    {
        printf("File not created !\n");
    }
    else
    {
        printf("The file was created !\n");
    }
}
void createFile() //touch
{
    char fileName[25];
    printf("Enter the file name : ");
    scanf("%s",fileName);
    FILE *dosya = fopen(fileName,"w");
    if (dosya == NULL)
    {
        printf("File not created.\n");
    }
}
