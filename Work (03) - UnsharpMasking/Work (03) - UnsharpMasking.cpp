/**********************************************************
Name : OpenRAW_main
Date : 2016/08/03
By   : CharlotteHonG
Final: 2016/10/13
**********************************************************/
#include "OpenRAW_fun\OpenRAW"

namespace imr{
    // Imrintv建構子
    ImrIntv::ImrIntv(imint min, imint max){
        this->min = min;
        this->max = max;
    }
    /*
         ##   ##             ##
         ###  ##
         ###  ##   #####   ####      #####    #####
         ## # ##  ##   ##    ##     ##       ##   ##
         ## # ##  ##   ##    ##      ####    #######
         ##  ###  ##   ##    ##         ##   ##
         ##   ##   #####   ######   #####     #####

    */
    // 低通
    void imgraw::low_pass(ImrSize size=ImrSize(3,3)){
        imgraw img2(ImrSize(this->high, this->width));
        double maslen = (double)size.high*(double)size.width;
        // 單點處理
        for (int j = 0; j < (int)this->high; ++j){
            for (int i = 0; i < (int)this->width; ++i){
                double long temp=0;
                // 取得遮罩加總數值
                for (int k = 0; k < (int)size.high; ++k){
                    for (int l = 0; l < (int)size.width; ++l){
                        ImrCoor ori(j,i);
                        ImrCoor mas(k, l);
                        temp += this->maskVal(ori, mas);
                    }
                }
                // 取得平均
                temp = temp/maslen;
                // 寫入新圖
                img2.at2d(j, i) = (imch)temp;
            }
        }
        // 寫回舊圖
        *this=img2;
    }
    /*
         ##         ##                ##
         ##                           ##
         ######   ####      #####   ######    #####    ######  ## ###    ######  ### ##
         ##   ##    ##     ##         ##     ##   ##  ##   ##  ###      ##   ##  ## # ##
         ##   ##    ##      ####      ##     ##   ##  ##   ##  ##       ##   ##  ## # ##
         ##   ##    ##         ##     ##     ##   ##   ######  ##       ##  ###  ## # ##
         ##   ##  ######   #####       ###    #####        ##  ##        ### ##  ##   ##
                                                       #####
    */
    // 收縮
    void imgraw::shrink(ImrIntv intv){
        // 取得數據極值
        this->extremum();
        int y=this->high;
        int x=this->width;

        double par = (((double)intv.max - (double)intv.min) / 
            ((double)this->max - (double)this->min));

        double temp; imch orig;
        for (int j = 0; j < y; ++j){
            for (int i = 0; i < x; ++i){
                orig = (double)this->point_read(j,i);
                temp = par*(orig - 
                        (double)this->min) + 
                        (double)intv.min;
                this->point_write(j, i, (imch)temp);
            }
        }
    }
    // 還原
    void imgraw::stretch(ImrIntv intv){
        // 取得數據極值
        this->extremum();
        int y=this->high;
        int x=this->width;

        double temp; imch orig;
        double par = (1/((double)this->max - (double)this->min)) *
            ((double)intv.max - (double)intv.min) + (double)intv.min;
        for (int j = 0; j < y; ++j){
            for (int i = 0; i < x; ++i){
                orig = (double)this->point_read(j,i);
                temp = (orig - (double)this->min) * par;
                if (temp > 255){
                    temp=255;
                }else if (temp < 0){
                    temp=0;
                }
                this->point_write(j, i, (imch)temp);
            }
        }
    }
    // 均質
    void imgraw::equalization(){
        // 取得數據統計
        this->histogram();
        // 找最極值
        this->extremum();
        // 取得分母
        int n = this->width * this->high;
        // 取得分子
        double grand=0,S[255];
        for (int j = 0; j < 255; ++j){
            grand += this->htg_data[j];
            S[j] = grand/n;
        }
        // 導入數據
        double temp;
        for (int i = 0; i < n; ++i){
            temp = S[(int)img_data.at(i)];
            img_data.at(i) = (int)(temp * (double)this->max);
        }
    }
}