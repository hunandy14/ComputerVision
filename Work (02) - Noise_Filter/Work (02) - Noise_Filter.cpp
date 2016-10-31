/**********************************************************
Name : OpenRAW_main
Date : 2016/08/03
By   : CharlotteHonG
Final: 2016/10/13
**********************************************************/
#include "OpenRAW_fun\OpenRAW"
/*
     ##   ##             ##
     ###  ##
     ###  ##   #####   ####      #####    #####
     ## # ##  ##   ##    ##     ##       ##   ##
     ## # ##  ##   ##    ##      ####    #######
     ##  ###  ##   ##    ##         ##   ##
     ##   ##   #####   ######   #####     #####

*/
namespace imr{
    // 高斯
    void imgraw::gaussian(double dev=5){
        // 係數
        double sq_12 = sqrt((double)12);
        double sq_10 = sqrt((double)10);
        // 高斯係數
        double gau = (sq_12*dev)/sq_10;
        // 計算
        for (int j = 0; j < (int)this->high; ++j){
            for (int i = 0; i < (int)this->width; ++i){
                // 取亂數
                int ran = rand_int(-dev,dev+1);
                // 雜訊值
                double noise = gau*ran;
                // 寫入圖檔
                double temp = (double)this->point_read(j,i);
                temp += noise;
                if (temp > 255)
                    temp = 255;
                else if (temp < 0)
                    temp = 0;
                this->point_write(j, i, (imch)temp);
            }
        }

    }
    // 中值
    void imgraw::median_filter(ImrSize size=ImrSize(3,3)){
        this->setMaskSize(size);
        imgraw img2(ImrSize(this->high, this->width));
        int maslen = (int)size.high*(int)size.width;
        int mid=maslen/2;
        // 單點處理
        for (int j = 0; j < (int)this->high; ++j){
            for (int i = 0; i < (int)this->width; ++i){
                ImrMask mask=this->getMask(ImrCoor(j, i));
                mask.sort();
                img2.at2d(j, i) = mask[mid];
            }
        }
        // 寫回舊圖
        *this=img2;
    }
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
    // 胡椒鹽雜訊
    void imgraw::salt_pepper(imint white, imint black=0){
        srand((unsigned)time(NULL));
        ImrSize size(this->high, this->width);
        imgraw img2(size);
        int temp;
        // 灑黑點
        temp = ((double)black/(double)100)
                         * this->high * this->width;
        // cout << temp << endl;
        for (int i = 0; i < temp; ++i){
            int y = rand_int(0,256);
            int x = rand_int(0,256);
            if (img2.point_read(y, x) != 1){
                img2.point_write(y, x, (imch)1);
            }else {--i;}
        }
        // 灑白點
        temp = ((double)white/(double)100)
                         * this->high * this->width;
        // cout << temp << endl;
        for (int i = 0; i < temp; ++i){
            int y = rand_int(0,256);
            int x = rand_int(0,256);
            if (img2.point_read(y, x) != 255
                && img2.point_read(y, x) != 1){
                img2.point_write(y, x, (imch)255);
            }else {--i;}
        }
        // 灑到原圖上
        for (int j = 0; j < (int)this->high; ++j){
            for (int i = 0; i < (int)this->width; ++i){
                imch temp = img2.point_read(j, i);
                if (temp == (imch)1){
                    this->point_write(j, i, (imch)0);
                }else if (temp == (imch)255){
                    this->point_write(j, i, (imch)255);
                }
            }
        }
        // *this = img2;
    }
    // 取亂數(不包含up)
    int imgraw::rand_int(int low, int up){
        int temp;
        if (low < 0)
            low-=1;
        temp = (int)((rand() / (RAND_MAX+1.0)) * (up - low) + low);
        return temp;
    }
}