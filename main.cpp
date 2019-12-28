#include <iostream>
#include<string>
#include <fstream>
#include <sstream>
#include <cstdlib>
#include <iomanip>
#include <vector>
#include <stdlib.h>
#include <cstddef>

using namespace std;
using std::setw;

//print the description of company
void description(){
    cout << " "<< endl;
    cout << setw(40)<<"******************************************************************************"<< endl;
    cout << setw(40)<<"******************************************************************************"<< endl;
    cout << setw(48)<<"WELCOME TO THE "<< endl;
    cout << " " <<endl;
    cout << setw(50)<<"AKURU BOOKSHOP PVT LTD"<< endl;
    cout << " " <<endl;
    cout << setw(50)<<"GROUP OF ABC COMPANIES" << endl;
    cout << " " <<endl;
    cout << setw(40)<<"******************************************************************************"<< endl;
    cout << setw(40)<<"******************************************************************************"<< endl;
    cout << " " <<endl;
}

//display help for the user
int displayHelp(){
    char exit;
    system("cls");
    description();
    cout << "1. Login to the system using your login credentials" << endl;
    cout << "2. Available books in the store are displayed in the home page and then you can choose what you want to do." << endl;
    cout << "3. To purchase books, press no 1 and enter the book details need to buy." << endl;
    cout << "4. The bill is displayed and you can settle the payment." << endl;
    cout << "5. If you want to purchase more you can repeat the purchasing process." << endl;
    cout << "6. To logout from the system press no 3." << endl;
    cout << "\n\n Press Enter to direct to Home : " << endl;
    getchar();
    getchar();
    system("cls");
    return 1;
}

//input item to the stock
void inputItem(ofstream& itemFile)
{
    string category,name;
    double price;

	cout << "Enter the Name(use underscore(_) to enter space ) :" ;
	cin >> name;
	cout << "Enter the Category : ";
	cin >> category;
	cout << "Enter the Price : ";
	cin >> price;
	itemFile<<setw(20)<< "|"+name+"|" << setw(20)<< category <<setw(20)<<price<<' ' << endl;

}

//display all items in the stock
void displayAllItems()
{
    char ch;
	const char *fileName="item.txt";

	ifstream file;
	int item_num=0;
	//open file
	file.open(fileName,ios::in);
	if(!file)
	{
		cout<<"Error in opening file!!!"<<endl;
	}

	cout << left;
	cout <<setw(20) << "Item Number"<<setw(22)<<"Item Name"<<setw(20)<<"Category"<<setw(20)<<"Price(Rs.)" << endl;

	//read and print file content
	cout << ++item_num <<setw(11);
	while (!file.eof())
	{
		file >> noskipws >> ch;	//reading from file
			//printing
		if(ch=='\n'){
            cout <<endl;
            cout << ++item_num <<setw(11);
		}else if(ch!='|'){
            cout << ch;
		}
	}
	//close the file
	cout << right;
	file.close();
}

//delete the item admin needs
void deleteLine(const char *itemFile, int n)
{
    ifstream is(itemFile);
    ofstream os;
    os.open("temp.txt", ofstream::out);
    char c;
    int lineNo = 1;
    while (is.get(c))
    {
        if (c == '\n')
        lineNo++;

        if (lineNo != n)
            os << c;
    }

    os.close();
    is.close();
   remove(itemFile);
   rename("temp.txt", itemFile);
}

//login to the system
int login(){

    string name,password;
    cout << "\nLogin To The System To Proceed";
    cout << " " <<endl;
    cout << " " <<endl;
    cout << "Enter Username : " ;
        cin >> name;
        cout << "Enter Password : " ;
            cin >> password;
            if((name == "admin" ||name =="Admin" ||name == "ADMIN") && password == "123" ){
                system("cls");
                description();
                return 0;
            }else if((name == "user" ||name =="User" ||name == "USER") && password == "456" ){
                system("cls");
                description();

                return 1;
            }else{
                system("cls");
                description();
                return -1;
            }
}


//user
//to get the item name of specific item
string getItemName(string line){

    string f = line.substr(0,line.rfind("|"));
    int n = f.length();
    int q=f.find("|");
    string d= f.substr(q+1,n);
    return d;
}

//to get the price of specific item
double itemValue(string line){
    line = line.substr(0,line.rfind(' '));
	line = line.substr(line.rfind(' '));

	double num1=atof(line.c_str());
    return num1;
 }

 //details of item purchased
string purchaseItem(){
    int num1,counter=1;
    std::string line;
    char ch;
    displayAllItems();
    cout << "\n"<< endl;
    cout << "Enter the Item Number of Item you want to purchase :";
    cin >> num1;
    const char *fileName="item.txt";

	ifstream file;
	file.open(fileName,ios::in);
	if(!file)
	{
		cout<<"Error in opening file!!!"<<endl;
	}
	while (!file.eof()||counter==num1+1)
	{
		file >> noskipws >> ch;

		if(ch=='\n'){
            counter++;
		}
		if(counter==num1){
            line.push_back(ch);
		}
	}
    file.close();
	return line;
}

//calculate and print the bill
void calculateAndPrintBill(){
    int num2;
    double sum=0;
    ofstream itemFile;
    itemFile.open("bill.txt",ios::app);
    do{
    cout <<"Select 1 to add items "<< endl;
    cout <<"Select 2 to print the bill  "<< endl;
    cin >> num2;
    system("cls");
    description();
    //printing bill
    if(num2==2){

            char ch;
	        const char *fileName="bill.txt";
	        ifstream file;
	        file.open(fileName,ios::in);

            if(sum!=0){
            cout << setw(20)<<"AKURU BOOKSHOP"<<endl;
            cout << setw(20)<<"Purchased Items"<<endl;
            cout << left;
            cout << setw(20)<<"Items"<<setw(20)<< "Price" <<endl;

	        if(!file){
            cout<<"Error in opening file!!!"<<endl;
	        }

                while (!file.eof()){
                    file >> noskipws >> ch;
                    if(ch=='\n'){
                        cout <<endl;
                    }else{
                        cout << ch;
                    }
                }
                    cout <<setw(20) <<"Total" <<":" <<setw(20)<< sum << endl;
            }else{
                cout << "Purchase before print the bill.";
            }

	        file.close();
	        file.open("bill.txt", std::ifstream::out | std::ifstream::trunc);
	        file.close();
   //calculating bill
    }else if (num2==1){

        string s=purchaseItem();
        cout << "Enter number of units :";
        int num;
        cin >> num;
        double m=itemValue(s);
        string t=getItemName(s);
        double val =num*m;

        itemFile << left <<setw(20) << t <<":" <<setw(20)<< val << right << endl;
        sum+=val;
        cout << " " << endl;
        cout << "Cost :" << val<< endl;
     }
    }
    while(num2==1);
}

//calculate the cost
double addCost(int num){
    const char *fileName="bill.txt";
    int counter =1;
	ifstream file;
	char ch;
	std::string line;
	file.open(fileName,ios::in);
	if(!file)
	{
		cout<<"Error in opening file!!!"<<endl;
	}
	while (!file.eof()||counter==num+1)
	{
		file >> noskipws >> ch;

		if(ch=='\n'){
            counter++;
		}
		if(counter==num){
            line.push_back(ch);
            cout<< line;
		}
	}
    file.close();

	line = line.substr(0,line.rfind(' '));
	line = line.substr(line.rfind(' '));

	double num1=atof(line.c_str());
	cout << num1;
    return num1;
}

int main(char a,int no)
{
    int no2;
    int exit_code = 5;
    description();
    do{
    if(a!='a'){
        no=login();
    }
    //admin part
    if(no==0){
            displayAllItems();
            do{
                cout << " " << endl;
                cout << " " << endl;
                cout << "Select 1 to Input new item " << endl;
                cout << "Select 2 to Delete an item " << endl;
                cout << "Select 3 to Display items " << endl;
                cout << "Select 4 to Log out  " << endl;
                cout << "Select 5 to Terminate system \n" << endl;
                cin >> no2;
                system("cls");
                description();
                if(no2==1){
                    ofstream itemFile;
                    itemFile.open("item.txt",ios::app);
                    inputItem(itemFile);
                    displayAllItems();
                    itemFile.close();
                }else if(no2==2){
                           int n;
                           displayAllItems();
                           cout << " "<< endl;
                           cout << "Enter Item number of Item you want to delete :" << endl;
                           cin >> n;
                           deleteLine("item.txt",n);
                           system("cls");
                           description();
                           displayAllItems();
                       }if(no2==3){
                           displayAllItems();
                       }if(no2==4){
                           system("cls");
                           main(' ',4);
                       }if(no2==5){
                           _Exit(exit_code);
                       }
                       }while(true);
    }else if(no==1){
        //user part
        int a;
        displayAllItems();
        cout << " "<< endl;
        cout << "Select 1 to Purchase items " << endl;
        cout << "Select 2 to Help " << endl;
        cout << "Select 3 to Log out " << endl;
        cin >> a;
        if(a==1){
            calculateAndPrintBill();
            cout << " " <<endl;
            cout << "Select 1 to continue :" <<endl;
            int n;
            cin >> n;
            system("cls");
            main('a',1);
        }else if(a==3){
            system("cls");
            main(' ',2);
        }else if(a==2){
            int exit;
            exit = displayHelp();
            if(exit==1){
                main('a',1);
            }

        }

    }else{
        cout << "Access Denied.";
        system("cls");
        main(' ',2);
    }
    }while(true);


    return 0;
}
