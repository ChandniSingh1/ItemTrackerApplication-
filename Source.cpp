#include <Python.h>
#include <iostream>
#include <Windows.h>
#include <cmath>
#include <string>
#include <fstream>

using namespace std;
string checkForItem;
int option;
int amount;
ifstream inFile;
int quantiny;
string name;

/*
Description:
	To call this function, simply pass the function name in Python that you wish to call.
Example:
	callProcedure("printsomething");
Output:
	Python will print on the screen: Hello from python!
Return:
	None
*/
void CallProcedure(string pName)
{
	char* procname = new char[pName.length() + 1];
	std::strcpy(procname, pName.c_str());

	Py_Initialize();
	PyObject* my_module = PyImport_ImportModule("PythonCode");
	PyErr_Print();
	PyObject* my_function = PyObject_GetAttrString(my_module, procname);
	PyObject* my_result = PyObject_CallObject(my_function, NULL);
	Py_Finalize();

	delete[] procname;
}

/*
Description:
	To call this function, pass the name of the Python functino you wish to call and the string parameter you want to send
Example:
	int x = callIntFunc("PrintMe","Test");
Output:
	Python will print on the screen:
		You sent me: Test
Return:
	100 is returned to the C++
*/
int callIntFunc(string proc, string param)
{
	char* procname = new char[proc.length() + 1];
	std::strcpy(procname, proc.c_str());

	char* paramval = new char[param.length() + 1];
	std::strcpy(paramval, param.c_str());


	PyObject* pName, * pModule, * pDict, * pFunc, * pValue = nullptr, * presult = nullptr;
	// Initialize the Python Interpreter
	Py_Initialize();
	// Build the name object
	pName = PyUnicode_FromString((char*)"PythonCode");
	// Load the module object
	pModule = PyImport_Import(pName);
	// pDict is a borrowed reference 
	pDict = PyModule_GetDict(pModule);
	// pFunc is also a borrowed reference 
	pFunc = PyDict_GetItemString(pDict, procname);
	if (PyCallable_Check(pFunc))
	{
		pValue = Py_BuildValue("(z)", paramval);
		PyErr_Print();
		presult = PyObject_CallObject(pFunc, pValue);
		PyErr_Print();
	}
	else
	{
		PyErr_Print();
	}
	//printf("Result is %d\n", _PyLong_AsInt(presult));
	Py_DECREF(pValue);
	// Clean up
	Py_DECREF(pModule);
	Py_DECREF(pName);
	// Finish the Python Interpreter
	Py_Finalize();

	// clean 
	delete[] procname;
	delete[] paramval;


	return _PyLong_AsInt(presult);
}

/*
Description:
	To call this function, pass the name of the Python functino you wish to call and the string parameter you want to send
Example:
	int x = callIntFunc("doublevalue",5);
Return:
	25 is returned to the C++
*/
int callIntFunc(string proc, int param)
{
	char* procname = new char[proc.length() + 1];
	std::strcpy(procname, proc.c_str());

	PyObject* pName, * pModule, * pDict, * pFunc, * pValue = nullptr, * presult = nullptr;
	// Initialize the Python Interpreter
	Py_Initialize();
	// Build the name object
	pName = PyUnicode_FromString((char*)"PythonCode");
	// Load the module object
	pModule = PyImport_Import(pName);
	// pDict is a borrowed reference 
	pDict = PyModule_GetDict(pModule);
	// pFunc is also a borrowed reference 
	pFunc = PyDict_GetItemString(pDict, procname);
	if (PyCallable_Check(pFunc))
	{
		pValue = Py_BuildValue("(i)", param);
		PyErr_Print();
		presult = PyObject_CallObject(pFunc, pValue);
		PyErr_Print();
	}
	else
	{
		PyErr_Print();
	}
	//printf("Result is %d\n", _PyLong_AsInt(presult));
	Py_DECREF(pValue);
	// Clean up
	Py_DECREF(pModule);
	Py_DECREF(pName);
	// Finish the Python Interpreter
	Py_Finalize();

	// clean 
	delete[] procname;

	return _PyLong_AsInt(presult);
}
void menu() {  // menu that asks user for input
	while (true) {
		cout << "    ***Welcome to CornerGrocery!***" << endl;
		cout << "Please choose an option from the menu below." << endl;  
		cout << endl;
		cout << "1: Produce a list of all items purchased in a given day along with the number of times each item was purchased" << endl;
		cout << "2: Produce a number representing how many times a specific item was purchased in a given day." << endl;
		cout << "3: Produce a text-based histogram listing all items purchased in a given day, along with a representation of the number of times each item was purchased." << endl;
		cout << "4: Exit the program." << endl;
		cin >> option;
		if (option == 1) {
			CallProcedure("listOfItems"); // calls python function that prints list of items purchased in that day 
		}
		else if (option == 2) {
			cout << "What item would you like to check? ";
			cin >> checkForItem;
			amount = callIntFunc("searchSpefic", checkForItem); // calls python function 
			cout << checkForItem << " were purchased " << amount << " times today." << endl; // prints the item an how many times it was purchased
			cout << endl;
		}
		else if (option == 3) {
			CallProcedure("create_new_doc"); // calls functions that creatres new file 
		    inFile.open("frequency.dat"); // opens new file
			inFile >> name; // adds data to new file
			inFile >> quantiny;
			cout << name; 
			for (int i = 0; i < quantiny; i++) { // converts qunatity to  CHAR - *
				cout << '*';
			}
			cout << endl;
			inFile >> name;
			inFile >> quantiny;
			inFile.close(); //close doc

		}
		else if (option == 4) {
			break; // quits program
		}
		else {
			cout << "Please choose a valid option.";// loops back if the user chooses a nonvaild option 
			cout << endl;
			continue;
		}
	}
}


void main(){
	menu(); // calls menu fuction 

}