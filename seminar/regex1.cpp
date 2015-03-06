// C++11
#include <iostream>
#include <regex>
#include <string>

int main()
{
	using namespace std;
	string input;
	regex integer("(\\+|-)?[[:digit:]]+");
	// as long as the input is correct ask for another number
	while(true)
	{
		cout<<"Give me an integer!"<<endl;
		cin>>input;
		if(!cin) break;
		if(input=="q") // exit when the user inputs q
			break;
		if(regex_match(input,integer))
			cout<<"integer"<<endl;
		else
		{
			cout<<"Invalid input"<<endl;
		}
	}
}
