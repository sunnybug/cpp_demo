#include <iostream>
using namespace std;

int main()
{
    const char* fmt = "恭喜<font color=0xff00ea>%s</font>的<font color=0xff00ea>【%s】</font>，通过融合开启了一个新的技能格子。";
    char sz[256] = {0};
    snprintf(sz, sizeof(sz) - 1, fmt, "哈哈1", "哈哈2");
    cout << sz << endl;
    return 0;
}