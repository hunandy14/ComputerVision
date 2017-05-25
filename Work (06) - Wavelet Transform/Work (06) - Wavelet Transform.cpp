/**********************************************************
Name : OpenRaw 2.5.1
Date : 2016/08/03
By   : CharlotteHonG
Final: 2016/10/05
**********************************************************/
#include "OpenRaw_fun\OpenRAW"
//=========================================================
//-------------------------Structor------------------------
//=========================================================
#include "OpenRaw_fun\Structor.cpp"
//=========================================================
//------------------------ImrSize--------------------------
//=========================================================
#include "OpenRaw_fun\ImrSize.cpp"
//=========================================================
//------------------------ImrMask--------------------------
//=========================================================
#include "OpenRaw_fun\ImrMask.cpp"
//=========================================================
//------------------------ImrCoor--------------------------
//=========================================================
#include "OpenRaw_fun\ImrCoor.cpp"
//=========================================================
//------------------------imgraw---------------------------
//=========================================================
#include "OpenRaw_fun\imgraw.cpp"
//=========================================================
//------------------------Operator-------------------------
//=========================================================
#include "OpenRaw_fun\Operator.cpp"
//=========================================================
namespace imr {
// 小波轉換驅動程式
void imgraw::wavelet(imint value=1){
    int h=this->high;
    int w=this->width;
    for (int i = 0; i < (int)value; ++i){
        int temp=pow(2, i);
        this->wavelet_core(ImrSize(h/temp, w/temp));
    }
}
// 小波轉換核心程式
void imgraw::wavelet_core(ImrSize size){
    imgraw temp(size);
    // row
    for (int j=0, p=0; j < (int)size.width; ++j){
        // 左邊
        for (int i = 0; i < (int)size.width/2; ++i, ++p){
            temp[p] = round(
                ((double)this->at2d(j, (i*2))
                +(double)this->at2d(j, (i*2)+1)) /2 
            );
        }
        // 右邊
        for (int i = 0; i < (int)size.width/2; ++i, ++p){
            temp[p] = round(
                ((double)this->at2d(j, (i*2))
                -(double)this->at2d(j, (i*2)+1)) /2 
            );temp[p]+=128;
        }
    }
    // col
    for (int j=0, p=0; j < (int)size.high; ++j){
        // 上面
        for (int i = 0; i < (int)size.high/2; ++i, ++p){
            this->at2d(p, j) = round(
                ((double)temp.at2d((i*2), j)
                +(double)temp.at2d((i*2)+1, j)) /2 
            );
        }
        // 下面
        for (int i = 0; i < (int)size.high/2; ++i, ++p){
            this->at2d(p, j) = round(
                ((double)temp.at2d((i*2), j)
                -(double)temp.at2d((i*2)+1, j)) /2 
            );this->at2d(p, j)+=128;
        }p=0;
    }
}
} // imr