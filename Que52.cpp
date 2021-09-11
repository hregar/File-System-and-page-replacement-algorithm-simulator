//********************************************************************************************************************
//
//					Assignment : 5       
//					Question_number : 2 
//					Compiler : GCC (tdm64-1) 9.2.0
//					Subject : System Lab
//					Roll No. : 204101025 (Harshit Joshi) 204101027 (Hemant Regar) 					
//
//********************************************************************************************************************

#include<bits/stdc++.h>
using namespace std;

vector<int> in,seq;
int np,nf;

void read(string file) //Reading input from user and assigning values to np,nf and seq vector.
{
	string my,temp="",t1="";
	int x=0;
	ifstream m;
	m.open(file);
	getline(m,my);
	for(int i=0;i<my.size();i++)
	{
		temp=my[i];
		if(temp==","){
			stringstream g(t1);
			g>>x;
			in.push_back(x);
			t1="";
		}
		else{
			t1+=temp;
		}
		
		if(i==my.size()-1 && temp!=",")
		{
			stringstream g(t1);
			g>>x;
			in.push_back(x);
		}
	}
	getline(m,my);
	t1="";
	for(int i=0;i<my.size();i++)
	{
		temp=my[i];
		if(temp==","){
			stringstream g(t1);
			g>>x;
			seq.push_back(x);
			t1="";
		}
		else{
			t1+=temp;
		}
		
		if(i==my.size()-1 && temp!=",")
		{
			stringstream g(t1);
			g>>x;
			seq.push_back(x);
		}
	}
	np=in[0];nf=in[1];
}


void FIFO()  //Simulation function for FIFO
{
	cout<<"\n\n***********************************************";
	cout<<"\nSimulation result for FIFO\n";
	unordered_set<int> s;
    queue<int> indexes;
    int pf = 0;
    for (int i=0; i<np ; i++)
    {
        if (s.size() < nf)
        {
            if(s.find(seq[i])==s.end())
            {
                s.insert(seq[i]);
                pf++;
                indexes.push(seq[i]);
                cout<<"\n   Miss  for  "<<seq[i];
            }
            else
            {
            	cout<<"\n   Hit  for  "<<seq[i];
			}
        }
        else
        {
            if (s.find(seq[i]) == s.end())
            {
                int val = indexes.front();
                indexes.pop();
                s.erase(val);
                s.insert(seq[i]);
                indexes.push(seq[i]);
                pf++;
                cout<<"\n   Miss  for  "<<seq[i];
            }
            else
            {
            	cout<<"\n   Hit  for  "<<seq[i];
			}
        }
	}
	cout<<"\n Page faults  by FIFO    "<<pf;
}


void LRU()	//Simulation function for LRU
{
	cout<<"\n\n***********************************************";
	cout<<"\nSimulation result for LRU\n";
	unordered_set<int> s;
    queue<int> indexes;
    int pf = 0;
    for (int i=0; i<np ; i++)
    {
        if (s.size() < nf)
        {
            if(s.find(seq[i])==s.end())
            {
                s.insert(seq[i]);
                pf++;
                indexes.push(seq[i]);
                cout<<"\n   Miss  for  "<<seq[i];
            }
            else
            {
            	cout<<"\n   Hit  for  "<<seq[i];
            	queue<int> temp;
            	while(!indexes.empty())
            	{
            		int val=indexes.front();
            		if(val!=seq[i])
            		{
            			temp.push(val);
					}
					indexes.pop();
				}
                temp.push(seq[i]);
                indexes=temp;
			}
        }
        else
        {
            if (s.find(seq[i]) == s.end())
            {
                int val = indexes.front();
                indexes.pop();
                s.erase(val);
                s.insert(seq[i]);
                indexes.push(seq[i]);
                pf++;
                cout<<"\n   Miss  for  "<<seq[i];
    
            }
            else
            {
            	cout<<"\n   Hit  for  "<<seq[i];
            	queue<int> temp;
            	while(!indexes.empty())
            	{
            		int val=indexes.front();
            		if(val!=seq[i])
            		{
            			temp.push(val);
					}
					indexes.pop();
				}
                temp.push(seq[i]);
                indexes=temp;
			}
        }
	}
	cout<<"\n Page faults  by LRU    "<<pf;
}


void LFU() //Simulation function for LFU
{
	cout<<"\n\n***********************************************";
	cout<<"\nSimulation result for LFU\n";
	unordered_set<int> s;
	map<int,int> mp;
    queue<int> indexes;
    int pf = 0;
    for (int i=0; i<np ; i++)
    {
        if (s.size() < nf)
        {
            if(s.find(seq[i])==s.end())
            {
                s.insert(seq[i]);
                indexes.push(seq[i]);
                pf++;
                mp[seq[i]]=0;
                cout<<"\n   Miss  for  "<<seq[i];
            }
            else
            {
            	cout<<"\n   Hit  for  "<<seq[i];
			}
			mp[seq[i]]++;
        }
        else
        {
            if (s.find(seq[i]) == s.end())
            {
            	int t=mp[indexes.front()],val=indexes.front(),temp,index=0;
            	for(int j=0;j<indexes.size();j++)
            	{
            		temp=indexes.front();
            		if(t > mp[temp])
            			{
            				t=mp[temp];
            				val=temp;
            				index=j;
						}
					indexes.pop();indexes.push(temp);
					
				}
                s.erase(val);
                mp[val]=0;
                s.insert(seq[i]);
                for(int i=0;i<index;i++)
                {
                	temp=indexes.front();
                	indexes.pop();indexes.push(temp);
				}
				indexes.pop();
				indexes.push(seq[i]);
                pf++;
                cout<<"\n   Miss  for  "<<seq[i];
            }
            else
            {
            	cout<<"\n   Hit  for  "<<seq[i];
			}
			mp[seq[i]]++;
        }
	}
	cout<<"\n Page faults  by LFU    "<<pf;
}

void simulate(string fname,vector<string> option) //Main simulation function
{
	read(fname); //Reading the inputs from text files which are no. of pages,no. of frames,sequence of pages
	
	if(option.empty()){
		FIFO(); //Simulation function for FIFO
		LRU();	//Simulation function for LRU
		LFU();	//Simulation function for LFU
	}
	else 
	{
		for(int i=0;i<option.size();i++)
		{
			//Simulating the page replacment technique 
			if(option[i]=="FF") FIFO();
			else if(option[i]=="LF") LFU();
			else if(option[i]=="LR") LRU();
			else{
			cout<<"Wrong page replacement technique ";break;} //Terminates if user enters wrong page replacement technique
		}
	}
}

int main()
{
	string fn,jk;
	char ch='y'; //Loop variable
	vector<string> op;
	cout<<"Enter name of the data file :  ";  // Taking filename where input is residing
	cin>>fn;
	cout<<"Do you want to choose a page replacement technique (y/n) 	:";
	cin>>ch;
	while(ch=='y' || ch=='Y') //Loop iterates till user 
	{
		cout<<"Enter name of the page replacement policy :   ";
		cin>>jk;
		op.push_back(jk); //Making vector of choices of user for page replacement technique
		
		cout<<"Press (y/n) to continue"; 
		cin>>ch;
	}
	
	simulate(fn,op); //Calling the main simulating function to simulate various page replacement techniques
	
	return 0;
}

