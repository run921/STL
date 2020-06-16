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


//multiset性能测试（红黑树实现，multi关键字表示key可以重复）
#include<set>
namespace jj06
{
    void test_multiset(long &value)
    {
        cout << "\ntest_multiset()..................\n";
        multiset<string> c;
        char buf[10];
        clock_t timeStart = clock();
        for (long i = 0; i < value; ++i)
        {
            try
            {
                snprintf(buf, 10, "%d", rand());
                c.insert(string(buf));
            }
            catch (exception& p){
                cout << "i=" << i << " " << p.what() << endl;
                abort();
            }
        }
        cout << "milli-seconds:" << (clock() - timeStart) << endl;
        cout << "multiset.size()=" << c.size() << endl;
        cout << "multiset.max_size()=" << c.max_size() << endl;

        string target = get_a_target_string();
        {
            timeStart = clock();
            auto pItem = ::find(c.begin(), c.end(), target);        //比c.find()慢很多
            cout << "::find(),milli-seconds:" << (clock() - timeStart) << endl;
            if (pItem != c.end())
                cout << "found," << *pItem << endl;
            else
                cout << "not found!" << endl;
        }
        {
            timeStart = clock();
            auto pItem = c.find(target);        //比::find()快很多
            cout << "c.find(),milli-seconds:" << (clock() - timeStart) << endl;
            if (pItem != c.end())
                cout << "found," << *pItem << endl;
            else
                cout << "not found!" << endl;
        }
    }
}

//multimap性能测试（红黑树）    
#include <utility>
#include<map>
namespace jj07
{
    void test_map(long& value)
    {
        cout << "\ntest_multimap()..................\n";
        multimap<long,string> c;
        char buf[10];
        clock_t timeStart = clock();
        for (long i = 0; i < value; ++i)
        {
            try
            {
                snprintf(buf, 10, "%d", rand());
                //multimap不能用[]insertion
                c.insert(pair<long,string>(i,buf));
            }
            catch (exception & p)
            {
                cout << "i=" << i << " " << p.what() << endl;
                abort();
            }
    }
    cout << "milli-seconds:" << (clock() - timeStart) << endl;
    cout << "multimap.size()=" << c.size() << endl;
    cout << "multimap.max_size()=" << c.max_size() << endl;

    string target = get_a_target_string();
    {
        timeStart = clock();
        auto pItem = ::find(c.begin(), c.end(), target);        //比c.find()慢很多
        cout << "::find(),milli-seconds:" << (clock() - timeStart) << endl;
        if (pItem != c.end())
            cout << "found," << *pItem << endl;
        else
            cout << "not found!" << endl;
    }
    {
        timeStart = clock();
        auto pItem = c.find(target);        //比::find()快很多
        cout << "c.find(),milli-seconds:" << (clock() - timeStart) << endl;
        if (pItem != c.end())
            cout << "found," << (*pItem).second << endl;
        else
            cout << "not found!" << endl;
    }
}
}


//unordered_multimap性能测试(hashtable)
#include<unordered_set>
namespace jj08
{
    void test_unordered_multimap(long& value)
    {
        cout << "\ntest_unordered_multimap()............";
        unordered_multimap<string> c;
        char buf[10];
        clock_t timeStart = clock();
        for (long i = 0; i < value; ++i)
        {
            try
            {
                snprintf(buf, 10, "%d", buf);
                c.insert(string(buf));
            }
            catch (exception& p)
            {
                cout << "i=" << i << " " << p.what() << endl;
                abort();
            }
        }
        cout << "milli-seconds:" << (clock() - timeStart) << endl;
        cout << "unordered_multimap.size()=" << c.size() << endl;
        cout << "unordered_multimap.max_size()=" << c.max_size() << endl;
        cout << "unordered_multimap.bucket_count()=" << c.bucket_count() << endl;
        cout << "unordered_multimap.load_factor()=" << c.load_factor() << endl;
        cout << "unordered_multimap.max_load_factor()=" << c.max_load_factor() << endl;
        cout << "unordered_multimap.max_bucket_count()=" << c.max_bucket_count() << endl;
        for (unsigned i = 0; i < 20; ++i)
        {
            cout << "bucket #" << i << " has " << c.bucket_size(i) << " elements.\n";
        }

        string target = get_a_target_string();
        {
            timeStart = clock();
            auto pItem = ::find(c.begin, c.end(), target);      //比c.find()慢很多
            cout << "::find(),milli-second:" << timeStart - clock() << endl;
            if (pItem != c.end())
                cout << "found," << *pItem << endl;
            else
                cout << "not found!" << endl;
        }
        {
            timeStart = clock();
            auto pItem = c.find(c.begin, c.end(), target);      //比c.find()慢很多
            cout << "c.find(),milli-second:" << timeStart - clock() << endl;
            if (pItem != c.end())
                cout << "found," << *pItem << endl;
            else
                cout << "not found!" << endl;
        }

    }
}

//unordered_multimap性能测试(hashtable)
#include<unordered_map>
namespace jj09
{
    void test_unordered_multimap(long& value)
    {
        cout << "\ntest_unordered_multimap()............";
        unordered_multimap<long,string> c;
        char buf[10];
        clock_t timeStart = clock();
        for (long i = 0; i < value; ++i)
        {
            try
            {
                snprintf(buf, 10, "%d", buf);
                c.insert(pair<long,string>(i,buf));
            }
            catch (exception & p)
            {
                cout << "i=" << i << " " << p.what() << endl;
                abort();
            }
        }
        cout << "milli-seconds:" << (clock() - timeStart) << endl;
        cout << "unordered_multimap.size()=" << c.size() << endl;
        cout << "unordered_multimap.max_size()=" << c.max_size() << endl;
       
        for (unsigned i = 0; i < 20; ++i)
        {
            cout << "bucket #" << i << " has " << c.bucket_size(i) << " elements.\n";
        }

        string target = get_a_target_string();
        {
            timeStart = clock();
            auto pItem = c.find(c.begin, c.end(), target);      //比c.find()慢很多
            cout << "c.find(),milli-second:" << timeStart - clock() << endl;
            if (pItem != c.end())
                cout << "found," << (*pItem).second() << endl;
            else
                cout << "not found!" << endl;
        }

    }
}
//set
namespace jj13
{
    void test_set(long& value)
    {
        cout << "\ntest_set().............\n";

        set<string> c;
        char buf[10];

        clock_t timeStart = clock();
        for (long i = 0; i < value; ++i)
        {
            try
            {
                snprintf(buf, 10, "%d", rand());
                c.insert(string(buf));
            }
            catch (exception& p)
            {
                cout << "i=" << i << " " << p.what() << endl;
                abort();
            }
        }
        cout << "milli-second:" << (clock() - timeStart) << endl;
        cout << "set.size()=" << c.size() << endl;
        cout << "set.max_size()" << c.max_size() << endl;

        string target = get_a_target_string();
        
        {
            timeStart = clock();
            auto pItem = ::find(c.begin(), c.end(), target);    //比c.find()慢很多
            cout << "::find(),milli-seconds:" << (clock() - timeStart) << endl;
            if (pItem != c.end())
                cout << "found, " << *pItem << endl;
            else
                cout << "not found!" <<endl;
        }

        {
            timeStart = clock();
            auto pItem = c.find(target);
            cout << "c.find(),milli-seconds:" << (clock() - timeStart) << endl;
            if (pItem != c.end())
                cout << "found, " << *pItem << endl;
            else
                cout << "not found!" << endl;
        }
    }
}


int main()
{

    system("pause");
    return EXIT_SUCCESS;

}