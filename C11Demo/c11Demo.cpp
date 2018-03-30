// c11Demo.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include <iostream>
#include <utility>
#include <thread>
#include <chrono>
#include <functional>
#include <atomic>

using namespace std;
//////////////////////////////////////////////////////////////////////////

void f1(int n)
{
	for (int i = 0; i < 5; ++i) {
		std::cout << "Thread " << n << " executing\n";
		std::this_thread::sleep_for(std::chrono::seconds(1));
	}
}

void f2(int& n)
{
	for (int i = 0; i < 5; ++i) {
		std::cout << "Thread 2 executing\n";
		++n;
		std::this_thread::sleep_for(std::chrono::seconds(1));
	}
}

void thread_main()
{
	cout << std::thread::hardware_concurrency() << endl;
	int n = 0;
	std::thread t1; // t1 is not a thread
	std::thread t2(f1, n + 1); // pass by value
	std::thread t3(f2, std::ref(n)); // pass by reference
	std::thread t4(std::move(t3)); // t4 is now running f2(). t3 is no longer a thread
	std::this_thread::sleep_for(std::chrono::seconds(10));
	t2.join();
	t4.join();
	std::cout << "Final value of n is " << n << '\n';
}

//////////////////////////////////////////////////////////////////////////
class CMyString
{
public:
	// ���캯��
	CMyString(const char *pszSrc = NULL)
	{
		cout << "CMyString(const char *pszSrc = NULL)" << endl;
		if (pszSrc == NULL)
		{
			m_pData = new char[1];
			*m_pData = '\0';
		}
		else
		{
			m_pData = new char[strlen(pszSrc) + 1];
			strcpy(m_pData, pszSrc);
		}
	}

	// �������캯��
	CMyString(const CMyString &s)
	{
		cout << "CMyString(const CMyString &s)" << endl;
		m_pData = new char[strlen(s.m_pData) + 1];
		strcpy(m_pData, s.m_pData);
	}

	// move���캯��
	CMyString(CMyString &&s)
	{
		cout << "CMyString(CMyString &&s)" << endl;
		m_pData = s.m_pData;
		s.m_pData = NULL;
	}

	// ��������
	~CMyString()
	{
		cout << "~CMyString()" << endl;
		delete[] m_pData;
		m_pData = NULL;
	}

	// ������ֵ����
	CMyString &operator =(const CMyString &s)
	{
		cout << "CMyString &operator =(const CMyString &s)" << endl;
		if (this != &s)
		{
			delete[] m_pData;
			m_pData = new char[strlen(s.m_pData) + 1];
			strcpy(m_pData, s.m_pData);
		}
		return *this;
	}

	// move��ֵ����
	CMyString &operator =(CMyString &&s)
	{
		cout << "CMyString &operator =(CMyString &&s)" << endl;
		if (this != &s)
		{
			delete[] m_pData;
			m_pData = s.m_pData;
			s.m_pData = NULL;
		}
		return *this;
	}

private:
	char *m_pData;
};

CMyString GetMyString()
{
	CMyString o1;
	return (o1);
}

CMyString GetMoveMyString()
{
	CMyString o1;
	return std::move(o1);
}

void MoveDemo()
{
	{
		CMyString o2 = GetMyString();
	}
	{
		CMyString o2 = GetMoveMyString();
	}
	{
		CMyString o1;
		CMyString o2 = o1;
	}
}

//////////////////////////////////////////////////////////////////////////
#include <iostream>       // std::cout
#include <functional>     // std::ref
#include <thread>         // std::thread
#include <future>         // std::promise, std::future

void print_int(std::future<int>& fut) {
	int x = fut.get(); // ��ȡ����״̬��ֵ.
	std::cout << "value: " << x << '\n'; // ��ӡ value: 10.
}

int FutureDemo()
{
	std::promise<int> prom;						// ����һ�� std::promise<int> ����.
	std::future<int> fut = prom.get_future();	// �� future ����.
	std::thread t(print_int, std::ref(fut));	// �� future ��������һ���߳�t.
	prom.set_value(10);							// ���ù���״̬��ֵ, �˴����߳�t����ͬ��.
	t.join();
	return 0;
}

//////////////////////////////////////////////////////////////////////////
#include <iostream>       // std::cin, std::cout, std::ios
#include <functional>     // std::ref
#include <thread>         // std::thread
#include <future>         // std::promise, std::future
#include <exception>      // std::exception, std::current_exception

void get_int(std::promise<int>& prom) {
	int x;
	std::cout << "Please, enter an integer value: ";
	std::cin.exceptions(std::ios::failbit);   // throw on failbit
	try {
		std::cin >> x;                         // sets failbit if input is not int
		prom.set_value(x);
	}
	catch (std::exception&) {
		prom.set_exception(std::current_exception());
	}
}

void print_int2(std::future<int>& fut) {
	try {
		int x = fut.get();
		std::cout << "value: " << x << '\n';
	}
	catch (std::exception& e) {
		std::cout << "[exception caught: " << e.what() << "]\n";
	}
}

int FutureDemo2()
{
	std::promise<int> prom;
	std::future<int> fut = prom.get_future();

	std::thread th1(get_int, std::ref(prom));
	std::thread th2(print_int2, std::ref(fut));

	th1.join();
	th2.join();
	return 0;
}
//////////////////////////////////////////////////////////////////////////


int _tmain(int argc, _TCHAR* argv[])
{

	return FutureDemo2();
}
