//********************************************************************************************************************
//
//					Assignment : 5       
//					Question_number : 3 
//					Compiler : GCC (tdm64-1) 9.2.0
//					Subject : System Lab
//					Roll No. : 204101025 (Harshit Joshi) 204101027 (Hemant Regar) 					
//
//********************************************************************************************************************

#include<bits/stdc++.h>
using namespace std;

char data[128][1024];

struct inode //structure of a inode
{
	char name[8];
	int size;
	int block[8]={0,0,0,0,0,0,0,0};
	int used=0;	
};

struct superblock //structure of superblock
{
	int freeblock[128];
	struct inode inodearr[16];
};

struct superblock sb;

void create(char name[8],int size) //Creating a file 
{
	int f=0;
	int in=0;
	for(int i=0;i<17;i++)
	{
		if(i==16 and sb.inodearr[i].used==1) //If there are alraedy 16 files available
		{	
			cout<<"File creation not possible as there are alreay 16 files available!!!";
			return ;
			
			
		}
		else if(sb.inodearr[i].used==1) //If file already exist
		{
			int c=0;
			for(int j=0;j<8;j++)
			{
				if(name[j]==sb.inodearr[i].name[j])
				{
					c=0;
					if(name[j]=='\0' && sb.inodearr[i].name[j]=='\0') break;
				}
				else
				{
					c=1;
					break;
				}
			}
			if(c==0) 
			{
				cout<<"\nFile name already exist!!!";
				break;
				return ;
			}
		}
		else if(sb.inodearr[i].used==0) //If file not exist
		{
			sb.inodearr[i].used=1;
			f=1;
			for(int j=0;j<8;j++)
			{
				if(name[j]!='\0')
				{
					sb.inodearr[i].name[j]=name[j];
				}
				else
					break;
			}
			in=i;
			break;
		}
	}
	if(f==1)
	{
		int si=0;
		for(int i=1;i<128;i++)
		{
			if(sb.freeblock[i]==0)
			{
				if(i==121 && si==0)
				{
					cout<<"Only 7 blocks will be allocated!!!";
				}
				sb.freeblock[i]=1;
				sb.inodearr[in].block[si]=i;
				si++;
			}
			if(si==size)
			{
				cout<<"file created successfully !!! ";	
				break;
			}
		}
	}
}

void deleteit(char name[8]) //Deleting a file
{
	for(int i=0;i<17;i++)
	{
		int c=0;
		for(int j=0;j<8;j++)
		{
			if(name[j]==sb.inodearr[i].name[j])
			{
				c=0;
				if(name[j]=='\0' && sb.inodearr[i].name[j]=='\0') break;
			}
			else
			{
				c=1;
				break;
			}
		}
		if(c==0)  //if file exist
		{
			cout<<"\n\n"<<sb.inodearr[i].name<<"	File deleted!!!\n";
			sb.inodearr[i].used=0;
			for(int k=0;k<8;k++)
			{
				if(sb.inodearr[i].block[k]!=0)
					sb.freeblock[sb.inodearr[i].block[k]]=0;
				else 
					break;
			}
			return ;
		}
	}
	cout<<"File not exist";
	return;		
}

void read(char name[8],int blocknum) //Reading data in a block
{
	for(int i=0;i<17;i++)
	{
		int c=0;
		for(int j=0;j<8;j++)
		{
			if(name[j]==sb.inodearr[i].name[j])
			{
				c=0;
				if(name[j]=='\0' && sb.inodearr[i].name[j]=='\0') break;
			}
			else
			{
				c=1;
				break;
			}
		} 
		if(c==0)  // if File exist
		{
			cout<<"\n\n Reading data : \n";
			for(int k=0;k<1024;k++)
			{
				if(data[sb.inodearr[i].block[blocknum]][k]=='\0')
				{
					return;
				}
				else
				{
					cout<<data[sb.inodearr[i].block[blocknum]][k];
				}	
			}
		}	
	}
	cout<<"\nBlock is empty!!!";	
	return ;
}

void write(char name[8], int blocknum,char buff[1024]) //Writing data in a block
{
	for(int i=0;i<17;i++)
	{
		int c=0;
		for(int j=0;j<8;j++)
		{
			if(name[j]==sb.inodearr[i].name[j])
			{
				c=0;
				if(name[j]=='\0' && sb.inodearr[i].name[j]=='\0') break;
			}
			else
			{
				c=1;
				break;
			}
		}
		if(c==0)  //If file exist
		{
			for(int k=0;k<1024;k++)
			{
				if(buff[k]=='\0')
				{
					cout<<"\nWritten successfully !!!\n";	return;
				}
				else
				{
					data[sb.inodearr[i].block[blocknum]][k]=buff[k];
				}	
			}
		}	
	}
	cout<<"\nFile not written";
	return ;
}
 
void ls() //Showing all available files in system 
{
	cout<<"\nList of file names is as follows  :		\n";
	for(int i=0;i<17;i++)
	{
		if(sb.inodearr[i].used==1) 
		{
			cout<<"\n"<<sb.inodearr[i].name;
		}
	}	
}

int main()
{
	//sb is a instance for superblock
	for(int i=0;i<128;i++)
	{
		sb.freeblock[i]=0; //intializing all initial freeblocks index with a 0 in super block
	}
	char ch='y';
	while(ch=='y' || ch=='Y') //iterates till user enter a value 'y' or 'Y'
	{
		int choice=0;
		
		//Menu for display
		cout<<"\nHere is the menu for the file system operation :   ";
		cout<<"\n1.\tCreate File";
		cout<<"\n2.\tDelete File";
		cout<<"\n3.\tRead data from a block";
		cout<<"\n4.\tWrite data into file";
		cout<<"\n5.\tPrint name of all files\n";
		cout<<"\n\nChoose from the above options :->	";
		cin>>choice;  //Input desired choice
		
		if(choice > 0 && choice <5)
		{
			char name[8]; //for file name
			char buff[1024]; //size of a block
			int blocks; //no. of blocks
			cout<<"\nEnter file name { max 7 character } ";
			cin>>name; //File name
			if(choice==1){
				cout<<"\nEnter number of blocks you want [Range 0-8]";
				cin>>blocks; //no. of blocks
				if(blocks>8)
				{
					cout<<"Number of blocks should be less than equal to 8 ";
					return 0;
				}
				create(name,blocks); //Creating file
			}
			else if(choice==2){
				deleteit(name); //Deleting File
			}
			else if(choice==3){
				cout<<"\nEnter block number from where you want to read ->	";
				cin>>blocks;
				read(name,blocks); //Reading data from a block
			}
			else{
				cout<<"\nEnter data to be inserted ->	";
				scanf(" %[^\n]s",buff);
				cout<<"\nEnter block number where data need to be written ->	";
				cin>>blocks;
				write(name,blocks,buff); //Writing data in a block
			}
		}
		else if(choice==5) //To show all available files within the file system
		{
			ls();
		}
		else //Wrong choice entered
		{
			cout<<"\nWrong input!!!";
			cout<<"\n\nThe End";
			return 0;
		}
		cout<<"\nEnter y to continue to operate File system ->	";
		cin>>ch;
	}
	cout<<"\n\nThe End";
	return 0;
}
