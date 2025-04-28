#include "trashbin.h"
#include <iostream>

using namespace std;

TrashBin::TrashBin(double rate) : Device(rate) {}

void TrashBin::operate(Map& map, int x, int y) {
    cout << "TrashBin is operating with rate " << getRate() << endl;

    // 垃圾桶清除开采物
    if (map.getCell(x, y).oreType > 0) {  // 检查当前格子是否有开采物
        // 创建一个表示垃圾桶状态的 Cell 对象
        Cell trashCell = map.getCell(x, y);
        trashCell.oreType = 0;
        trashCell.oreValue = 0;
        map.setCell(x, y, trashCell);  // 清除当前格子的开采物
        cout << "Ore trashed at (" << x << ", " << y << ")" << endl;
    } else {
        cout << "No Ore in TrashBin at (" << x << ", " << y << ")" << endl;
    }
}
