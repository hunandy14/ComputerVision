/**********************************************************
Name : OpenRAW_main
Date : 2016/08/03
By   : CharlotteHonG
Final: 2016/10/05
**********************************************************/

#include <iostream>
#include "OpenRaw_fun\OpenRAW"
// Visual Studio 編譯 -> "單獨"加入本main檔即可
#include "Work (06) - Wavelet Transform.cpp" // GCC單檔編譯用

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
    //---------------------------------------------------------
    // 小波轉換
    img.wavelet(2);
    //---------------------------------------------------------
    // 提示訊息
    img.info();
    //---------------------------------------------------------
    // 輸出檔案
    img.write(Pic_name_out);
    // 開啟檔案
    if(AutoOpen==1)
        system(Pic_name_out);
    return 0;
}