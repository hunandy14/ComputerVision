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
// 膨脹(填充後的數值, 目標影像數值, 背景底色數值)
void imgraw::dilation(imch value=255, imch tar=255, imch bg=0){
    imgraw temp=(*this);
    for (int j = 0; j < (int)this->high; ++j){
        for (int i = 0; i < (int)this->width; ++i){
            if(mor_check(ImrCoor(j, i), tar, bg)[0]=='1') {
                temp.at2d(j, i) = value;
            }
        }
    }(*this)=temp;
}
// 侵蝕(填充後的數值, 目標影像數值, 背景底色數值)
void imgraw::erosion(imch value=0, imch tar=255, imch bg=0){
    imgraw temp=(*this);
    for (int j = 0; j < (int)this->high; ++j){
        for (int i = 0; i < (int)this->width; ++i){
            // 修正侵蝕位置
            int u = j==0?                   j: j-1;
            int d = j==(int)this->high -1?  j: j+1;
            int l = i==0?                   i: i-1;
            int r = i==(int)this->width-1?  i: i+1;
            // 侵蝕
            if(mor_check(ImrCoor(j, i), tar, bg)[1]=='1') {
                temp.at2d(u, i) = value;
            }
            if(mor_check(ImrCoor(j, i), tar, bg)[2]=='1') {
                temp.at2d(d, i) = value;
            }
            if(mor_check(ImrCoor(j, i), tar, bg)[3]=='1') {
                temp.at2d(j, l) = value;
            }
            if(mor_check(ImrCoor(j, i), tar, bg)[4]=='1') {
                temp.at2d(j, r) = value;
            }
        }
    }(*this)=temp;
}
// 確認是否為目標
string imgraw::mor_check(ImrCoor ori, imch tar=255, imch bg=0){
    // 鑑別方向
    string str("00000");
    // 周圍數據
    int u = ori.y==0?                   ori.y: ori.y-1;
    int d = ori.y==(int)this->high -1?  ori.y: ori.y+1;
    int l = ori.x==0?                   ori.x: ori.x-1;
    int r = ori.x==(int)this->width-1?  ori.x: ori.x+1;
    // 不符合條件其他都不用做了
    if(this->at2d(ori.y, ori.x) == bg){
        // 判定周圍四點
        if(this->at2d(u, ori.x) == tar)
            str[1]='1';
        if(this->at2d(d, ori.x) == tar)
            str[2]='1';
        if(this->at2d(ori.y, l) == tar)
            str[3]='1';
        if(this->at2d(ori.y, r) == tar)
            str[4]='1';
        // 判定為目標
        if(str[1]=='1' || str[2]=='1' || str[3]=='1' || str[4]=='1')
            str[0]='1';
    }
    return str;
}
} // imr
