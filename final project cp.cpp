#include<iostream>
#include<fstream>
#include<string>
using namespace std;

void login();
void registeration();
void forget();
void home(string);
void menu(string);
void create_userhistory(string [],double,int,string);
void show_history(string);
int main(){
	
int choice;
cout<<"\t\t--------------------------------------------------------------------------------\n\n\n";
cout<<"\t\t                            Welcome to our Website                                 \n\n\n";
cout<<"\t\t___________________________________ MENU_________________________________________ \n\n";
cout<<"                                                                                       \n\n";
cout<<"\t| Press 1 to LOGIN                     |"<<endl;
cout<<"\t| Press 2 to REGISTER                  |"<<endl;	
cout<<"\t| Press 3 if you forget your PASSWORD  |"<<endl;
cout<<"\t| Press 4 to EXIT                      |"<<endl;
cout<<"\n\t Please Enter your Choice : ";
cin>>choice;
cout<<endl;

switch (choice)
{
	case 1:
		login();
		break;
		
	case 2:
	    registeration();
		break;
		
	case 3: 
	    forget();
		break;
		
	case 4:
	    cout<<"\t\t\t THANK YOU! \n\n";
		break;
		
	default:
	    system("cls");
	    cout<<"\t\t\t PLEASE SELECT FROM THE OPTIONS GIVEN ABOVE \n"<<endl;
	    main();
	}
	
}

void login()
{

	bool found = false;
	string userID, password, ID , pass;
	system("cls");
	cout<<"\t\t\t Please Enter the username and password : "<<endl;
	cout<<"\t\t\t USERNAME : ";
	cin>>userID;
	cout<<"\t\t\t PASSWORD : ";
	cin>>password;
	
	ifstream input("records.txt");
	
	while(input>>ID>>pass)
	{
		if(ID==userID && pass==password)
		{
			found = true;
			
		}
		}	
	input.close();
	
	if (found)
	{
	home(userID);
	}
	else {
		cout<<"\n LOGIN ERROR \n Please check your username and password\n";
		main();
	}
}
void registeration() {
    string username, password, un, pw;
    bool isfound = false;
    int c, ch;
    system("cls");
    cout << "\t---------------- Welcome To User Registration Page ----------------" << endl
         << endl;

    cout << "\tEnter Your username : ";
    cin >> username;
    cout << "\tEnter Your Password : ";
cin>>password;
    
    ifstream file("records.txt");
    while (file >> un >> pw) {
        if (un == username && pw == password) {
            isfound = true;
            break;
        } else {
            isfound = false;
        }
    }
    file.close();

    if (isfound) {
        cout << endl << "You are already registered." << endl;
        cout << endl << "Press 1 for Login Screen: ";
        cin >> c;
        if (c == 1) {
            login();
        }
    } else {
        ofstream files("record.txt", ios::app);     
        files << username << " " << password << endl;
        files.close();
        cout << endl;
        cout << "\tRegistration Successful! Now you can login and enjoy our services." << endl;
        cout << endl << "Press 1 for Login Screen: ";
        cin >> c;
        if (c == 1) {
            login();
        }
    }
}


void forget()
{
    int option;
    system ("cls");
    cout<<"\t\t\t You forget the password? No worries \n";
    cout<<"Press 1 to search your id by username "<<endl;
    cout<<"Press 2 to go back to the main menu "<<endl;
    cout<<"\t\t\t Enter your choice : ";
    cin>>option;
    switch(option)
    {
    	case 1:
		{
    		int count=0;
    		string suserid,sid,spass;
    		cout<<"\n\t\t\t Enter the username which you remembered : ";
    		cin>>suserid;
    		
    		ifstream f2("records.txt");
    		while(f2>>sid>>spass)
    		{
    			if(sid==suserid)
    			{
    				count=1;
				}
			}
			f2.close();
			if(count==1)
			{
			cout<<"\n\n Your account is found! \n";
			cout<<"\n\n Your password is : "<<spass;
			main();
			}
			else{
				cout<<"\n\t SORRY! your account is not found! \n";
				main();
			}
			break;
		}
		case 2:
			{
				main();
			}
			default:
				cout<<"\t\t\t Wrong option! Please TRY AGAIN! "<<endl;
				forget();
	}
			}			
		
void home(string user){
	int ch;
	cout<<"Enter 1 for Menu"<<endl;
	cout<<"Enter 2 for Order history"<<endl;
	cout<<"Enter 3 for logout"<<endl;
	cout<<"Enter your choice";	
	cin>>ch;
	if(ch == 1){
		menu(user);
	}else if(ch == 2 ){
	show_history( user);
	} else if(ch == 3){
		main();
	}
} 	

void menu(string user){
	
	system("cls");
	string items;
	string iname, item_name;
    int cnt = 0;
    bool isfound = false;
    double iprice = 0;
    double tprice;
    
	int price,count=0;
	 ifstream file("menu.txt");
	while(file>>items>>price){
		cout<<count+1<<"\t"<<left<<items<<" "<<price<<endl;
	count++;
	}
	 string item[count];
	while (true) {
		
        int item_index; // declare item_index variable
        cout << endl << "\tEnter the index of the item you want to buy (1-" << count << "): ";
        cin >> item_index;

        if (item_index == 0) {
       create_userhistory(item, tprice, cnt, user);    
		    break;
        } else if (item_index < 1 || item_index > count) {
            cout << "Invalid item index. Please try again." << endl;
            continue;
        }
        
        item_index--;
        ifstream infile("menu.txt");
        int current_index = 0;
        while (infile >> iname >> iprice) {
            if (current_index == item_index) {
                isfound = true;
                int quantity;
                cout << "Enter the quantity of the item you want to buy: ";
                cin >> quantity;
                tprice += iprice * quantity;
                item[cnt] = iname;
                cnt++;
                break; 
            }
            current_index++;
        }
        if (isfound) {
            cout << "Total Amount is: " << tprice << endl;
        } else {
            cout << "Invalid item index. Please try again." << endl;
        }
    }
}

// user history
void create_userhistory(string item_name[], double price, int count,string username) {
    ofstream outfile("history.txt", ios::app);
    outfile<<username<<" ";
	for(int i =0;i<count;i++){
		outfile<<item_name[i]<<",";
}
       outfile<<" "<<price<<endl;
}
void show_history(string username) {
	system("cls");
    string search_string = username;
    ifstream file("history.txt");
    string line;
    bool isfound = false;
    cout<<"\t---------------- Purchase History ----------------"<<endl<<endl;
    while (getline(file, line)) {
        if (line.find(search_string) != string::npos) {
            cout <<"\t"<< line << endl;
         isfound = true; 
		}
    }    
    if(isfound != true){
    	cout<<"No Purcahase History found "<<endl;
	}
    file.close();
 int c;
 cout<<"Press 0 to go back";
 cout<<endl<<"Press 1 to repeat order";
 cout<<endl<<"Enter your choice : ";
 cin>>c;
 if(c==0){
 	home(username);
 }
}
void billing(string user, double price){
	int c;
}
