#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <conio.h>

//Used For Replacing The Line
void ReplaceLine(const std::string& ToReplace,const std::string&& Main){
    std::vector<std::string>Content;
    std::string s;
    std::ifstream File("contacts.txt");
    while(getline(File,s)){
        if(s==ToReplace){
            s=Main;
        }
        Content.push_back(s);
    }
    std::ofstream writer("contacts.txt",std::ostream::trunc);
    for(std::string& s:Content){
        writer<<s<<std::endl;
    }
}

//Editing The Contact
void EditContact(const std::string& ID){
    std::string NewName,NewNumber;
    std::cout<<"Enter A New Name : ";
    std::cin>>NewName;
    std::cout<<"Enter A New Number : ";
    std::cin>>NewNumber;
    NewName+=" ";
    ReplaceLine(ID,NewName+NewNumber);
}

//Adding New Contact
void AddContact(const std::string&& ID){
    std::ofstream File("contacts.txt",std::ios_base::app);
    std::string s;
    std::ifstream reader("contacts.txt");
    char Confirmation;
    while(getline(reader,s)){
            if(ID==s){
            std::cout<<"Contact Already Exist!\n"<<"Do You Want To OverWrite?[Y/N]"<<std::endl<<">>";
            std::cin>>Confirmation;
            if(Confirmation=='Y'){
                system("clear");
                EditContact(ID); 
                std::cout<<"Contacts Overriden"<<std::endl;
                system("pause");
                File.close();
                return;
            }
            else{
                std::cout<<"Contacts Aren't Touched"<<std::endl;
                system("pause");
                File.close();
                return;
            }
        }
    }
    File<<ID<<std::endl;
    std::cout<<"New Contact Has Been Added"<<std::endl;
    system("pause");
    File.close();
}

//Deleting A Contact
void DeleteContact(const std::string&& ToDlt){
    std::vector<std::string>Contact;
    std::string s;
    bool Deleted=false;
    std::ifstream Reader("contacts.txt");
    while(getline(Reader,s)){
        if(s==ToDlt){
            Deleted=true;
            continue;
        }
        Contact.push_back(s);
    }
    std::ofstream Writer("contacts.txt",std::ios_base::trunc);
    for(std::string&k : Contact){
        Writer<<k<<std::endl;
    }
    if(!Deleted){
        std::cout<<"Contact Didn't Existed!"<<std::endl;
    }
    else{
        std::cout<<"Contact Has Been Deleted"<<std::endl;
    }
}

//Searching A Contact This Wont Be Called Directly
int Search(const std::string& Query){
    int Count=0;
    bool IsNum=false;
    if(isdigit(Query[0])){
        IsNum=true;
    }
    std::ifstream reader("contacts.txt");
    std::string Name,Number;
    std::string s;
    while(getline(reader,s)){
        std::stringstream Extractor(s);
        Extractor>>Name>>Number;
        if(IsNum==true){
            if(Number.find(Query)!=std::string::npos){
                Count++;
                std::cout<<"NAME : "<<Name<<"   "<<"NUMBER : "<<Number<<std::endl;
            }
        }
        else{
            if(Name.find(Query)!=std::string::npos){
                Count++;
                std::cout<<"NAME : "<<Name<<"  "<<"NUMBER : "<<Number<<std::endl;
            }
        }
    }
    return Count;
}

//This Is Used To Take Inputs For Searching
void Query(){
    std::string Query="";
    std::cout<<"Contact Search"<<std::endl;
    std::cout<<">>";
    while(true){
        char s=getche();
        //If User Presses Enter Case It Worked Atleast for mine
        if(int(s)==10){
            return;
        }
        //Handling BackSpace Case Worked In Mine :)
        if(int(s)==127){
           if(Query.length()==0){
              Query=" ";
              std::cout<<"\b"<<"\b";
           }
           Query.erase(Query.end()-1);
        }
        //Else  Adding Character To Query
        else{
           Query.push_back(s);
        }
        system("clear");
        //The Contacts Get Printed In Search Itself
        int Searched=0;
        Searched=Search(Query);
        if(Searched==0){
            std::cout<<"No Results Found!!"<<std::endl;
        }
        std::cout<<">>"<<Query;
    }
    system("pause");
    system("clear");
}
void EditContact(const std::string&& ID){
    system("clear");
    std::ifstream Reader("contacts.txt");
    std::string S;
    bool Exist=false;
    std::vector<std::string>NewBlocks;
    while(getline(Reader,S)){
        if(S==ID){
            std::string Name,Num;
            std::cout<<"Enter The New Name : ";
            std::cin>>Name;
            std::cin.ignore();
            std::cout<<"Enter The New Number : ";
            std::cin>>Num;
            Name+=" ";
            NewBlocks.push_back(Name+Num);
            Exist=true;
            continue;
        }
        NewBlocks.push_back(S);
    }
    if(!Exist){
        std::cout<<"The Contact You Want To Edit Didn't Exist!!"<<std::endl;
        system("pause");
        return;
    }
    std::ofstream Writer("contacts.txt",std::ios_base::trunc);
    for(std::string& Val:NewBlocks){
        Writer<<Val<<std::endl;
    }
    std::cout<<"Contacts Has Been Edited!!"<<std::endl;
    system("pause");
}

int main()
{
    char Cmnd;
    while(true){
        std::cout<<"~Add A Conatct [1]\n~Delete A Contact [2]\n~Edit A Contact [3]\n~Search A Contact [4]\n>>";
        std::cin>>Cmnd;
        std::cin.ignore();
        if(Cmnd=='1'){
            system("clear");
            std::string Name,Number;
            std::cout<<"Enter Name : ";
            std::cin>>Name;
            std::cin.ignore();
            std::cout<<"Enter Number : ";
            std::cin>>Number;
            Name+=" ";
            AddContact(Name+Number);
            system("clear");
        }
        else if(Cmnd=='2'){
            system("clear");
            std::string Name,Num;
            std::cout<<"Enter The Number : ";
            std::cin>>Num;
            std::cin.ignore();
            std::cout<<"Enter Users Name : ";
            std::cin>>Name;
            Name+=" ";
            DeleteContact(Name+Num);
            system("clear");
        }
        else if(Cmnd=='3'){
            system("clear");
            std::string Name,Num;
            std::cout<<"Enter The Name : ";
            std::cin>>Name;
            std::cin.ignore();
            std::cout<<"Enter The Number : ";
            std::cin>>Num;
            Name+=" ";
            EditContact(Name+Num);
            system("clear");
        }
        else if(Cmnd=='4'){
            system("clear");
            Query();
            system("clear");
        }
        else{
            std::cout<<"Invalid Option!!";
            system("pause");
            system("clear");
        }
    }
}