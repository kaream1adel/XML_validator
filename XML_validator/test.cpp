/*
 * test.cpp
 *
 *  Created on: Dec 11, 2022
 *      Author: pc
 */
#include <iostream>
#include "validatexml.h"
#include <stack>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <cstring>



using namespace std;






int main(){
	validatexml xml1;

string input="sample.xml";
string output="corrected.xml";

	xml1.check_xml(input);

	xml1.correct_xml( input, output);

	cout <<"finish";




}



