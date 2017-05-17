#include <stdio.h>
#include<stdlib.h>
struct TNode
{
    bool isEOW;
    TNode* next[26];
};
char path[100];
TNode* createNode()
{
    TNode* nn=(TNode*)malloc(sizeof(TNode));
    nn->isEOW=false;
    for(int i=0;i<26;i++)
        nn->next[i]=NULL;
    return nn;
}
void insertWord(TNode* root,char* word)
{
    int i=0;
    TNode* temp=root;
    while(word[i]!='\0')
    {
        if(temp->next[word[i]-'a']!=NULL)
            temp=temp->next[word[i]-'a'];
        else
        {
            TNode* t=createNode();
            temp->next[word[i]-'a']=t;
            temp=temp->next[word[i]-'a'];
        }
        i++;
    }
    temp->isEOW=true;
}
int num=1;
void printAllWords(TNode* root,int k)
{
    if(root->isEOW)
    {
        printf("%d) %s\n",num,path);
        num++;
    }
    else
    {
        for(int i=0;i<26;i++)
        {
            if(root->next[i]!=NULL)
            {
                path[k]=i+'a';
                path[k+1]='\0';
                printAllWords(root->next[i],k+1);
            }
        }

    }
}
void printIfExists(TNode* root2,char *word)
{
    TNode* temp=root2;
    int i=0;
    while(word[i]!='\0')
    {
        if(temp->next[word[i]-'a']!=NULL)
            temp=temp->next[word[i]-'a'];
        else
            return;
        i++;
    }
    if(temp->isEOW)
        printf("%s\n",word);
}
char board[4][4]={{'s','t','f','z'},{'w','m','h','n'},{'a','b','i','g'},{'y','x','d','e'}};
char word[17];
bool visited[4][4];
void generateAllWordsAtIdx(TNode* root,int i,int j,int k)
{
    if(i<0 || i>=4|| j<0 || j>=4 || visited[i][j])
        return;
    word[k]=board[i][j];
    word[k+1]='\0';
    visited[i][j]=true;
    printIfExists(root,word);
    /*for(int di=-1;di<=1;di++)
    {
        for(int dj=-1;dj<=1;dj++)
        {
                generateAllWordsAtIdx(root,i+di,j+dj,k+1);
        }
    }*/
    generateAllWordsAtIdx(root,i,j-1,k+1);
    generateAllWordsAtIdx(root,i,j+1,k+1);
    generateAllWordsAtIdx(root,i-1,j,k+1);
    generateAllWordsAtIdx(root,i+1,j,k+1);
    visited[i][j]=false;
}
void generateAllWords(TNode* root)
{
    for(int i=0;i<4;i++)
        for(int j=0;j<4;j++)
            generateAllWordsAtIdx(root,i,j,0);
}
int main()
{
    TNode* root=createNode();
    FILE* fp;
    char word[45];
    fp=fopen("words.txt","r");
    while(!feof(fp))
    {
        fscanf(fp,"%s",word);
        insertWord(root,word);
    }
    generateAllWords(root);
    //printAllWords(root,0);
    return 0;
}
