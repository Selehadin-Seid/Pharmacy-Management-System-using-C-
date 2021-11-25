#include <iostream>
#include <stdlib.h> //for system
#include <string>
#include <fstream>
#include <iomanip>
#include <ctime>

using namespace std;


class pharmacy                                           
{
public:                                             // To make it accessible from outside the class

    void customer();
    void admin();
	void purchase();                                //to  take_order
    void delete_order();                            //to delete the order
    void modify();                                  //to modify the order
	void completePayment();                         //to display the order_list
	void daily_summary();                           //to display daily_summary
	void exit();                                    //function to exit system
	

};  // End of class



struct collection
{
	int reciept_number;
	string customerName;
	string date;
	int quantity[10];
	
	int numentry, drug_ID[100];
    double amount[10];
   string medicineName[100]={"Paracetamol (500mg)","Tetracycline (250mg)","Amoxicillin (250mg)","Albendazole (100 mg)","Diclofenac","Doxycyline ",
	"Amino Zinc Tablet","Omeprazole","Fabuloss 5","Metronidazole "};
	double amount_in_birr[10]= {17.00,36.00,45.00,97.00,42.00,150.00,25.00,40.00,35.00,132.00};
	double total;


	collection *new_store;

} *delete_ptr, *store1;
				//pointer declaration 


collection *store2 = NULL;
collection *last = NULL;


int main()	
{

	pharmacy medicine;   // Create an object of pharmacy
	
	
int userchoice;
	do{
	system ("cls");
	
	cout<<" \t\t Please choose one option" <<endl<<endl;
	cout<<"\t 1.  Admin: " <<endl;
	cout<<"\t 2.  Customer  " <<endl;
	cout<<"\t 3.  Exit  " <<endl;
	cout<<endl<<"Enter Choice: ";
	cin>>userchoice;
	
    if (userchoice == 2)
    {
    	medicine.customer();
    	break;
	}
	else if ( userchoice == 1)
	{
		medicine.admin();
		break;
	}
	else if ( userchoice == 3)
	{
		medicine.exit();
		break;
	}
	else {
		cout<< "Invalid Entry! Please try again"<<endl;
		system ("pause");
		
	}

	
}while(userchoice!=1 || userchoice!=2);

return 0;

}//end  main function


void pharmacy::customer()		//function to user
{
	pharmacy medicine;
	int menu;
   	do
	{
		system("cls");

		cout<<"1. Purchase a New Medicine "<<endl ;
		cout<<"2. Revise or Modify Purchase List "<<endl;
		cout<<"3. Cancel or Delete Purchase"<<endl;
		cout<<"4. Complete Payment "<<endl;
		cout<<"5. Exit"<<endl<<endl<<endl;

		cout<<"Enter choice: ";

		cin>>menu;

		switch (menu)
		{
		case 1:
			{
				medicine.purchase ();	//function purchase
				break;
			}	
		
		
		case 2:
			{
				medicine.modify();	//function modify
				system("PAUSE");
				break;
			}	//end case 2
		
		case 3:
			{
				medicine.delete_order();	//function delete
				system("PAUSE");
				break;
			}	//end case 3
			


		case 4:
			{
			  medicine.completePayment();	//function order
				system("PAUSE");
				break;
			}	//end case 4

        case 5:
			{
				medicine.exit();	//function exit
			    
				break;
			}	//end case 5

		
		default:
			{
				cout<<"You enter invalid input\nre-enter the input\n"<<endl;
				break;
			}//end defeault
		}//end Switch
	}while(menu!=5);//end do
	
	
}//End function user


// start of customer functions


void pharmacy::purchase()		//function to take_order
{
	system("cls");
    int quantity, price;

	cout <<"\n Medicine lists and descriptions \n";
	cout <<"_____________________________________ \n\n";

	store1= new collection;
	
	string printdoc;
	fstream inputFile;        // Input file stream object
	inputFile.open ("medicinelist.txt");
	
	if(inputFile.is_open()){
		while ( getline (inputFile,printdoc) )
		{
		//Printing the output of the file contents
		cout << printdoc << '\n';
		}
				cout<<endl;
		        inputFile.close();
		    }
    else{
        cout << "No data table to show" << endl; }
	

	// save to file
	
    fstream myfile ("database.txt", std::ios_base::app );
  		if (myfile.is_open())
  		{
	   int i=0;
  	myfile <<"\n";
  			
	cout << "Enter Reciept Number: ";
    cin >> store1->reciept_number;
    myfile<< store1->reciept_number;
	cout<< "Enter Customer Name: ";
	cin>> store1->customerName;
	myfile<< setw(20)<<store1->customerName;
	
	//for date
	time_t now = time(0);
	char* datetime = ctime(&now);	
	cout<<"Date : "<<datetime;
	
	store1->date = datetime;
	
	//date
	cout << "How many Medicine would you like to order (maximum entry upto 10):"<< endl;

	cout << "  " ;
	cin >> store1->numentry;
	if (store1->numentry >10)
	{
		cout << "The Medicine you order is exceed the maximum amount of order !";
		system("pause");
	}
	else{
	for (int i=0; i<store1->numentry; i++)
	{
		
		cout << "Please enter the drug id : "<<endl;
		cin>> store1->drug_ID[i];
        cout<< "Medicine Name: " <<store1->medicineName[store1->drug_ID[i]-1]<<endl;
        myfile<<setw(30)<<store1->medicineName[store1->drug_ID[i]-1];
        cout << "How many medicine do you want: ";
        cin >> store1->quantity[i];
        myfile<< setw(10)<<store1->quantity[i];
        store1->amount[i] = store1->quantity[i] * store1->amount_in_birr[store1->drug_ID[i]-1];
        cout << "The amount You need to pay is: " << store1->amount[i]<<" Birr"<<endl;
        myfile <<setw(15) << store1->amount[i]<<" Birr";
        
        system("PAUSE");
                      
	}
	cout<<"---------------------------------------------------------------------------"<<endl;
    cout << "Order Taken Successfully"<<endl;
    cout<<endl;
    cout << "Go to Reciept Menu to Pay The Bill"<<endl;
    cout<<"----------------------------------------------------------------------------"<<endl;
	system ("PAUSE");


 	}
 	
 	myfile.close();
 	}
 	 else { cout << "Unable to process your order"; }



    store1->new_store=NULL;
	if(store2!=NULL)
	{
		store1->new_store=store2;
	}
	store2=store1;
	system("cls");

}//End function purchase



void pharmacy::modify()		//function to modify order
{
 system("cls");
 int ch, sid;  // sid represent a temporary id number to check it with the reciept number 
 bool found;
 found = false;
 store1 = store2;
 cout<<"Enter Receipt Number To be Modified: ";
 cin>>sid;
 if (store1==NULL || sid==0)
 {
    cout<<"NO RECORD TO MODIFY..!"<<endl;
 }

 else
 {
 	while(store1 !=NULL && !found)
	{
		if (store1->reciept_number==sid)
		{
			found = true;
		}
		else
		{cout<<"you enter invalid receipt number"<<endl;
			store1 = store1 -> new_store;
		}
    if (found)
    {
    
    fstream myfile ("database.txt", std::ios_base::app );
  		if (myfile.is_open())
  		{
	   int i=0;
  	myfile <<"\n";
  	
	cout << "Change  Reciept  Number: ";
    cin >> store1->reciept_number;
    myfile<<setw(20)<<store1->reciept_number;
	cout<< "Change Customer Name: ";
	cin>> store1->customerName;
	myfile<<setw(20)<<store1->customerName;
	
		//for date
	time_t now = time(0);
	char* datetime = ctime(&now);	
	cout<<"Changed date : "<<datetime;
	
	
	
	cout << "How many  Medicine would you like to Change (Maximum entry is 10):"<< endl;
	cout << "  " ;
	cin >> store1->numentry;
	if (store1->numentry >10)
	{
		cout << "The Medicine you order exceeds the maximum amount of order !";
		system("pause");
	}
	else{
	for (int i=0; i<store1->numentry; i++)
	
	{  	string printdoc;
	fstream inputFile;        // Input file stream object
	inputFile.open ("medicinelist.txt");
	
	if(inputFile.is_open()){
		while ( getline (inputFile,printdoc) )
		{
		//Printing the output of the file contents
		cout << printdoc << '\n';
		}
				cout<<endl;
		        inputFile.close();
		    }
		
		cout << "Please enter the new drug id : "<<endl;
		cin>> store1->drug_ID[i];
        cout<< "New Medicine Name: " <<store1->medicineName[store1->drug_ID[i]-1]<<endl;
        myfile<<setw(20)<<store1->medicineName[store1->drug_ID[i]-1];
        cout << "How many new medicine do you want: ";
        cin >> store1->quantity[i];
        myfile<<setw(20)<<store1->quantity[i];
        store1->amount[i] = store1->quantity[i] * store1->amount_in_birr[store1->drug_ID[i]-1];
        cout << "The new amount You need to pay is: " << store1->amount[i]<<" Birr"<<endl;
        myfile<<setw(20)<<store1->amount[i]<<" Birr";
        myfile<<"..... MODIFIED";
        system("PAUSE");
	}
	store1 = store1->new_store;
	system("cls");
	
	}

	 cout<<"RECORD MODIFIED....!"<<endl;
	 }
 
 	myfile.close();
 	}
 	 else { cout << "Unable to modify"; }
}
}
}		//End modify function


void pharmacy::delete_order()	//function to delete_order
{
	system("cls");
	int did, count; // did stands for deleted id, uses in comparision with reciept number
    cout<<"Enter the receipt number you want to delete \n";
    cin>>did;
    collection *delete_ptr;
	collection *store1;
	bool found;

	if(store2 == NULL)
		cout<<"Can not delete from an empty list.\n";
	else
	{
		if(store2->reciept_number == did)
		{
			delete_ptr = store2;
			store2 = store2->new_store;
			count--;
			if(store2 == NULL)
			last = NULL;
			delete delete_ptr;
			cout<<"The Reciept is Deleted Successfully"<<endl;
		}
		else
		{
			found = false;
			store1 = store2;
			delete_ptr = store2->new_store;
	
		while((!found) && (delete_ptr != NULL))
		{
  			if(delete_ptr->reciept_number != did) 
			{
				store1 = delete_ptr;
				delete_ptr = delete_ptr-> new_store;
			}
			else
				found = true;
		}

			if(found)
			{
				store1->new_store = delete_ptr->new_store;
				count--;

				if(last == delete_ptr) 
				last = store1;
				delete delete_ptr;
				cout<<"The Reciept is Deleted Successfully"<<endl;
			}
			else
				cout<<"Item to be deleted is not in the list."<<endl;
			}
		} 
}	//End function delete_order


void pharmacy::completePayment()		//Function to display receipt
{
	int num, pid;	
	bool found;			//variable to search 
	system("cls");
	collection *store1;

	store1=store2;
	found = false;
	
	cout<<" Enter the Reciept Number To complete the payment\n";
	cin>>pid; // reciept number
	cout<<"\n";
	

	if(store1 == NULL) //Invalid receipt code
	{
		cout << "\tThere is no Order to show\n\t\t\tSo The List is Empty\n\n\n";
	}
	while(store1 !=NULL && !found)  // else
	{
		if (store1->reciept_number==pid)
		{
			found = true;
		}
		else
		{
			store1 = store1 -> new_store;
		}
        if (found)	//print the receipt
        {	cout<<""<<endl;
	        cout <<"\t\tHere is the Order list\n"; 
	        cout<<endl;
	        
		cout <<"Reciept Number : "<<store1->reciept_number;
		cout <<"\n";
		cout<<"Customer Name: "<<store1->customerName<<endl;
				
		cout<<"Order Date : "<<store1->date<<endl;
				
		cout<<"_______________________________________________________________"<<endl;
		
		cout << "" << endl;
		cout << "|     Medicine Name    |  	Quantity     |   Total Price |" << endl;
		cout << "_____________________________________________________________" << endl;
		for (int i=0;i<store1->numentry;i++)
		{
			//cout << temp->type <<"  \t\t";
			cout<<store1->medicineName[store1->drug_ID[i]-1]<<"\t\t\t  ";
			cout<<store1->quantity[i] <<"\t\t";
			cout<< store1->amount[i]<<" Birr"<<endl;
			cout<<"____________________________________________________________"<<endl;
		}
		
		store1->total = store1->amount[0]+store1->amount[1]+store1->amount[2]+store1->amount[3]+store1->amount[4]+store1->amount[5]+store1->amount[6]+store1->amount[7]
						+store1->amount[8]+store1->amount[9];
		cout<<"Total Bill is : "<<store1->total;
		cout<<"\n"<<endl;
	
	// calculation

		cout << "Type the exact amount You need to pay: ";
        cin >> num;
        if(num > store1 -> total)
         {
         	cout<< num - store1 -> total << " Will be returned!";
		 }
		 else if ( num < store1 -> total)
		 {
		 	cout<< "Please add "<<store1 -> total - num << " birr" <<endl;
		 	
		 }
		 else 
		 {
		 	cout<<"Payment Done\nThank You\n";  
		 }
		 


		cout <<"\n";
		cout <<"\n";
		cout <<"\n_______________________________________________________________________________\n";
		}


}
}	//End function order_list



//Admin 

void pharmacy::admin()		//function to take_order
{
	pharmacy medicine;
	int menu;
   	do
	{
		system("cls");

		cout<<"1. Daily Summary of total Sale"<<endl;
		cout<<"2. Exit"<<endl<<endl<<endl;

		cout<<"Enter your choice: ";

		cin>>menu;

		switch (menu)
		{

		case 1:
			{
				medicine.daily_summary();	//function daily_summary
				system("PAUSE");
				break;
			}	//end case 1
			

        case 2:
			{
				medicine.exit();	//function exit
			
				break;
			}	//end case 2

		
		default:
			{
				cout<<"You enter invalid input\nre-enter the input\n"<<endl;
				break;
			}//end defeault
		}//end Switch
	}while(menu!=2);//end do
	
} // end of admin


//Admin functions 


//Function to display Daily Summary
void pharmacy::daily_summary()		
{
	
	system("cls");
	cout<<endl;
	
	//print from file
	string printdoc;
	fstream inputFile;        // Input file stream object
	inputFile.open ("database.txt");
	
	if(inputFile.is_open()){
		while ( getline (inputFile,printdoc) )
		{
		//Printing the output of the file contents
		cout << printdoc << '\n';
		}
				cout<<endl;
		        inputFile.close();
		    }
    else{
        cout << "No data table to show" << endl; }
        
   
}		//End daily summary


//Exit function common to both customer and admin part
void pharmacy::exit() //Function to exit
{
		
    main();
	cout<<"\nYou choose to exit.\n"<<endl;
	cout<<"thank you"<<endl;
}	//end function exit

