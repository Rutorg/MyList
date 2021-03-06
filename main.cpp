#include <iostream>

#include "MyList.h"


using std::cout; 
using std::cin;
using std::endl;


template <typename T>
void myPrintMyList(MyList<T>& listToPrint, const char* name = "")
{
	cout << "Name: " << name << endl;
	cout << "Content: ";

	for (auto& element : listToPrint) {
		cout << element << ' ';
	}

	cout << endl << endl;
}

void myPrintTestEnded(size_t testNumber)
{
	cout << "Test " << testNumber << " ended." << endl << "==============================" << endl;
}


// Проверка pushBack и pushFront.
void test1()
{
	MyList<int> list;

	for (size_t i = 0; i < 10; i++) {
		list.pushBack(i);
	}

	for (size_t i = 0; i < 10; i++) {
		list.pushFront(-static_cast<int>(i));
	}

	myPrintMyList(list, "list");
	myPrintTestEnded(1);
}


// Проверка popFront и popBack.
void test2()
{
	MyList<int> list;

	for (size_t i = 0; i < 10; i++) {
		list.pushBack(i);
	}

	for (size_t i = 0; i < 10; i++) {
		list.pushFront(-static_cast<int>(i));
	}
	myPrintMyList(list, "list");


	list.popFront();
	cout << "After popFront:" << endl;
	myPrintMyList(list, "list");


	list.popBack();
	cout << "After popBack:" << endl;
	myPrintMyList(list, "list");


	for (size_t i = 0; i < 10; i++) {
		list.popBack();
	}
	cout << "After 10 popBack:" << endl;
	myPrintMyList(list, "list");


	for (size_t i = 0; i < 8; i++) {
		list.popBack();
	}
	cout << "After another 8 popBack:" << endl;
	myPrintMyList(list, "list");

	myPrintTestEnded(2);
}


// Проверка insert.
void test3()
{
	MyList<int> list;

	for (size_t i = 0; i < 10; i++) {
		list.pushBack(i);
	}

	for (size_t i = 0; i < 10; i++) {
		list.pushFront(-static_cast<int>(i));
	}

	myPrintMyList(list, "list");


	auto it = list.begin();
	list.insert(it, 100);
	cout << "After insert at begin:" << endl;
	myPrintMyList(list, "list");


	it = list.end();
	list.insert(it, -100);
	cout << "After insert at end:" << endl;
	myPrintMyList(list, "list");

	
	it = list.begin();
	for (size_t i = 0; i < 5; i++) {
		++it;
	}

	it = list.insert(it, -100);
	cout << "After insert at 5th element." << endl;
	myPrintMyList(list, "list");

	++it;
	it = list.insert(it, 99);
	cout << "After insert at 6th element." << endl;
	myPrintMyList(list, "list");

	myPrintTestEnded(3);
}


// Проверка clear, front и back.
void test4()
{
	MyList<int> list;

	for (size_t i = 0; i < 10; i++) {
		list.pushBack(i);
	}

	for (size_t i = 0; i < 10; i++) {
		list.pushFront(-static_cast<int>(i));
	}

	myPrintMyList(list, "list");


	list.front() = -440;
	list.back() = -550;
	cout << "After changing first and last elements:" << endl;
	myPrintMyList(list, "list");

	list.clear();
	cout << "After clear:" << endl;
	myPrintMyList(list, "list");

	myPrintTestEnded(4);
}


// Проверка конструктора копирования.
void test5()
{
	MyList<double> list1;

	for (size_t i = 0; i < 10; i++) {
		list1.pushBack(i + 0.1);
	}

	for (size_t i = 0; i < 10; i++) {
		list1.pushFront(-(i + static_cast<double>(i) / 5));
	}

	myPrintMyList(list1, "list1");


	MyList<double> list2 = list1;
	cout << "list2 - copy of list2." << endl;
	myPrintMyList(list2, "list2");


	list1.clear();
	myPrintMyList(list1, "list1 cleared");

	cout << "list2 doesn't changed." << endl;
	myPrintMyList(list2, "list2");
	

	myPrintTestEnded(5);
}

// Проверка оператора присваивания.
void test6()
{
	MyList<double> list1;

	for (size_t i = 0; i < 10; i++) {
		list1.pushBack(i + 0.1);
	}

	for (size_t i = 0; i < 10; i++) {
		list1.pushFront(-(i + static_cast<double>(i) / 5));
	}

	myPrintMyList(list1, "list1");


	MyList<double> list2;

	for (size_t i = 0; i < 20; i++) {
		list2.pushBack(i);
	}

	for (size_t i = 0; i < 5; i++) {
		list2.pushFront(-static_cast<int>(i));
	}

	myPrintMyList(list2, "list2");


	list1 = list2;
	cout << "After list1 = list2" << endl;
	myPrintMyList(list1, "list1");
	myPrintMyList(list2, "list2");


	list2.clear();
	cout << "After list2.clear()" << endl;
	myPrintMyList(list1, "list1");
	myPrintMyList(list2, "list2");

	myPrintTestEnded(6);
}


int main()
{
	test1();
	test2();
	test3();
	test4();
	test5();
	test6();

	return 0;
}