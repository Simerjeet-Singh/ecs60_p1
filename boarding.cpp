#include <iostream>
#include <fstream>
#include "StackAr.h"
#include "QueueAr.h"
using namespace std;

typedef enum {EMPTY, STORING_LUGGAGE1, STORING_LUGGAGE2, ABC_DEF_OUT, ABC_DEF_IN} State; 
class Passenger_row
{
        public:
        int pass_row;
};
class Passenger_seat
{
        public:
        char pass_seat;
};

class Passenger
{
	public:
	int pass_row;
	char pass_seat;
	Passenger(): pass_row(0) {}
};
class Row
{
	public:
	   Passenger pass;
	   int row_number;//current row_number
	   State state; // current row state
  	   StackAr <char> stackABC, stackDEF, stackAisle;
	   Row() : row_number(0), state(EMPTY), stackABC(3), stackDEF(3), stackAisle(3) {}
};


int boardPassengers(Queue <Row> &plane, Queue <Passenger_row> &pass_row, Queue <Passenger_seat> &pass_seat)
{
	int time = 0;
	int seat_count = 0;
	int load_count = 0; 
	Row row;
	Row previousRow;
	int whileLoopCount = 0;
	bool rightRow = 0;	
	int testload_count = 288;
  	int testseat_count = 288;
	while(seat_count < testseat_count)  // loop until all passengers seated
  	{
		whileLoopCount++;
  		previousRow.row_number = 0;
    		for(int i = 1; i <= 48; i++) 
    		{
      			row = plane.dequeue();
      			switch(row.state)
      			{
				case EMPTY: 
					if(row.pass.pass_row > 0){
						if(row.pass.pass_row == row.row_number)
						{
							row.state = STORING_LUGGAGE1;
					//		rightRow = 1;
						}
						else if(previousRow.pass.pass_row == 0){
							previousRow.pass.pass_row = row.pass.pass_row;
							previousRow.pass.pass_seat = row.pass.pass_seat;
							row.pass.pass_row = 0;
						}
					}
		//		cout <<"State: NONE "<< " while loop count is: "<< whileLoopCount<<" Time is " << time << " Row num is " <<  row.row_number << endl;
				break;
				case STORING_LUGGAGE1: row.state = STORING_LUGGAGE2; break;
				/*	if(rightRow == 1)
					{
						time+=5;
						rightRow = 0;
					}//we added extra 5 seconds needed for storing the luggage besides 5 seconds for each state
					*/
				case STORING_LUGGAGE2:
					if(row.pass.pass_seat < 'D')
					{
						//row.state = EMPTY;
						if(row.stackABC.isEmpty())
						{
							//rightRow = 0;
							row.stackABC.push(row.pass.pass_seat);
							row.state = EMPTY;
						}
						else if(!row.stackABC.isEmpty() && row.stackABC.top()>row.pass.pass_seat)
						{
							row.stackAisle.push(row.stackABC.topAndPop());
							row.state = ABC_DEF_OUT;
						}
						else if(!row.stackABC.isEmpty() && row.stackABC.top()<row.pass.pass_seat)
						{
							row.stackABC.push(row.pass.pass_seat);
							row.state = EMPTY;
						}
						//else{
						//	cout<<"Red alert in LUGGAGE" <<endl;
						//}
					}
					else
					{
						if(row.stackDEF.isEmpty())
						{
							row.stackDEF.push(row.pass.pass_seat);
							row.state = EMPTY;
							//row.rightRow = 0;
						}
						else if(!row.stackDEF.isEmpty() && row.stackDEF.top()<row.pass.pass_seat)
						{
							row.stackAisle.push(row.stackDEF.topAndPop());
							row.state = ABC_DEF_OUT; //DEF_OUT;
						}
						else if(!row.stackDEF.isEmpty() && row.stackDEF.top()>row.pass.pass_seat)
						{
							row.stackDEF.push(row.pass.pass_seat);
							row.state = EMPTY;
						}
						//else{
                                                  //      cout<<"Red alert in LUGGAGE" <<endl;
                                                //}
						
					}
		//		cout <<"State: StoringLuggage "<< " while loop count is: "<< whileLoopCount<<" Time is " << time << " Row num is " <<  row.row_number << endl;

				break;
				case ABC_DEF_OUT:
					if(row.pass.pass_seat<'D')
					{	
						if(!row.stackABC.isEmpty())
						{
							if(row.stackABC.top()<row.pass.pass_seat)
							{
								row.stackABC.push(row.pass.pass_seat);
								if(!row.stackAisle.isEmpty())
									row.state = ABC_DEF_IN;
								else 
									row.state = EMPTY;
							}	
							else
							{
								row.stackAisle.push(row.stackABC.topAndPop());
							}

						}
						else //row is empty now
						{
							row.stackABC.push(row.pass.pass_seat);
							if(row.stackAisle.isEmpty())
								row.state = EMPTY;
							else if(!row.stackAisle.isEmpty())
								row.state = ABC_DEF_IN;
						}
					}
					else
					{
						if(!row.stackDEF.isEmpty())
                                        {
                                                if(row.stackDEF.top()>row.pass.pass_seat)
                                                {
                                                        row.stackDEF.push(row.pass.pass_seat);
                                                        if(!row.stackAisle.isEmpty())
                                                                row.state = ABC_DEF_IN;//DEF_IN;
                                                        else
                                                                row.state = EMPTY;
                                                }
                                                else
                                                {
                                                        row.stackAisle.push(row.stackDEF.topAndPop());
                                                }

                                        }
                                        else //row is empty now
                                        {
                                                row.stackDEF.push(row.pass.pass_seat);
                                                if(row.stackAisle.isEmpty())
                                                        row.state = EMPTY;
                                                else if(!row.stackAisle.isEmpty())
                                                        row.state = ABC_DEF_IN;//DEF_IN;
                                                //else{
                                                  //      cout<<"Red alert in DEFout" <<endl;
                                                //}
                                        }
					}
					
		//		cout <<"State: ABC_DEF_OUT "<< " while loop count is: "<< whileLoopCount<<" Time is " << time << " Row num is " <<  row.row_number << endl;


				break;
				case ABC_DEF_IN:
					//if(!row.stackAisle.isEmpty())
					if(row.pass.pass_row > 0 && row.pass.pass_seat<'D'){
						row.stackABC.push(row.stackAisle.topAndPop());
						 if(row.stackAisle.isEmpty())
							row.state = EMPTY;
					}
					else{//going in for DEF row.
						if(row.pass.pass_row > 0){
                                                row.stackDEF.push(row.stackAisle.topAndPop());
                                                if(row.stackAisle.isEmpty())
                                                        row.state = EMPTY;
                                        }
					}

		//				cout <<"State: ABC_In "<< " while loop count is: "<< whileLoopCount<<" Time is " << time << " Row num is " <<  row.row_number << endl;


				break;		
				}// end of switch
			bool check = row.state==EMPTY ? (row.pass.pass_row==row.row_number ? 1 : 0) : 0;
			if(check)
			{
        			row.pass.pass_row = 0;
        			seat_count++;
      			}
			if(previousRow.row_number != 0)
				plane.enqueue(previousRow);
			previousRow = row;
	}//end of for loop
		bool check;
		check = previousRow.pass.pass_row == 0 ? (load_count<testload_count ? 1 : 0): 0;
		if(check) 
			{
				Passenger_row pass_row_object;
				Passenger_seat pass_seat_object;
				pass_row_object = pass_row.dequeue();
				pass_seat_object = pass_seat.dequeue();
				previousRow.pass.pass_row = pass_row_object.pass_row;//readin from the queue
				previousRow.pass.pass_seat = pass_seat_object.pass_seat;
				load_count++;
			}
		plane.enqueue(previousRow);
	time+=5;
//}while(seat_count<288);
} // end of while loop
	return time;
}//end of function

int main(int argc, char **argv)  
{	
	ifstream file(argv[1]);
	Queue <Row> plane1(48);
	Queue <Passenger_row> pass_row(864);
	Queue <Passenger_seat> pass_seat(864);
	Passenger_row passe_row;
	Passenger_seat passe_seat;
	Row row;
	int row_num;
	char seat;
	if(file.is_open()) 
	{
		while (file>>row_num>>seat)
		{
			passe_seat.pass_seat = seat;
			passe_row.pass_row = row_num;
			pass_row.enqueue(passe_row);
			pass_seat.enqueue(passe_seat);
		}
	}
        for(int i = 48; i > 0; i--)
        {
                row.row_number = i;
                plane1.enqueue(row);
        }  // created all rows in the plane and initialized them

	int time1 = boardPassengers(plane1, pass_row, pass_seat);
	cout << "Back to front: " << time1 << endl;

	Queue <Row> plane2(48);
	Queue <Passenger_row> pass_row2(864);
	Queue <Passenger_seat> pass_seat2(864);
	Passenger_row passe_row2;
	Passenger_seat passe_seat2;
 	Row row2;
	/*if(file.is_open()) 
	{
		while (file>>row_num>>seat)
		{
			passe_seat2.pass_seat = seat;
			passe_row2.pass_row = row_num;
			pass_row2.enqueue(passe_row);
			pass_seat2.enqueue(passe_seat);
		}
	}*/
        for(int i = 48; i > 0; i--)
        {
                row2.row_number = i;
                plane2.enqueue(row2);
        }  // created all rows in the plane and initialized them

	int time2 = boardPassengers(plane2, pass_row, pass_seat);
	cout << "Random: " << time2 << endl;

	Queue <Row> plane3(48);
	Row row3;

        for(int i = 48; i > 0; i--)
        {
                row3.row_number = i;
                plane3.enqueue(row3);
        }  // created all rows in the plane and initialized them

	int time3 = boardPassengers(plane3, pass_row, pass_seat);
	cout << "Outside in: " << time3 << endl;
	
	return(0);
}

