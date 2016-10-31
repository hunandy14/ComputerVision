/**********************************************************
Name : OpenRAW_main
Date : 2016/08/03
By   : CharlotteHonG
Final: 2016/10/13
**********************************************************/
#include <iostream>
#include "OpenRAW_fun\OpenRAW"
// Visual Studio 編譯 -> 加入本main檔即可
#include "OpenRAW.cpp" // GCC單檔編譯用

using namespace std;
using namespace imr;

#define AutoOpen 1
#define Pic_name_in "IMG.raw"
#define Pic_name_out "IMG_OUT.raw"
#define Pic_x 256
#define Pic_y 256

int main(int argc, char const *argv[]) {
    // 創建畫布
    imgraw img(ImrSize(Pic_y, Pic_x));
    // 讀取檔案
    img.read(Pic_name_in);
    imgraw img2 = img;
    //---------------------------------------------------------
    img.pri_htg("Original");
    // 低通
    img.low_pass();
    // 收縮
    img.shrink(ImrIntv(0,120));
    // 相減
    img = img2-img;
    // 還原
    img.stretch(ImrIntv(0,255));
    // 印出直方圖
    img.pri_htg("shrink");
    //---------------------------------------------------------
    // 提示訊息
    img.info();
    // 輸出檔案
    img.write(Pic_name_out);
    // 開啟檔案
    if(AutoOpen==1)
        system(Pic_name_out);
    return 0;
}