/**********************************************************
Name : OpenRAW_main
Date : 2016/08/03
By   : CharlotteHonG
Final: 2016/10/05
**********************************************************/

#include <iostream>
#include "OpenRaw_fun\OpenRAW"
// Visual Studio 編譯 -> "單獨"加入本main檔即可
#include "Work (07) - Morphological operations.cpp" // GCC單檔編譯用
using namespace std;
using namespace imr;

#define AutoOpen 1
#define Pic_name_in "MorphologicalOperations_500x500.raw"
#define Pic_name_out "IMG_OUT.raw"
#define Pic_x 500
#define Pic_y 500

int main(int argc, char const *argv[]) {
    // 創建畫布
    imgraw img(ImrSize(Pic_y, Pic_x));
    // 讀取檔案
    img.read(Pic_name_in);
    //---------------------------------------------------------
    int ch=0;
    // 查看效果
    if(ch==0){
        // 二值
        img.binarizae();
        // 膨脹
        img.dilation();
        img.dilation();
        // 侵蝕
        img.erosion();
        img.erosion();
    }
    // 驗證功能
    if(ch==1){
        // 二值(界線, 填充色, 底色)
        img.binarizae(128, 32, 0);
        // 膨脹(填充色, 目標影像數值)
        img.dilation(255, 32);
        // 侵蝕(填充色, 目標影像數值)
        img.erosion(128, 255);
    }
    //---------------------------------------------------------
    // 提示訊息
    img.info();
    //---------------------------------------------------------
    // 輸出檔案
    img.write(Pic_name_out);
    // 開啟檔案
    if(AutoOpen==1){
        string temp = "start \"\" ";
        temp += Pic_name_out;
        system(temp.c_str());
    }
    return 0;
}