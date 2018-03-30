#include <iostream>
#include <string>
#include "Interpreter.h"
using namespace std;

void main(){
	// Construct the Context first
	map<string,int> Dict;
	Dict["һ"] = 1;
	Dict["��"] = 2;
	Dict["��"] = 3;
	Dict["��"] = 4;
	Dict["��"] = 5;
	Dict["��"] = 6;
	Dict["��"] = 7;
	Dict["��"] = 8;
	Dict["��"] = 9;
	Evaluator myEvaluator = Evaluator();
	myEvaluator.Construct("��Ӷ�");
	double result = myEvaluator.Interprete(Dict);
	cout<<result<<endl;
	while(1){

	}
}