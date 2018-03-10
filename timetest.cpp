#include <iostream>
#include <fstream>
#include <string>  // using for getline
#include "CPUTimer.h"
#include "CursorList.h"
#include "dsexceptions.h"
#include "LinkedList.h"
#include "QueueAr.h"
#include "SkipList.h"
#include "StackAr.h"
#include "StackLi.h"
#include "vector.h"
using namespace std;
vector<CursorNode <int> > cursorSpace(500001); // max size parameter

int getChoice()
{
	int choice = 0;

	cout << "\n      ADT Menu\n0. Quit\n1. LinkedList\n2. CursorList\n3. StackAr\n4. StackLi\n5. QueueAr\n6. SkipList\n Your Choice >> ";
	cin >> choice;
	if(choice==0)
	{	//cout << "CPU time: " << 0 << endl; 
		return 0;
	}
	
	if(choice > 6 || choice < 0)
	{
		cout << "Your choice is not between 0 and 6.\nPlease try again.\n";	
	getChoice();
	}
	return choice;
}

void RunList(string nameOfFile)
{
	char command;
	int value;
	List<int> list;
	ListItr<int> itr=list.zeroth(); // initialize iterator to beginning

	ifstream file(nameOfFile);
	if (file.is_open())
	{
		file.ignore(1000, '\n');
		while (file>>command>>value)
		{

			if(command=='i')
			{
				// count++; for debug purposes
				//cout<<"in insertion loop"<<count<<endl;
				list.insert(value,itr); 
				itr.advance();
			}// insert into list, advance iterator
			itr=list.zeroth();
			if(command=='d')
			{
				//itr=list.find(value);
				list.remove(value);
			}//delete from list
			
		}// end of while loop
		file.close();
	}
//	list.print(); for debug purposes
}//RunList

void RunCursorList(string nameOfFile)
{
	char command;
	int value;
	CursorList<int> cursorList(cursorSpace);
	CursorListItr<int> itr = cursorList.zeroth();

	ifstream file(nameOfFile);
	if (file.is_open())
	{
		file.ignore(1000, '\n');
		while (file>>command>>value)
		{

			if(command=='i')
			{
				cursorList.insert(value,itr); 
				itr.advance();
			}//insert, advance iterator
				itr=cursorList.zeroth();

			if(command=='d')
			{
				//itr=list1.find(value);
				cursorList.remove(value);
			}//remove from list
			
		}//while loop ends
		file.close();
	}
	
}//RunCursorList

void RunStackAr(string nameOfFile)
{
	char command;
	int value;

	StackAr<int> stack(500001);

	ifstream file(nameOfFile);
	if (file.is_open())
	{
		file.ignore(1000, '\n');

		while (file>>command>>value)
		{
			if(command=='i')
			{
				stack.push(value);
			}//push into stack

			if(command=='d')
			{
				stack.pop();
			}//delete from stack
		}//while loop ends
		file.close();
	}
	
}//RunStackAr

void RunStackLi(string nameOfFile)
{
	char command;
	int value;
	StackLi<int> stack_list;

	ifstream file(nameOfFile);
	if (file.is_open())
	{
		file.ignore(1000, '\n');

		while (file>>command>>value)
		{
			if(command=='i')
			{
				stack_list.push(value);
			}//push to stack
			if(command=='d')
			{
				stack_list.pop();
			}//delete from the StackLi
			
		}//while loop ends
		file.close();
	}
	
}//RunStackList

void RunQueueAr(string nameOfFile)
{
	char command;
	int value;

	Queue<int> qu_ar(500001);

	ifstream file(nameOfFile);
	if (file.is_open())
	{
		file.ignore(1000, '\n');
		//cout<<"value here at line is : "<<line<<endl;
		while (file>>command>>value)
		{
		//	cout<<"value is: "<<value<<endl;
			if(command=='i')
			{
				qu_ar.enqueue(value);
			}//enqueue to stack

			if(command=='d')
			{
				qu_ar.dequeue();
			}//delete from stack
		}
		file.close();
	}

}//RunQueueAr

void RunSkipList(string nameOfFile)
{
	char command;
	int value;
	SkipList<int> list1(true,500001);

	ifstream file(nameOfFile);
	if (file.is_open())
	{
		file.ignore(1000, '\n');

		while (file>>command>>value)
		{

			if(command=='i')
			{
				list1.insert(value); 
			}//insert into list

			if(command=='d')
			{
				//itr=list1.find(value);
				list1.deleteNode(value);
			}//delete from list
			
		}
		file.close();
	}
	
}//RunList

int main()
{
	int choice;
	string nameOfFile = "";
	cout << "Filename >> ";
	getline(cin, nameOfFile);
	CPUTimer ct;

	do
	{
		choice = getChoice();
		ct.reset();
		switch (choice)
		{
			case 0: cout << "CPU time: " << 0 << endl; return 0;
			case 1: RunList(nameOfFile); break;
			case 2: RunCursorList(nameOfFile); break;
			case 3: RunStackAr(nameOfFile); break;
			case 4: RunStackLi(nameOfFile); break;
			case 5: RunQueueAr(nameOfFile); break;
			case 6: RunSkipList(nameOfFile); break;

	 	}
		//if (choice == 0)
		//	cout << "CPU time: " << 0 << endl;
		//else
			cout << "CPU time: " << ct.cur_CPUTime() << endl;
	} while(choice > 0);

	return 0;
}

