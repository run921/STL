#define _CRT_SECURE_NO_WARNINGS
#include<iostream>  
#include<algorithm>
#include<functional>
#include<vector>
using namespace std;

int main()
{
    int a[6] = { 27,210,12,47,109,83 };
    vector<int, allocator<int>> v(a, a + 6);
    //vector<int> v(a, a + 6);      //也可不写allocator<int>,默认会有分配器

    //大于等于40的元素
    cout << count_if(v.begin(), v.end(), not1(bind2nd(less<int>(), 40))) << endl;   //not1为否定，内部表示小于40
    //bind2ed绑定第二参数
    //count_if是标准算法
    

    system("pause");
    return EXIT_SUCCESS;

}