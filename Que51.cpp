//********************************************************************************************************************
//
//					Assignment : 5
//					Question_number : 1
//					Compiler : GCC (tdm64-1) 9.2.0
//					Subject : System Lab
//					Roll No. : 204101025 (Harshit Joshi) 204101027 (Hemant Regar)
//
//********************************************************************************************************************

#include<bits/stdc++.h>
using namespace std;

int np,nf;
vector<int> seq;

int quefind(queue<pair<int, int>>in,int n) //Function to check whether a element is present in queue or not
    {
    	while(!in.empty()) //Till the queue is empty
    	{
    		if(in.front().first==n)
    		{
    			return 1; //Returning 1 if the element n is found
			}
			in.pop();
		}
		return 0;
	}

void SecondChanceAlgo() //Fuction to simulate Second chance algo
{
	cout<<"\n\n***********************************************";
	cout<<"\nResult by Second chance algorithm :";
    queue<pair<int, int>> indexes; //Queue of pair
    int pf=0;
   	int index=0;
   	int rp=0;
    for (int i=0; i<np ; i++) //Iterating till all rquests arrive
    {
        if(indexes.size()< nf) // Condition when que size is less than no. of frames
        {
            if(!quefind(indexes,seq[i])) //if a boxid is not found in queue
            {
                indexes.push({seq[i],0});
                cout<<"\nMiss\t\tfor\tbox\tno.\t"<<seq[i];
                pf++;
            }
            else // if a box id is alreday present in the queue
            {
            	//This condition shows the reference of a existing one
            	cout<<"\nReference\tfor\tbox\tno.\t"<<seq[i];
            	queue<pair<int, int>> temp=indexes;
            	int cnt=0;
		    	while(!temp.empty())
		    	{
		    		if(temp.front().first==seq[i])
		    		{
		    			break;
					}
					temp.pop();
					cnt++;
				}
				temp=indexes;
				int cmt=0;
				while(!temp.empty())
		    	{
		    		if(cmt==cnt)
		    		{
		    			indexes.front().second=1;
					}
					temp.pop();
					int v1=indexes.front().first;
					int v2=indexes.front().second;
					indexes.pop();
					indexes.push({v1,v2});
					cmt++;
				}
			}
        }
        else // Condition when que size is equal to no. of frames
        {
            if (!quefind(indexes,seq[i]))  //if a boxid is not found in queue
            {
            	//This condition shows the replacement of new box with a existing one
    			pf++;
            	while(!indexes.empty())
            	{
            		int val=indexes.front().first;
            		if(indexes.front().second==0)
            		{
            			cout<<"\nBox\t"<<indexes.front().first<<"\tis\treplaced\tby\tnew\tbox\t"<<seq[i];
            			indexes.pop();
            			indexes.push({seq[i],0});
            			rp++;
            			break;
					}
					indexes.pop();
					indexes.push({val,0});
				}

            }
            else
            {
            	//This condition shows the reference of a existing one
            	cout<<"\nReference\tfor\tbox\tno.\t"<<seq[i];
            	queue<pair<int, int>> temp=indexes;
            	int cnt=0;
		    	while(!temp.empty())
		    	{
		    		if(temp.front().first==seq[i])
		    		{
		    			break;
					}
					temp.pop();
					cnt++;
				}
				temp=indexes;
				int cmt=0;
				while(!temp.empty())
		    	{
		    		if(cmt==cnt)
		    		{
		    			indexes.front().second=1;
					}
					temp.pop();
					int v1=indexes.front().first;
					int v2=indexes.front().second;
					indexes.pop();
					indexes.push({v1,v2});
					cmt++;
				}
			}
        }
	}
	cout<<"\nNumber of Miss is    "<<pf;
	cout<<"\nNumber of replacement is	 "<<rp;
}


int main()
{
	srand(time(0) + rand());  //For random page sequenece
	cout<<"Enter no. of boxes	: ";
	cin>>np;  //No. of boxes
	cout<<"Enter no. of slots	: ";
	cin>>nf;  //No. of slots
	if(nf >= np)  //If no. of frames is greater than equal to no. of pages program terminates
	{
		cout<<"No. of slots must be less than no. of boxes ";
		return 0;
	}

	for(int i=0;i<np;i++) //Creating a random sequence of box id by rand function
	{
		int boxid=100;
		seq.push_back(boxid+rand()%15); //Sequence of box id
	}

	cout<<"The random set of boxes is as follows :- \n\n";

	for(int j=0;j<np;j++)
    {
        cout<<seq[j]<<"\t";
    }
	cout<<"\n\n";

	SecondChanceAlgo(); //Function for Second chance algo

	cout<<"\n\n*****************************   \nwith different number of slots	: \n\n\n";
	cout<<"Enter no. of slots	: "; //Finding no. of replacement at different number of slots
	cin>>nf;
	SecondChanceAlgo(); //Function for Second chance algo

	return 0;
}

