#include "validatexml.h"
#include <iostream>
#include <stack>
#include <queue>
#include <fstream>
#include <string>
#include <algorithm>
#include <cstring>
#include <stdio.h>


using namespace std;


//reversing string recursively
string reversestringrec(string str) {
    while (str.length() >= 0 && str.length() <= 20) {
        if (str.length() == 1) {
        	return str;
        }
        else {
            return reversestringrec(str.substr(1, str.length())) + str.at(0);
        }
    }
    return "invalid input string";
}


//changing filexml content



std::stack<std::string> str;
std::string myline;
//stack of char named input
stack<char> input;
stack <int> input2;

char chars[]=" ";
char chars2[]="/<> ";
char mychar,mychar2;
int lineNum=1;
//to avoid the initial value of false
bool mark = true;
string opentag, closetag;
int openN=0 , closeN=0;
bool flag = false;
//file correcting variables
string filename;
string text;
vector<string> lines;
queue<int> buffer;
int i=0;
queue<string> opentag_buffer,closedtag_buffer;





validatexml::validatexml() {

	// TODO Auto-generated constructor stub
}

void validatexml::  check_xml(string string){

		//check tag number and shape
		while ( read_file ) {
			//read char from the file stream
			mychar = read_file.get();
			if(mychar=='<'){
				input.push(mychar);
			}
			if(mychar=='>'){
				input.pop();
			}
		}

		read_file.close();
		//check the empty of the stack
		if(input.empty()==1){
			cout << "brackets are consistenet"<<endl;
		}
		else {
			//numbers of tags are equal and same shape <
			cout << "brackets are inconsistenet"<< endl;
		}
		read_file.close();

		//check tag name
		//open file identified by file name as an argument
		read_file.open("sample.xml");
			//return true if the file is opened
			if( read_file.is_open() ) {
				//.good() return true if the file has no errors
                    while (read_file.good()){
					//read line from myfile in myline
					getline (read_file, myline);
                    int linelen = myline.length();
					for(int j = 0; j <linelen; j++){
						opentag = "";
						closetag="";
						int counter = 0;
						mychar2 = myline[j];
						//open tag
						if (mychar2 == '<' && myline[j+1] != '/'){
							openN++;
							for(int k = j+1 ; myline[k] != '>' ; k++){
								input.push(myline[k]);
								counter += 1 ;
							}
							//counter in stack for the current length of the tag
							input2.push(counter);
						}
						//close tag
						else if(mychar2 == '/' && myline[j-1] == '<' && !input2.empty()) {
							closeN++;
							int cnt = input2.top();
							input2.pop();
							//forming the close tag name
							for (int v = j+1 ; myline[v] != '>' ; v++){
								closetag += myline[v];
							}
							//cout << closetag<<endl;
							for (int m = j+1,n=2 ;n < cnt + 2;m++,n++){
								if( myline[linelen-n] == input.top() ){
									//forming the open tag name in variable tag
									opentag += input.top();
									input.pop();
									//all results must be true to obtain a true output
									mark &= true;
								}

						//&= for cumulative error checking if one time is false then the result is false
								else
								{
									opentag += input.top();
									input.pop();
									mark &= false;
								//cout << "error in line      : " << lineNum << endl;

									if(buffer.front() != lineNum  ){

									buffer.push(lineNum);


									}



									//missing tag in case of OPEN tag is missed
									//cout << "in case of missing open tag the missed tag is " <<closetag << endl;
									opentag_buffer.push(closetag);

								}
							}
						//cout the name of the tag and missing tag in case of CLOSED tag is missed
						//cout <<"in case of missing closed tag the missed tag is "<< reversestringrec(opentag) << endl;
							if(mark==false){
							closedtag_buffer.push(reversestringrec(opentag));

							}
					}
					}
					lineNum += 1 ;
                    }

                    //show the error

                    if (openN>closeN){


                    	cout << "missing closetag"<<endl;

                    	while(!buffer.empty()){
                    	 cout << "error in line: " << buffer.front()<< endl;
                    	 buffer.pop();
                    	}
                    	 cout<< "the tag is "<<closedtag_buffer.front()<<endl;


                    	 status=missing_close;
                    	 tag=closedtag_buffer.front();
                    	 line_number=buffer.front();
                    }
                    else if (openN>=closeN && mark==false){
                    	cout << "missing opentag" <<endl;
                    	 cout << "error in line: " << buffer.front()<< endl;
                    	 cout<< "the tag is "<<opentag_buffer.front()<<endl;
                    	status= missing_open;
                    	tag=opentag_buffer.front();
                    	line_number=buffer.front();

                    }
                    else{
                    	cout << "No error"<<endl;
                    }
                    /*if (reversestringrec(opentag) == reversestringrec(closetag)){
                    	cout << "no tag errors"<<endl;
                    }
                    else {
                    	cout<< "error in line:" << lineNum<<endl;
                    }*/

					if (mark == true){
						cout << "tags are consistent"<< endl;
					}
					else{
						cout << "tags are inconsistent" << endl;
						file_status=No_Error;
					}
/*
					if (input.empty()==true){
						cout << "empty stack"<<endl;
					}
					else cout << "error in stack"<< endl;
*/
					//printing the total number of lines in the file
					//cout << lineNum<<endl;

//return "Tree";


					//validatexml::correct_xml(buffer[0], opentag_buffer.front(), status);

}

			read_file.close();
}


void validatexml::correct_xml(string input_file,string output_file){

/*
	 output_file="corrected.xml";
	 input_file="sample.xml";
*/


	  // fstream object will be used to read all of the existing lines in the file


	  // Open the file with the provided filename
	  read_file.open(input_file);

	  // If file failed to open, exit with an error message and error exit status
	  if (read_file.fail())
	  {
	    cout << "Error opening file." << endl;

	    // returning 1 instead of 0 is a signal to the shell that something went
	    // wrong in the execution of the program

	  }

	  // Create a vector to store all the file lines, and a string line to store
	  // each line that we read
	  vector<string> lines;
	  string line;

	  // Read each line of the file and store it as the next element of the vector,
	  // the loop will stop when there are no more lines to read
	  while (getline(read_file, line))
	    lines.push_back(line);

	  // Close our access to the file since we are done reading with it
	  read_file.close();



	  // Create ofstream object for writing to the file
	  write_file.open(output_file);

	  // If the file failed to open, exit with an error message and exit status
	  if (write_file.fail())
	  {
	    cout << "Error opening file." << endl;

	  }

	  for (int counter = 0; counter < int(lines.size()); counter++){
		  write_file << lines[counter] << endl;
	    if (counter == line_number-2){
	    	// write_file <<"\n";
	    	 if (status== missing_open){



	    		 write_file <<"<"<<tag<<">"<<endl;
	    	 	                    }



	    	 else if(status== missing_close){

	    		 write_file <<"</"<<tag<<">"<<endl;

	    	 	                    }
	    }
	  }


	  // Close our access to the file since we are done working with it
	  write_file.close();


}



validatexml::~validatexml() {
	// TODO Auto-generated destructor stub
}
