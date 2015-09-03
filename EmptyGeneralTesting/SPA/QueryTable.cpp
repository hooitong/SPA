#include "QueryTable.h"
#include <iostream>
#include <vector>
#include <sstream>
#include <map>
#include <fstream>
#include <algorithm>
using namespace std;



QueryTable::QueryTable(void) {


    string array1[] = { "prog_line","stmt", "if", "while","call","assign", "procedure", "variable"};
    string array2[] = { "prog_line","stmt","assign"};


    //the first two numbers is the range of the design entity  for arg1_list
    //the last two numbers is the range of the design entity  for arg2_list
    // for this line,  addEntry("Modifies", array1 , array1, 0, 7, 7, 8);
    // 0 7 refers to  "prog_line","stmt", "if", "while","call","assign", "procedure"
    // 7 8 refers to  "variable"
    // the numbers are like index of the array
    addEntry("Modifies", array1 , array1, 0, 7, 7, 8);
    addEntry("Uses", array1 , array1, 0, 7, 7, 8);
    addEntry("Calls", array1 , array1, 6, 7, 6, 7);
    addEntry("Calls*", array1 , array1, 6, 7, 6, 7);
    addEntry("Parent", array1 , array1, 0, 4, 0, 6);
    addEntry("Parent*", array1 , array1, 0, 4, 0, 6);
    addEntry("Follows", array1 , array1, 0, 6, 0, 6);
    addEntry("Follows*", array1 , array1, 0, 6, 0, 6);
    addEntry("Next", array1 , array1, 0, 6, 0, 6);
    addEntry("Next*", array1 , array1, 0, 6, 0, 6);
    addEntry("Affects", array2 , array2, 0, 3, 0, 3);
    addEntry("Affects*", array2 , array2, 0, 3, 0, 3);
	
	entry boo = table["Modifies"];
	if (find(boo.arg2_list.synonym_type.begin(), boo.arg2_list.synonym_type.end(),"procedure")!= boo.arg2_list.synonym_type.end() ){
	    cout << "Found" <<endl;
	}else{
	    cout << "Not Found" <<endl;
	} 

}

void QueryTable::addEntry(string condition, string array1[], string array2[], int len1 , int len2, int len3, int len4){
	arg_type_list arg1_list,arg2_list;
    arg1_list.synonym_type.assign(array1 + len1 ,array1 + len2);
    arg2_list.synonym_type.assign(array2 + len3 ,array2 + len4);
	entry e = {arg1_list,arg2_list};
	table[condition] = e;
}