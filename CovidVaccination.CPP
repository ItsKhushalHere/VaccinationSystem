#include <bits/stdc++.h>
#include<conio.h>
#include<windows.h>
#include<fstream>

using namespace std;
#define SIZE 30
#define SS 3
void UserOperation(string,string,int);
string  convertDate(int,int,int);

class User{

    char usrname1[SIZE],pwd1[SIZE],name[SIZE];
    int phno,adhno,v=0;
public:
    void Register();
    string GetUserName(){
        return usrname1;
    }
    string GetPass(){
        return pwd1;
    }
    int getV(){
        return v;
    }
    void Display();
    void setV1(){
        v=1;
    }
    void setV0(){
        v=0;
    }
};

void User::Display(){
    cout<<"\n "<<usrname1<<"\t\t "<<pwd1<<"\t\t "<<name<<"\t "<<v;
}
void User::Register(){
    system("cls");
    cout<<"\n \t\t\t****************** Register ******************";
    cout<<"\n \t\t\t\t Set UserName :";
    cin>>usrname1;
    cout<<"\n \t\t\t\t Set Password :";
    cin>>pwd1;
    Sleep(1000);
    system("cls");
    cout<<"\n \t\t\t****************** Personal Details ******************";
    cout<<"\n \t\t\t\t Name :";
    cin>>name;
    cout<<"\n \t\t\t\t Mobile :";
    cin>>phno;
    cout<<"\n \t\t\t\t Adhar Number :";
    cin>>adhno;
    cout<<"\n \t\t\t\t Registering...";
    Sleep(500);
    system("cls");
    cout<<"\n\n \t\t\t\t You are Registered Successfully!";
    Sleep(1000);
    system("cls");
}

class Date{
    char usrnameD[SIZE]={'\0'};
    int date=0,slot=0;
public:
    int getDate(){
        return date;
    }
    int getSlot(){
        return slot;
    }
    string getUser(){
        return usrnameD;
    }
    void DateUpdate(int d,string s,int c){
        date=d;
        slot=c;
        //cout<<"\n \t\t before Usrname:"<<usrnameD;
        for(int i=0;i<(int)s.size();i++)
            {
                //cout<<"\n\t\t S[i] :"<<s[i];
                usrnameD[i]=s[i];
                //cout<<"\n\t\t U[i] :"<<usrnameD[i];
            }
        //cout<<"\n \t\t usrnameClass:"<<usrnameD;
    }
};

void getDateAndSlot(int a[2]){
    int dateT=a[0], s1=a[1];
    if(dateT==0&&s1==0){
        s1++;
        dateT=20210425;
    }
    else if(s1%SS!=0){
        s1++;
    }
    else{
        int dd=dateT%100;
        dateT/=100;
        int mm=dateT%100;
        dateT/=100;
        int flag=0;
        if(mm==1||mm==3||mm==5||mm==7||mm==8||mm==10||mm==12){
            dd++;
            if(dd>31){
                dd=1;
                flag=1;
            }
        }
        else if(mm==4||mm==6||mm==9||mm==11){
                dd++;
                if(dd>30){
                    dd=1;
                    flag=1;
                }
        }
        else if(mm==2){
            bool leap;
            if(dateT%400 == 0)
                leap=true;
            if(dateT%100 == 0)
                leap= false;
            if(dateT%4 == 0)
                leap=true;
            if(leap){
                dd++;
                if(dd>29){
                    dd=1;
                    flag=1;
                }
            }
            else{
                dd++;
                if(dd>28){
                    dd=1;
                    flag=1;
                }
            }
        }
        int flag2=0;
        if(dd==1&&flag==1)
        {
            mm++;
            if(mm>12){
                mm=1;
                flag2=1;
            }
        }
        if(mm==1&&flag2==1)
            dateT++;
        dateT=dateT*10000+mm*100+dd;
        s1++;
    }
    a[0]=dateT;
    a[1]=s1;
}

void upDate(string usr){
   Date d;
    ifstream f("date.dat", ios::in|ios::binary);
    ofstream fout("TempDate.dat", ios::out|ios::binary);
    int isInserted = 0, a[]={0, 0};
    while(f.read((char*)&d, sizeof(d))){
        if(!isInserted && d.getSlot()-a[1]!=1){
            getDateAndSlot(a);
            Date d2;
            d2.DateUpdate(a[0], usr, a[1]);
            fout.write((char*)&d2,sizeof(d2));
            isInserted=1;
        }
        fout.write((char*)&d,sizeof(d));
        a[0]=d.getDate();
        a[1]=d.getSlot();
    }
    if(!isInserted){
            getDateAndSlot(a);
            Date d2;
            d2.DateUpdate(a[0], usr, a[1]);
            fout.write((char*)&d2,sizeof(d2));
            isInserted=1;
    }
    f.close();
    fout.close();
    remove("date.dat");
    rename("TempDate.dat", "date.dat");
    //cout<<"\n \t\t Date: "<<a[0]<<"\n\t\t Slot:" <<a[1];
    //getch();
}
void reg(){
    User u;
    u.Register();
    ofstream fout("User.dat",ios::binary|ios::out|ios::app);
    fout.write((char*)&u,sizeof(u));
    fout.close();
}

void login(int ch){
    system("cls");
    cout<<"\n \t\t\t****************** Login ******************";
    cout<<"\n";
    string usr,pswd;
    cout<<"\n \t\t\t\t USERNAME :";
    cin>>usr;
    cout<<"\n \t\t\t\t PASSWORD :";
    cin>>pswd;
    int flag=0;
    User u;
    ifstream fin;
    fin.open("User.dat",ios::in|ios::binary);
    while(fin.read((char*)&u,sizeof(u))){
            if(u.GetUserName()==usr&&u.GetPass()==pswd){
                cout<<"\n \t\t\t\t LoggedIn Successfully";
                Sleep(1000);
                flag=1;
                break;
            }
    }
    fin.close();
    if(flag)
        UserOperation(usr,pswd,u.getV());
    else{
        cout<<"\n \t\t\t\t Incorrect Username or Password";
        Sleep(1000);
    }
}

void CancelRegistration(string usr){
   // cout<<"\n Cancel";
    ifstream fin("date.dat",ios::in|ios::binary);
    ofstream fout("date1.dat",ios::out|ios::app|ios::binary);
    Date d1;
    while(fin.read((char*)&d1,sizeof(Date))){
        if(d1.getUser()!=usr){
            fout.write((char*)&d1,sizeof(Date));
        }
    }
    fin.close();
    fout.close();
    remove("date.dat");
    rename("date1.dat","date.dat");
   // getch();
}

void UserOperation(string usr,string pswd,int v){
    system("cls");
    if(v==0){
        cout<<"\n \t\t\t****************** Dashboard ******************\n";
        cout<<"\n \t\t\t\t\t Welcome "<<usr<<"!";
        cout<<"\n\n \t\t\t You have not registered for vaccination till now.";
        cout<<"\n \t\t\t\t Register(y/n) :";
        char ch;
        cin>>ch;
        if(ch=='y'||ch=='Y'){
            User u;
            fstream f("User.dat",ios::in|ios::out|ios::binary);
            f.seekg(0);
            while(f.read((char*)&u,sizeof(u))){
                    if(u.GetUserName()==usr&&u.GetPass()==pswd){
                            u.setV1();
                            f.seekp(f.tellg()-sizeof(u));
                            f.write((char*)&u,sizeof(u));
                            upDate(usr);
                            break;
                    }
            }
            f.close();
            cout<<"\n \t\t\t You have been registered for vaccination!";
            Sleep(1000);
        }
        else{
            system("cls");
            cout<<"\n \t\t\t\t LoggingOut...";
            Sleep(1000);
            return;
        }
    }
    int date=0,slot=0;
    Date d;
    ifstream fin("date.dat",ios::in|ios::binary);
    while(fin.read((char*)&d,sizeof(d))){
            if(d.getUser()==usr){
                date=d.getDate();
                slot=d.getSlot();
                break;
            }
    }
    fin.close();
    int dd=date%100;
    date/=100;
    int mm=date%100;
    date/=100;
    string temp;
    temp=convertDate(mm,dd,date);
    char ch='0',x;
    do{
        if(ch!='1'&&x!='1'){
            system("cls");
            cout<<"\n \t\t\t****************** Dashboard ******************\n";
            cout<<"\n \t\t\t\t\t Welcome "<<usr<<"!";
            cout<<"\n\n\t\t\t\t Vaccination Date \t\t Slot ";
            cout<<"\n \t\t\t\t   "<<temp;
            cout<<"\t\t\t   "<<ceil((float)slot/SS);
        }
        if(ch!='2'){
            if(x=='1'){
                system("cls");
                cout<<"\n \t\t\t****************** Dashboard ******************\n";
                cout<<"\n \t\t\t\t\t Welcome "<<usr<<"!";
                cout<<"\n\n \t\t\t Registration Canceled! Login to register again.";
            }
            cout<<"\n\n\t\t\t\t\t 1)Cancel Registration";
            cout<<"\n \t\t\t\t\t 2)Logout";
            cout<<"\n \t\t\t\t\t\t:";
             cin>>ch;
        }
        if(ch=='1'){
            CancelRegistration(usr);
            User u;
            fstream f("user.dat",ios::in|ios::out|ios::binary);
            f.seekg(0);
            while(f.read((char*)&u,sizeof(u))){
                    if(u.GetUserName()==usr&&u.GetPass()==pswd){
                            u.setV0();
                            f.seekp(f.tellg()-sizeof(u));
                            f.write((char*)&u,sizeof(u));
                            break;
                    }
            }
            system("cls");
            cout<<"\n \t\t\t****************** Dashboard ******************\n";
            cout<<"\n \t\t\t\t\t Welcome "<<usr<<"!";
            cout<<"\n\n \t\t\t Registration Canceled! Login to register again.";
            x='1';
        }
        else if(ch=='2'){
             system("cls");
             cout<<"\n \t\t\t\t LoggingOut...";
             Sleep(1000);
        }
    }while(ch!='2');
}

int main()
{
    char ch;
    do{
        system("cls");
        cout<<"\n \t\t\t****************** Welcome ******************";
        cout<<"\n \t\t\t\t 1)Login";
        cout<<"\n \t\t\t\t 2)Register";
        cout<<"\n \t\t\t\t 3)Exit";
        cout<<"\n \t\t\t\t\t :";
        cin>>ch;
        if(ch=='1')
            login(ch);
        else if(ch=='2')
            reg();
        else if(ch>'3'||ch<'1')
            cout<<"\n \t\t\t Wrong Input!";
    }while(ch!='3');

    return 0;
}



string  convertDate(int month,int day,int year)
{
    string ans;
    if(day<=9){
        ans+="0";
    }
    ans+=to_string(day)+" ";
    switch(month)
   	{
		case 1:
      			ans+="JAN ";
      			break;
		case 2:
      			ans+="FEB ";
      			break;
		case 3:
      			ans+="MAR ";
      			break;
		case 4:
     			ans+="APR ";
      			break;
		case 5:
      			ans+="MAY ";
      			break;
		case 6:
      			ans+="JUN ";
      			break;
		case 7:
      			ans+="JUL ";
      			break;
		case 8:
      			ans+="AUG ";
      			break;
		case 9:
      			ans+="SEP ";
      			break;
		case 10:
      			ans+="OCT ";
      			break;
		case 11:
      			ans+="NOV ";
      			break;
		case 12:
      			ans+="DEC ";
      			break;
   	}
   	ans+=to_string(year);
   	return ans;
}
