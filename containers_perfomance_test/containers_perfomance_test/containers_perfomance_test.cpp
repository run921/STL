/********************************
*程序功能：测试STL各个容器性能
*
*by 高智强
**********************************/
#define _CRT_SECURE_NO_WARNINGS
#include<iostream>  
#include<array>
#include<ctime>
#include<cstdlib>   //qsort,bsearch,NULL
using namespace std;

long get_a_target_long()    //输入一个容器容量值，小于rand返回的最大值RAND_MAX
{
    long target = 0;

    cout << "target(0~" << RAND_MAX << "):";
    cin >> target;
    return target;
}

string get_a_target_string()    //将输入的数字转换为字符串
{
    long target = 0;
    char buf[10];

    cout << "target(0~" << RAND_MAX << "):";
    cin >> target;
    snprintf(buf, 10, "%d", target);
    return string(buf);
}

int compareLongs(const void* a, const void* b)      //做qsort()辅助函数
{
    return (*(long*)a - *(long*)b);
}

int compareString(const void* a, const void* b)
{
    if (*(string*)a > * (string*)b)return 1;
    if (*(string*)a == *(string*)b)return 0;
    if (*(string*)a < *(string*)b)return -1;
}

//Array测试，使用到Qsort,Bsearch
namespace jj01{
    void test_array()
    {
        cout << "\ntest_array()...............\n";
        array<long, 10000> c;
        clock_t timeStart = clock();
        for (long i = 0; i < 10000; ++i)
        {
            c[i] = rand();
        }
        cout << "milli-seconds:" << (clock() - timeStart) << endl;
        cout << "array.size()" << c.size() << endl;
        cout << "array.front()" << c.front() << endl;
        cout << "array.back()" << c.back() << endl;
        cout << "array.data()" << c.data() << endl;

        long target = get_a_target_long();

        timeStart = clock();
        qsort(c.data(), 10000, sizeof(long), compareLongs);

        long* pItem = (long*)bsearch(&target, (c.data()), 10000, sizeof(long), compareLongs);
        cout << "asort()+bsearch(),milli-seconds:" << (clock() - timeStart) << endl;
        if (*pItem != NULL)
            cout << "found," << *pItem << endl;
        else
            cout << "not found" << endl;
    }
}

//vector测试
#include<vector>
#include<stdexcept>
#include<string>    
#include<cstdlib>   //abort()
#include<cstdio>  //snprintf()
#include<iostream>
#include<ctime>
#include<algorithm>
namespace jj02
{
    void test_vector(long& value)
    {
        cout << "\ntest_vector().........\n";
        vector<string> c;
        char buf[10];

        clock_t timeStart = clock();
        for (int i = 0; i < value; ++i)
        {
            //数组大小可能会超过栈大小
            try
            {
                snprintf(buf,10,"%d",rand());
                c.push_back(string(buf));
            }
            catch (exception& p)
            {
                cout << "i=" << i << p.what() << endl;
                abort();
            }

            cout << "milli-seconds:" << (clock()-timeStart) << endl;
            cout << "vrctor.size()=" << c.size() << endl;
            cout << "vector.front()" << c.front() << endl;
            cout << "vector.back()" << c.back() << endl;
            cout << "vector.data()" << c.data() << endl;
            cout << "vector.capacity()" << c.capacity() << endl;
        }
        
        string target = get_a_target_string();
        
        {
            timeStart = clock();
            auto pItem = ::find(c.begin(), c.end(), target);        //直接查找
            cout << "::find(), milli-seconds:" << timeStart - clock() << endl;
            if (pItem != c.end)
                cout << "found," << *pItem << endl;
            else
                cout << "not found" << endl;

            {
                timeStart = clock();
                sort(c.begin(), c.end());
                string* pItem = (string*)bsearch(&target, (c.data()), c.size(), sizeof(string), compareString);     //排序后二分查找
            }
        }
    }       
}

//双向链表list性能测试
#include<list>
namespace jj03
{
    void test_list(long& value)
    {
        cout << "\ntest_list().......\n";

        list<string> c;
        char buf[10];

        clock_t timeStart = clock();
        for (long i = 0; i < value; ++i)
        {
            try
            {
                snprintf(buf,10,"%d",rand());
                c.push_back(string(buf));
            }
            catch (exception& p)
            {
                cout << "i=" << i << " " << p.what() << endl;
                abort();
            }
        }
        //开始打印list测试信息
        cout << "milli-seconds:" << timeStart - clock() << endl;
        cout << "list.size():" << c.size() << endl;
        cout << "list.max_size():" << c.max_size() << endl;
        cout << "list.front():" << c.front() << endl;
        cout << "list.back():" << c.back() << endl;

        //测试查找性能
        string target = get_a_target_string();
        timeStart = clock();
        auto pItem = ::find(c.begin(),c.end(),target);
        cout << "::find(),milli-seconds:" << timeStart - clock() << endl;
        
        if (pItem != c.end())
            cout << "found," << *pItem << endl;
        else
            cout << "not found" << endl;

        timeStart = clock();
        c.sort();
        cout << "c.sort(),milli-seconds:" << timeStart - clock() << endl;

    }
}


//单向链表forward_list性能测试
#include<forward_list>
namespace jj04
{
    void test_forward_test(long& value)
    {
        cout << "\ntest_forward_list................\n";

        forward_list<string> c;
        char buf[10];

        clock_t timeStart = clock();
        for (long i = 0; i < value; ++i)
        {
            try
            {
                snprintf(buf,10,"%d",rand());
                c.push_front(string(buf));
            }
            catch (exception& p)
            {
                cout << "i:" << i << " " << p.what() << endl;
                abort();
            }
        }
        //输出测试信息
        cout << "milli-second:" << timeStart - clock() << endl;
        cout << "forward_list.max_size()=" << c.max_size() << endl;
        cout << "fordward_list.front()" << c.front() << endl;

        string target = get_a_target_string();
        timeStart = clock();
        auto pItem = ::find(c.begin(),c.end(),target);
        cout << "::find(),milli-seconds:" << timeStart - clock() << endl;

        if (pItem != c.end())
            cout << "found," << *pItem << endl;
        else
            cout << "not found！" << endl;

        timeStart = clock();
        c.sort();
        cout << "sort milli-seconds:" << timeStart - clock() << endl;

    }
}

//deque性能测试
#include<deque>
namespace jj05
{
    void test_deque(long& value)
    {
        cout << "\ntest_deque().......\n";

        deque<string> c;
        char buf[10];

        clock_t timeStart = clock();
        for (long i = 0; i < value; ++i)
        {
            try
            {
                snprintf(buf, 10, "%d", rand());
                c.push_back(string(buf));
            }
            catch (exception& p)
            {
                cout << "i:" << i << " " << p.what() << endl;
                abort();
            }
        }
        //输出测试信息
        cout << "milli-seconds:" << timeStart - clock() << endl;
        cout << "deque.size():" << c.size() << endl;
        cout << "deque.front():" << c.front() << endl;
        cout << "deque.back():" << c.back() << endl;
        cout << "deque.max_size():" << c.max_size() << endl;

        string target = get_a_target_string();
        timeStart = clock();
        auto pItem = ::find(c.begin(), c.end(), target);
        cout << "::find(),milli-seconds:" << timeStart - clock() << endl;
        
        if (pItem != c.end())
            cout << "found," << *pItem << endl;
        else
            cout << "not found!" << endl;
    }
}

//栈stack性能测试（stack基于deque实现）
#include<stack>
namespace jj17
{
    void test_stack(long& value)
    {
        cout << "\ntest_stack()...........\n";

        stack<string> c;
        char buf[10];

        clock_t timeStart = clock();
        for (long i = 0; i < value; ++i)
        {
            try
            {
                snprintf(buf, 10, "%d", rand());
                c.push(string(buf));
            }
            catch (exception& p)
            {
                cout << "i=" << i << " " << p.what() << endl;
                abort();
            }
        }
        cout << "milli-seconds:" << timeStart - clock() << endl;
        cout << "stack.size():" << c.size() << endl;
        cout << "stack.top():" << c.top() << endl;
        c.pop();
        cout << "stack.size():" << c.size() << endl;
        cout << "stack.top():" << c.top() << endl;
    }
}

//队列queue性能测试（queue基于deque实现）
#include<queue>
namespace jj18
{
    void test_queue(long& value)
    {
        cout << "\ntest_stack()...........\n";

        queue<string> c;
        char buf[10];

        clock_t timeStart = clock();
        for (long i = 0; i < value; ++i)
        {
            try
            {
                snprintf(buf, 10, "%d", rand());
                c.push(string(buf));
            }
            catch (exception & p)
            {
                cout << "i=" << i << " " << p.what() << endl;
                abort();
            }
        }
        cout << "milli-seconds:" << timeStart - clock() << endl;
        cout << "queue.size():" << c.size() << endl;
        cout << "queue.top():" << c.front() << endl;
        cout << "queue.back():" << c.back() << endl;
        c.pop();
        cout << "queue.size():" << c.size() << endl;
        cout << "queue.top():" << c.front() << endl;
        cout << "queue.back():" << c.back() << endl;
    }
}


int main()
{

    system("pause");
    return EXIT_SUCCESS;

}