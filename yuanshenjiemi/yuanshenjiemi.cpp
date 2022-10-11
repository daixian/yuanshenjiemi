// yuanshenjiemi.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>

#include <vector>
#include <array>

#include <deque>

// 一个方块,其中记录和它联动的方块的index.
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

    // 和它联动的cube的index
    std::vector<int> linkCube;
};

class CubeSystem
{
  public:
    // 当前的4个方块状态.
    std::vector<Cube> allCube;

    // 经历的步骤.
    std::vector<int> vStep;

    /**
     * @brief 敲击几号,除了最远的对角线不转,其他3个都跟着转.
     * @param index
     */
    void knock(int index)
    {
        // 自身转
        allCube[index].rotate();

        //自身的连接的也转
        for (size_t i = 0; i < allCube[index].linkCube.size(); i++) {
            int indexLinkIndex = allCube[index].linkCube[i];
            allCube[indexLinkIndex].rotate();
        }

        vStep.push_back(index);
    }

    /**
     * @brief 检察这个系统是否已经成功了(面向同一指定方向).
     * @param targetDir
     * @return
     */
    bool checkSuccess(int targetDir)
    {
        for (size_t i = 0; i < allCube.size(); i++) {
            if (allCube[i].dir != targetDir) {
                return false;
            }
        }
        return true;
    }
};

int main()
{
    // std::cout << "Hello World!\n";

    //用0,1,2,3代表4个方向,这是当前方块的初始方向.
    //方块的index从0开始
    CubeSystem start; //初始系统状态
    Cube cube0;
    cube0.dir = 1;
    cube0.linkCube = {{1}};
    start.allCube.push_back(cube0);
    Cube cube1;
    cube1.dir = 2;
    cube1.linkCube = {{0, 2}};
    start.allCube.push_back(cube1);
    Cube cube2;
    cube2.dir = 2;
    cube2.linkCube = {{1, 3}};
    start.allCube.push_back(cube2);
    Cube cube3;
    cube3.dir = 2;
    cube3.linkCube = {{2}};
    start.allCube.push_back(cube3);

    int targetDir = 2; //成功的方向是2

    std::deque<CubeSystem> qSearch;
    qSearch.push_back(start);

    while (true) {
        CubeSystem curSearch = qSearch.front();
        qSearch.pop_front();
        //尝试敲击每一个方块
        for (size_t i = 0; i < start.allCube.size(); i++) {
            CubeSystem newSystem = curSearch;
            newSystem.knock(i);
            if (!newSystem.checkSuccess(targetDir)) { //成功方向
                qSearch.push_back(newSystem);
            }
            else {
                std::cout << "成功!" << std::endl;
                // 输出结果,方块的index从0开始
                for (size_t resi = 0; resi < newSystem.vStep.size(); resi++) {
                    std::cout << newSystem.vStep[resi] << " ";
                }
                return 0;
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
