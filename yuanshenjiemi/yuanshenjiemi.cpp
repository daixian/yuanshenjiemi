// yuanshenjiemi.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>

#include <vector>
#include <array>

#include <deque>

class Cube
{
  public:
    // 0,1,2,3代表4个方向
    int dir;

    void rotate()
    {
        dir += 1;
        if (dir == 4) {
            dir = 0;
        }
    }
};

class CubeSystem
{
  public:
    // 当前的4个方块状态.
    std::array<Cube, 4> arr;

    // 经历的步骤.
    std::vector<int> vStep;

    /**
     * @brief 敲击几号,除了最远的对角线不转,其他3个都跟着转.
     * @param index
     */
    void knock(int index)
    {
        //除了对角线的全部转一下
        int acrossIndex = (index + 2) % 4; //对角线的方块index

        for (size_t i = 0; i < 4; i++) {
            if (i != acrossIndex) {
                arr[i].rotate();
            }
        }
        vStep.push_back(index);
    }

    bool checkSuccess(int targetDir)
    {
        for (size_t i = 0; i < arr.size(); i++) {
            if (arr[i].dir != targetDir) {
                return false;
            }
        }
        return true;
    }
};

int main()
{
    std::cout << "Hello World!\n";

    //用0,1,2,3代表4个方向,这是当前方块的初始方向.
    std::array<Cube, 4> arr;
    arr[0].dir = 2;
    arr[1].dir = 2;
    arr[2].dir = 2;
    arr[3].dir = 1;

    CubeSystem start;
    start.arr = arr;

    std::deque<CubeSystem> qSearch;
    qSearch.push_back(start);

    while (true) {
        CubeSystem curSearch = qSearch.front();
        qSearch.pop_front();
        //尝试4个
        for (size_t i = 0; i < 4; i++) {
            CubeSystem newSystem = curSearch;
            newSystem.knock(i);
            if (!newSystem.checkSuccess(2)) { //成功方向是面向2
                qSearch.push_back(newSystem);
            }
            else {
                printf("成功!");
            }
        }
    }
}

// 运行程序: Ctrl + F5 或调试 >“开始执行(不调试)”菜单
// 调试程序: F5 或调试 >“开始调试”菜单

// 入门使用技巧:
//   1. 使用解决方案资源管理器窗口添加/管理文件
//   2. 使用团队资源管理器窗口连接到源代码管理
//   3. 使用输出窗口查看生成输出和其他消息
//   4. 使用错误列表窗口查看错误
//   5. 转到“项目”>“添加新项”以创建新的代码文件，或转到“项目”>“添加现有项”以将现有代码文件添加到项目
//   6. 将来，若要再次打开此项目，请转到“文件”>“打开”>“项目”并选择 .sln 文件
