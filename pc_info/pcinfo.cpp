#include  <iostream>
#include  <sys/types.h>
#include <string>
#include <unistd.h> //execvp
#include<sys/wait.h> //wait fn

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

int main(int argc, char* argv[]) {

    string pwd=exec("pwd");
    pwd=pwd.substr(0,pwd.length()-1)+"/pc_info/";
    string cpu="python3 "+pwd+"cpu.py";
    string df="python3 "+pwd+"df.py";

    //functionalities :
    //overall space
    //Cpu information
    // A file system with date, size, last used
    // A GUI for displaying these information (allows delete)
    system("cat /proc/cpuinfo > ~/cpuinfo_.txt");
    system(("mv cpuinfo_.txt "+pwd).c_str());
    system("df > df.txt");
    system(("mv df.txt "+pwd).c_str());
    system(cpu.c_str());
    system(df.c_str());

	return 0;
}