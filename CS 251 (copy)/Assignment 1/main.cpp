//Simple CLI 

#include <assert.h>
#include <stdexcept>

#include <stdlib.h>
#include <stdio.h>
#include <fstream>

#include <unistd.h>

#include <iostream>
#include <string>

using namespace std;

static const int INITIAL_NAME_LEN = 80;
string prompt =""; //global prompt string
bool loggedin = false;
bool super = false;

typedef Array ARRAY;

//checks if file exists only
bool fexists(string filename)
{
  ifstream in(filename.c_str());
if( in.is_open())
{
	return true;
  }else
	return false;
}

string getprompt()
 {
  string line;
  ifstream myfile ("enc/misc/prompt.txt");
  
  //gets prompt string
  if (myfile.is_open())
  {
    //while ( myfile.good() )
    //{
      getline (myfile,line); //puts prompt into line
      //cout << line << endl;
    //}
    myfile.close();
  }
   else cout << "Unable to get prompt\n";

  return line + '>';
 
} 

//sets prompt
bool setprompt (string custom)
{ 
  if(custom == "")
  { prompt = getprompt();}
  else {

  	try{
	
	  system("rm enc/misc/prompt.txt");
	  ofstream change;
	  change.open ("enc/misc/prompt.txt");
	  change << custom + "\n";
	  change.close(); 
	  prompt = custom + ">";
	  return true;
	  }catch(...){ return false;}
  }
}

//makes sure prompt always shows
void display (string output)
{ cout << prompt <<" "<< output;}

int grep(std::string filename, std::string keyword)
{
int counter = 0;
std::string line;
ifstream in(filename.c_str());
if( in.is_open())
{
while( getline(in,line) )
{
if( line.find(keyword.c_str()) )
	{cout << "found " << keyword <<" in text file. It is: "<< line<<"\n";
	counter++;}
}
}
return counter;
}

bool Logged()
{ return loggedin;}

bool is_super()
{ return super;}

bool checkpswd(string user, string password)
{
	if(grep("enc/users/"+ user+".txt", password))
	{	
	//	ofstream change;
	  //change.open ("enc/misc/loggedin.txt");
	  //change << custom;
	  //change.close(); 
		

		return true;
	}	
	else
	{
		return false;
	}			
	
}

void login()
{

 if(! Logged())
 {

	string username = "";
	string pswd = "";
	display("Username: ");
	cin >> username;
	display("Password: ");
	cin >> pswd;


	//does user exists? and 

	if(fexists("enc/users/"+ username + ".txt"))
        {
        	if(grep("enc/misc/disabled.txt", username))
		{
			display("Your account has been disabled.\n");
		}		
		else
		{
			if(checkpswd(username, pswd))
			{	
				loggedin = true;
				if(username == "super")
				{ super = true; }
				ofstream change;
				change.open ("enc/misc/loggedin.txt");
				change << username;
				change.close();
				display("You are successfully logged in!\n");
			}
			else
				display("You're password is incorrect.\n");
		}
						
	}
	else
		display("Invalid Username\n");
 }
 else { display("You're not too bright, are you...You are already logged in and you must logout first.\n");}
	
}

void logout()
{
	system("rm enc/misc/loggedin.txt"); 
	loggedin = false;
	if(is_super())
	{ super = false;}
	display("You are successfully logged out!\n");
}

string getuser()
{
  string line = "" ;
  ifstream myfile ("enc/misc/loggedin.txt");
  
  //gets prompt string
  if (myfile.is_open())
  {
    //while ( myfile.good() )
    //{
      getline (myfile,line); //puts prompt into line
      //cout << line << endl;
    //}
    myfile.close();
  }
   else display("Unable to get prompt.\n");

  return line;
	
}

int lineCount(string filename)
{
	int counter = 0;
std::string line;
ifstream in(filename.c_str());
if( in.is_open())
{
while( getline(in,line) )
{
  if(line.find("\n"))
  {	 counter++;

   }
}
}
return counter;
}

int main (int argc, char *argv[]) 
{
  


try
{

//1. see if enc, user, and misc exists already if not create them.
system("mkdir -p enc/users");
system("mkdir -p enc/misc");
}catch (...)
{}

//2. Check for users/super.txt
//if not then create all need start up files

if(!fexists("enc/users/super.txt"))
{
  //create super user
  ofstream myfile;
  myfile.open ("enc/users/super.txt");
  myfile << "password\n";
  myfile.close();

  //create needed misc files
  //a. loggedin.txt
  ofstream myfile2;
  myfile2.open ("enc/misc/loggedin.txt");
  myfile2 << "super\n";
  myfile2.close();
  
  loggedin = true;
  super = true;
  //b. disabled.txt
  ofstream myfile3;
  myfile3.open ("enc/misc/disabled.txt");
  myfile3.close();

  //c. disabled.txt
  ofstream myfile4;
  myfile4.open ("enc/misc/disablednum.txt");
  myfile4.close();

  //d. prompt.txt
  ofstream myfile5;
  myfile5.open ("enc/misc/prompt.txt");
  myfile5 << "CLI";
  myfile5.close();

  //e. userlist.txt
  ofstream myfile6;
  myfile6.open ("enc/misc/userlist.txt");
  myfile6 << "super\n";
  myfile6.close();
}

//3. Set prompt

  system("clear");
  setprompt("");//prompt = getprompt();

string command = "";
  
do 
{

display("");

cin >> command;

	if(command == "cls")
		if(Logged())
			system("clear");
		else 
		   display("You're not too bright, are you...You must login first.\n");
	
	else if(command == "login")
	{
		if(Logged())
			display("You're not too bright, are you...You are already logged in and you must logout first.\n");
		else
			login();
	}

	else if (command == "logout")
		if(Logged())
		    logout();
                 else 
		   display("You're not too bright, are you...You must login first.\n");
        else if (command == "prompt")
	{ 
		if(Logged())
		{
			display("Change prompt to: ");
			string tmp;
			cin >> tmp;
			if(setprompt(tmp))
			{
				display("Prompt was changed successfully.\n");
			}
			else
				display("Prompt was not changed successfully!\n");
			
		}
	  else 
	        display("You're not too bright, are you...You must login first.\n");
	}
	else if (command == "usercount")
	{
		if(Logged())
		{
			int disabled = 0;
			int users = 0;
			disabled = lineCount("enc/misc/disabled.txt");
			
			if(fexists("enc/misc/userlist.txt"))
			{	
				users = lineCount("enc/misc/userlist.txt");
	
			}
			else 
			{
								
				system("ls enc/users -m1 >> enc/misc/userlist.txt");
				users = lineCount("enc/misc/userlist.txt");
				
			}

			display("There are ");
			cout << users;
			cout << " total users (";
			cout << disabled <<" disabled)\n";
	
		}else 
	        display("You're not too bright, are you...You must login first.\n");
 
	}
	else if (command == "userlist")
	{
		if(Logged())
			system("ls enc/users -m1");
		else 
		   display("You're not too bright, are you...You must login first.\n");
	}
	else if (command == "whoami")
	{
		if(Logged())
			display("Moron! You are " + getuser() +"!\n");
		else 
		   display("You're not too bright, are you...You must login first.\n");
	}
	else if (command == "changepwd")
	{
		if(Logged())
		{
			string password = "";
			string newpwd = "";
			string confirm = "";
			display("Enter current password:");
			cin >> password;

			
			if (checkpswd(getuser(), password))
			{
				display("Enter new password:");
				cin >> newpwd;
				display("Confirm new password:");
				cin >> confirm;
				
				if(newpwd == confirm)
				{	//create new user file. else display(command)
					  ofstream check;
					string file = "enc/user/" + getuser() + ".txt"; 
  					 check.open (file.c_str());
  					 check << confirm;
  					 check.close(); 
					display("Password was successfully changed.\n");
				}
				else
					display("Passwords do not match.\n");
			}
			else
				display("Password is not valid for current user.\n");
		}else 
		   display("You're not too bright, are you...You must login first.\n");
	}
	else if (command == "prompt")
	{
		if(Logged())
		{
			string prmpt = "";
			 display("Change prompt to:");
			 cin >> prmpt;
	
			if(prmpt != "")
			{
			 	 system("rm enc/misc/prompt.txt"); 
				 setprompt (prmpt);
			}
		}
		else 
		   display("You're not too bright, are you...You must login first.\n");
	}
	else if (command == "adduser")
	{
		if(Logged())
		{
			if(is_super())
			{
				display("Enter New Username:");
				string username = "";
				cin >> username;
				string password = "";
				if(fexists("enc/users/"+ username + ".txt"))
				{
					display("That user already exists.\n");
				}
				else
					if(username != "")
					{
						display("Enter New Password:");
						cin >> password;

						 //create new user
						  ofstream newpwd;
						 string file = "enc/users/"+username+".txt";
						  newpwd.open(file.c_str());
						  newpwd << password + "\n";
						  newpwd.close();

						  //e. userlist.txt
						  ofstream newusr;
						  newusr.open("enc/misc/userlist.txt");
						  newusr << username+"\n";
						  newusr.close();
						
						display("User was successfully added.\n");

					}
					else { display("Username Error!\n");}
			
			}
			else
				display("You do not have access to this command.\n");
		}else 
		   display("You're not too bright, are you...You must login first.\n");
	}
	else if (command == "deluser")
	{
		if(Logged())
		{
			string name = "";

			if(is_super())
			{	display("Enter name to be deleted:");
				cin >> name;
				if(fexists("enc/users/"+ name + ".txt"))
				{
				  string choice;
				 display("Delete user account <" + name + ">? Yes/No:");
				 cin >> choice;
					if(choice == "Yes" || choice == "yes" || choice == "Y"|| choice == "y")
					{
						string customstr = "";
						customstr = "rm enc/users/"+ name + ".txt";
						system(customstr.c_str());
						string customstr2 = "";
						customstr2 = "sed -e '/$"+name+"/d' enc/misc/disabled.txt > enc/misc/disabled.txt.new"; 
						system(customstr2.c_str());
						display("Account deleted\n");
					}else {display("Account not deleted\n");}
				}else
					display("User does not exist.\n");
			}else
				display("You do not have access to this command.\n");
		}else 
		   display("You're not too bright, are you...You must login first.\n");	
	}
	else if (command == "setuser")
	{
		if(Logged())
		{
			if(is_super())
			{	string name = "";
				display("Enter Username:");
				cin >> name;
				if(fexists("enc/users/"+ name + ".txt") && name != "super")
				{
					if(grep("enc/misc/disabled.txt", name))
					{
						  display("Account is currently disabled.\n");
						  string choice = "";
						 display("Enable user account <" + name + ">? Yes/No:");
						 cin >> choice;
							if(choice == "Yes" || choice == "yes" || choice == "Y"|| choice == "y")
							{
								string sysinput = "sed -e '/$"+name+"/d' enc/misc/disabled.txt >enc/misc/disabled.txt.new";
								system(sysinput.c_str());
								display("Account is now enabled.\n");
							}else {display("Account is still disabled.\n");}
					}
					else
					{
						display("Account is currently enabled.\n");
						 string choice = "";
						 display("Disable user account <" + name + ">? Yes/No:");
						 cin >> choice;
						if(choice == "Yes" || choice == "yes" || choice == "Y"|| choice == "y")
						{
							string sysinput2 = "echo '" + name + "' > enc/misc/disabled.txt";
							system(sysinput2.c_str());
								display("Account is now disabled.\n");
							}else {display("Account is still enabled.\n");}
					}
					
				}
				else
					display("This user either does not exist or is the 'super' user. Either way, you cannot enable/disable.\n");
			}else
				display("You do not have access to this command.\n");
		}else 
		   display("You're not too bright, are you...You must login first.\n");
	}
	else if (command == "exit")
	{
	}
	else 
		display("Invalid Command\n");
}while(command != "exit");

cout << "Good Bye!\n";

system("Pause");
 
std::cout << "*************end*************\n";


  return 0;     
}

