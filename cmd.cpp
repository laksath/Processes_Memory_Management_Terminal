#include <iostream>
#include <sys/types.h>
#include <string>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <signal.h>
#include <sys/ioctl.h>
#include <stdio.h>
#include <unistd.h>
#include <vector>
#include "conio.h"
#include <memory>
#include <fstream>
#include <algorithm>

using std::ifstream;
using std::ofstream;

using namespace std;

string exec(string command) {
   char buffer[1024];
   string result = "";

   // Open pipe to file
   FILE* pipe = popen(command.c_str(), "r");
   if (!pipe) {
      return "popen failed!";
   }

   // read till end of process:
   while (!feof(pipe)) {

      // use buffer to read and add to result
      if (fgets(buffer, 1024, pipe) != NULL)
         result += buffer;
   }

   pclose(pipe);
   return result;
}

int get_cmd_width(){
    struct winsize w;
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
    return w.ws_col;
}

void print_center(string welcome){
    int l = welcome.length();
    int x = get_cmd_width();
    string str="";
    for(int i=0;i<(int) ((x-l)/2);i++){
        str+=' ';
    }
    str+=welcome;
    for(int i=0;i<(int) ((x-l)/2);i++){
        str+=' ';
    }
    str="\n"+str+"\n\n";
    cout<<"\e[48;2;0;0;0m\033[1;33m"+str+"\033[0m";
}

int prevent_arrows(char ch){
   if(ch == '\033'){ // if the first value is esc
        getch_(); // skip the [
        switch(getch_()) { // the real value
        case 'A':
            // code for arrow up
            return 8;
        case 'B':
            // code for arrow down
            return 2;
        case 'C':
            // code for arrow right
            return 6;
        case 'D':
            // code for arrow left
            return 4;
        }
   }
   return 0;
}

string convertToString(char* a, int size){
    int i;
    string s = "";
    for (i = 0; i < size; i++) {
        s = s + a[i];
    }
    return s;
}

int pcinfo(string pwd,string curr_dir) {

    //functionalities :
    //overall space
    //Cpu information
    // A file system with date, size, last used
    // A GUI for displaying these information (allows delete)
    string cpu_info="cat /proc/cpuinfo > "+pwd+"/pc_info/cpuinfo_.txt";
    system(cpu_info.c_str());
    
    // system(("mv cpuinfo_.txt "+pwd).c_str());

    string df_s="df > "+pwd+"/pc_info/df.txt";
    system(df_s.c_str());

    // system(("mv df.txt "+pwd).c_str());
    string new_dir=pwd+"/pc_info/";
    // cout<<"**"<<new_dir<<"**"<<"\n";

    // string curr_dir=exec("pwd").substr(0,pwd.length()-1);
    // cout<<"*"<<curr_dir<<"*"<<"\n";

    chdir(new_dir.c_str());

    // system(new_dir.c_str());
    // system("pwd");
    string cpu="python3 cpu.py";
    string df="python3 df.py";
    system(cpu.c_str());
    system(df.c_str());

    chdir(curr_dir.c_str());

	return 0;
}

void findall(string pwd,string curr_dir){
    // string new_dir=pwd+"/pc_info/";
    chdir(pwd.c_str());

    string findall_="python3 findall.py "+curr_dir;
    system(findall_.c_str());

    chdir(curr_dir.c_str());
}

vector<string> tokenize(string s, string del = " "){
    int start = 0;
    int end = s.find(del);
    vector<string> vect;
    while (end != -1) {
        vect.push_back(s.substr(start, end - start));
        // cout << s.substr(start, end - start) << endl;
        start = end + del.size();
        end = s.find(del, start);
    }
    vect.push_back(s.substr(start, end - start));
    // cout << s.substr(start, end - start);
    return vect;
}

string remove_spaces(const string &s){
  int last = s.size() - 1;
  while (last >= 0 && s[last] == ' ')
    --last;
  return s.substr(0, last + 1);
}

bool BothAreSpaces(char lhs, char rhs) { return (lhs == rhs) && (lhs == ' '); }

vector<string> manager_change_read_write(string pwd,string content){
    for(int i=0;i<content.length();i++){
        if(content[i]=='t' && content[i+1]=='o' && content[i+2]=='p'){
            content=content.substr(i,content.length());
            break;
        }
    }
    
    // std::string::iterator new_end = std::unique(content.begin(), content.end(), BothAreSpaces);
    // content.erase(new_end, content.end());  

    string pwd2 = pwd+"/mem_stat/"; 
    chdir(pwd2.c_str());
    ofstream outdata; // outdata is like cin

    outdata.open("mem_stat.txt"); // opens the file
    if(!outdata) { // file couldn't be opened
        cerr << "Error: file could not be opened" << endl;
        exit(1);
    }
    for (int i=0;i<content.length();i++)
        outdata << content[i];
    outdata.close(); 

    vector<string> vect;

    fstream newfile;
    newfile.open("mem_stat.txt",ios::in); //open a file to perform read operation using file object

    if (newfile.is_open()){ //checking whether the file is open
      string tp;
      while(getline(newfile, tp)){ //read data from file object and put it into string.
        tp=remove_spaces(tp);
        cout << tp << "\n"; //print the data of the string
        vect.push_back(tp);
      }
      newfile.close(); //close the file object.
   }

    return vect;
}

void manager(string content,string pwd,string curr_dir){
    vector<string> vect = manager_change_read_write(pwd,content);

    string x;
    int x2=0;
    cout<<"1 Advanced Option\n";
    cout<<"2 Kill a process \n";
    cout<<"3 Exit \n";

    while(1){
        int j=0;
        cin>>j;
        if(j==0){
            vect = manager_change_read_write(pwd,content);

            cout<<"1 Advanced Option\n";
            cout<<"2 Kill a process \n";
            cout<<"3 Exit \n";

            cin>>j;
        }else if(j==1){
            system("htop");
        }else if(j==2){

            cout<<"Type:\n 1 -> Enter the application's name to terminate \n 2 -> PID to terminate\n";
            
            int type;
            cin>>type;

            while(type!=1 && type !=2){
                cout<<"Invalid type.Try again\n";
                cin>>type;
            }

            if(type==1){
                cout<<"Enter the application's name to be terminated : \n";
                string name;
                cin>>name;
                cout<<"\n\nTHE FOLLOWING PROCESSES MUST BE TERMINATED : \n\n";
                for(int i=0;i<vect.size();i++){
                    if(vect[i].find(" "+name+" ") != string::npos){
                        cout<<vect[i];
                        int l = 80;
                        cout<<" ";
                        while(l>=0 && l--) cout<<"-";
                        cout<<"\n";
                    }
                }
                cout<<"\n\n\n";
            }else if (type==2){
                cout<<"Enter the process ID to be terminated : \n";
                string pid;
                cin>>pid;
                string kill = "kill -9 "+pid;
                system(kill.c_str());
            }

            cout<<"0 Refresh process Manager\n";
            cout<<"1 Advanced Option\n";
            cout<<"2 Kill a process \n";
            cout<<"3 Exit \n";

        }else if(j==3){
            break;
        }else{
            cout<<"Invalid Option\n";
        }
    }

    chdir(curr_dir.c_str());
}

int main(){
    char command_char[100];
    system("clear");
    string welcome = "WELCOME TO INFORMATION TERMINAL";
    string pwd_ini="";
    print_center(welcome);
    while(1){
        string pwd=exec("pwd");
        if(pwd_ini==""){
            pwd_ini=pwd.substr(0,pwd.length()-1);
        }
        pwd=pwd.substr(0,pwd.length()-1)+">>>";
        // cout<<pwd_ini<<"**\n";
        cout<<"\e[48;2;0;0;0m\033[1;33m"+pwd+"\033[0m";
        int itr ;
        int cont=0;
        for(itr=0;itr<100;itr++){
            command_char[itr]=getch_();
            if((int) command_char[itr]==127){
                cout<<"\nKeyboard interrupt❗\n";
                cont=1;
                break;  
            }else if(prevent_arrows(command_char[itr])!=0){
                cout<<"\nKeyboard interrupt❗\n";
                cont=1;
                break;
            }
            else if(command_char[itr]!='\n'){
                printf("%c",command_char[itr]);
            }else{
                command_char[itr]='\0';
                cout<<"\n";
                break;
            }
        }
        if(cont==1) continue;
        string command =  convertToString(command_char, itr / sizeof(char));
        if(command=="pcinfo"){
                // string dir_loc = pwd_ini+"/pc_info";
                // cout<<dir_loc<<"\n";
                // string command_pcinfo="g++ "+dir_loc+"/pcinfo.cpp -o "+dir_loc+"/pcinfo.out";
                // cout<<command_pcinfo<<"\n";
                // system(command_pcinfo.c_str());
                // string move = "mv pcinfo.out "+dir_loc;
                // system(move.c_str());
                // cout<<move;
                // string command_pcinfo_run=dir_loc+"/pcinfo.out";
                // system(command_pcinfo_run.c_str());
                pcinfo(pwd_ini,pwd.substr(0,pwd.length()-3));
        }else if(command=="findall"){
            findall(pwd_ini,pwd.substr(0,pwd.length()-3));
        }else if(command=="exit"){
            exit(0);
        }else if(command.length()>=3 && command.substr(0,3)=="cd "){
            if(chdir(command.substr(3,command.length()-3).c_str())==-1){
                cout<<"\e[48;2;0;0;0m\033[1;31m❗INVALID DIRECTORY.PLEASE TRY AGAIN.❗\n\033[0m";
            }
        }else if(command=="manager"){
            string s = exec("top");
            manager(s,pwd_ini,pwd.substr(0,pwd.length()-3));
        }else{
            system(command.c_str());
        }
    }
    return 0;
}