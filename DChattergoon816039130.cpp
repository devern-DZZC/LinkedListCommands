#include<iostream>
#include<fstream>
#include<cstdlib>

using namespace std;

struct Node{
	int data;
	Node * next;
};

Node * createNode(int n)
{
	Node * newNode;
	newNode = new Node;
	newNode->data = n;
	newNode->next = NULL;
	
	return newNode;
}

Node * insertAtHead(Node * top, int n)
{
	Node * newNode;
	newNode = createNode(n);
	newNode->next = top;
	top = newNode;
	
	return top;
	
}

Node * insertAtTail(Node * top, int n)
{
	Node * newNode;
	newNode = createNode(n);
	Node * curr = new Node;
	
	if(top == NULL)
		return newNode;

	curr = top;
	while(curr->next != NULL)
	{
		curr = curr->next;
	}
	curr->next=newNode;
	
	return top;
}

void printList(Node * top)
{
	Node * curr = new Node;
	if(top==NULL)
	{
		cout << "List is Empty";
		return;
	}
	
	curr = top;
	while(curr != NULL)
	{
		cout << curr->data << "\t";
		curr=curr->next;
	}
	cout << endl;
}

Node * deleteNode(Node * top, int key)
{
	Node * curr = top;
	Node * pred = NULL;
	
	if(top==NULL)
	{
		cout << "List is empty";
		return top;
	}
	else
	{
		while(curr != NULL)
		{
			if(curr->data == key)
			{
				if(pred==NULL)
				{
					top = top->next;
					return top;
				}
				else
				{
					pred->next = curr->next;
					free(curr);
					return top;
				}
			}
			pred=curr;
			curr = curr->next;
			
		}
	}
	
	cout << "\n" << key << " was not found in the list.\n"; 
	return top;
}

Node * deleteList(Node * top)
{
	Node * curr;
	Node * temp;
	
	if(top == NULL)
	{
		cout << "List is empty";
		return top;
	}
	
	curr = top;
	while(curr != NULL)
	{
		temp = curr;
		curr = curr -> next;
		free(temp);
	}
	top=NULL;
	return top;
}

int findLargest(Node * top)
{
	int max = INT_MIN;
	Node * curr = new Node;
	curr = top;
	while(curr != NULL)
	{
		if(curr->data > max)
			max = curr->data;
			
		curr = curr->next;	
	}
	return max;
}

Node * mergeList(Node * top1, Node * top2, Node * top3)
{
	Node * tempNode = new Node;
	tempNode = NULL;
	Node * curr = new Node;
	curr = top1;
	while(curr != NULL)
	{
		tempNode = insertAtHead(tempNode, curr->data);
		curr = curr->next;
	}
	curr = top2;
	while(curr != NULL)
	{
		tempNode = insertAtHead(tempNode, curr->data);
		curr = curr->next;
	}
	
	curr = tempNode;
	while(curr != NULL)
	{
		top3 = insertAtHead(top3, curr->data);
		curr=curr->next;
	}
	return top3;
}

void commandRouter (Node *NUM_ARR[], char command, int param1, int param2, int param3)
{
	int largest;
	switch(command)
	{
		case 'G':
			cout << "\n\n  --> Processing command: "<<command<< " "<<param1<<" ...\n\n";
			largest=findLargest(NUM_ARR[param1]);
			cout<<"Largest in list "<<param1<<" is "<<largest<<endl;
			break; 
		
		case 'X':
			cout << "\n\n  --> Processing command: "<<command<< " "<<param1<<" ...\n\n";
			cout << "Deleting list " <<param1<< " ..."<<endl;
			NUM_ARR[param1]=deleteList(NUM_ARR[param1]);
			break;
				
		case 'A':
			cout << "\n\n  --> Processing command: "<<command<< " "<<param1<<" "<<param2<<" ...\n\n";
			cout << "Adding "<<param2<< " to the end of list "<<param1<<" ..."<<endl;
			NUM_ARR[param1] = insertAtTail(NUM_ARR[param1], param2);
			break;
			
		case 'D':
			cout << "\n\n  --> Processing command: "<<command<< " "<<param1<<" "<<param2<<" ...\n\n";
			cout << "Deleting "<<param2<< " from list "<<param1<<" ..."<<endl;
			NUM_ARR[param1]=deleteNode(NUM_ARR[param1], param2);
			break;
		
		case 'P':
			cout << "\n\n  --> Processing command: "<<command<< " "<<param1<<" ...\n\n";
			cout << "Printing list "<<param1<<" ..."<<endl;
			printList(NUM_ARR[param1]);
			break;
			
		case 'H':
			cout << "\n\n  --> Processing command: "<<command<< " "<<param1<<" "<<param2<<" ...\n\n";
			cout << "Adding "<<param2<< " to the head of list "<<param1<<" ..."<<endl;
			NUM_ARR[param1] = insertAtHead(NUM_ARR[param1], param2);
			break;
			
		case 'M':
			cout << "\n\n  --> Processing command: "<<command<< " "<<param1<<" "<<param2<<" "<<param3<<" ...\n\n";
			cout << "Merging list "<<param1<<" and list "<<param2<<" with list "<<param3<< " ..."<<endl;
			NUM_ARR[param3] = mergeList(NUM_ARR[param1], NUM_ARR[param2], NUM_ARR[param3]);
			NUM_ARR[param1]=deleteList(NUM_ARR[param1]);
			NUM_ARR[param2]=deleteList(NUM_ARR[param2]);
			break;
		
		default:
			cout << "Command not found";
			break;
	}
}


int main()
{
	Node * NUM_ARR[101];
	ifstream in;
	int location, data, count=0;
	char command;
	
	in.open("asg2.txt");
	if(!in.is_open())
	{
		cout << "Error opening file...";
		return 1;
	}
	
	NUM_ARR[0] = new Node;
	in >> location;
	while(location != -999)
	{
		NUM_ARR[location] = new Node;
		NUM_ARR[location] = NULL;
		in >> data;
		while(data != -1)
		{
			NUM_ARR[location] = insertAtTail(NUM_ARR[location], data);
			in >> data;
		}
		count++;
		in >> location;
	}
	NUM_ARR[0]->data = count;
	
	
	cout << "Processing Commands ...\n\n";
	
	in >> command;
	while(command != '$')
	{
		cout <<endl<< "-----------------------------------------------------------------------------------------------------------------------------------------------------------"<<endl;

		if(command == 'Z')
		{
			cout << "\n\n  --> Processing command: "<<command<< " ...\n";
			cout << "Number of Lists: "<<count<<endl<<endl;
			for(int i=1;i<=count;i++)
			{
				cout << "\nPrinting list "<<i<<" ..."<<endl;
				printList(NUM_ARR[i]);
				cout << endl;
			}
			
		}
		else
		{
			int temp_param, param1=0, param2=0, param3=0;
			if(command == 'G' || command == 'X' || command == 'P')
			{
				in >> param1;
			}
			else if (command == 'A' || command == 'D' || command == 'H')
			{
				in >> param1 >> param2;
			}
			else if(command == 'M')
			{
				in >> param1 >> param2 >> param3;	
			}
			commandRouter (NUM_ARR, command, param1, param2, param3);
		}
		in >> command;
			
	}
	in.close();
	
	for(int i=3;i<=count;i++)
	{
		NUM_ARR[i]=deleteList (NUM_ARR[i]);
	}
	
	for(int i=0;i<=count;i++)
	{
		delete (NUM_ARR[i]);
	}
	
	
	
return 0;
}
