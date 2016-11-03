/**********************************************************
Name : 建構子
Date : 2016/10/03
By   : CharlotteHonG
Final: 2016/10/13
**********************************************************/
#include "OpenRAW"
namespace imr{
    // ImrSize建構子
    ImrSize::ImrSize(imint high=0, imint width=0){
        this->high  = high;
        this->width = width;
    }
    // ImrCoor建構子
    ImrCoor::ImrCoor(int y=0, int x=0){
        this->y = y;
        this->x = x;
    }
    // ImrMask建構子
    ImrMask::ImrMask(ImrSize masksize){
        this->mask.vector::resize(masksize.high * masksize.width);
        this->masksize = masksize;
    }

    ImrMask::ImrMask(ImrSize masksize, imch value){
        this->mask.vector::resize(masksize.high * masksize.width);
        this->masksize = masksize;
        for (int i = 0; i < (int)(masksize.high*masksize.width); ++i){
            this->mask[i] = value;
        }
    }
    // imgraw建構子
    imgraw::imgraw(ImrSize size) {
        imint x = size.width;
        imint y = size.high;
        this->width = x;
        this->high = y;
        this->img_data.vector::resize(x*y);
        this->filesize = x*y;
        this->masksize = ImrSize(0,0);
    }
}