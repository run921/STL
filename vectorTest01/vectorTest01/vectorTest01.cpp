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
    //vector<int> v(a, a + 6);      //Ҳ�ɲ�дallocator<int>,Ĭ�ϻ��з�����

    //���ڵ���40��Ԫ��
    cout << count_if(v.begin(), v.end(), not1(bind2nd(less<int>(), 40))) << endl;   //not1Ϊ�񶨣��ڲ���ʾС��40
    //bind2ed�󶨵ڶ�����
    //count_if�Ǳ�׼�㷨
    

    system("pause");
    return EXIT_SUCCESS;

}