/**********************************************************
Name : OpenRAW_main
Date : 2016/08/03
By   : CharlotteHonG
Final: 2016/10/13
**********************************************************/
#include "OpenRAW_fun\OpenRAW"

namespace imr{
    // Imrintv�غc�l
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
    // �C�q
    void imgraw::low_pass(ImrSize size=ImrSize(3,3)){
        imgraw img2(ImrSize(this->high, this->width));
        double maslen = (double)size.high*(double)size.width;
        // ���I�B�z
        for (int j = 0; j < (int)this->high; ++j){
            for (int i = 0; i < (int)this->width; ++i){
                double long temp=0;
                // ���o�B�n�[�`�ƭ�
                for (int k = 0; k < (int)size.high; ++k){
                    for (int l = 0; l < (int)size.width; ++l){
                        ImrCoor ori(j,i);
                        ImrCoor mas(k, l);
                        temp += this->maskVal(ori, mas);
                    }
                }
                // ���o����
                temp = temp/maslen;
                // �g�J�s��
                img2.at2d(j, i) = (imch)temp;
            }
        }
        // �g�^�¹�
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
    // ���Y
    void imgraw::shrink(ImrIntv intv){
        // ���o�ƾڷ���
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
    // �٭�
    void imgraw::stretch(ImrIntv intv){
        // ���o�ƾڷ���
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
    // ����
    void imgraw::equalization(){
        // ���o�ƾڲέp
        this->histogram();
        // ��̷���
        this->extremum();
        // ���o����
        int n = this->width * this->high;
        // ���o���l
        double grand=0,S[255];
        for (int j = 0; j < 255; ++j){
            grand += this->htg_data[j];
            S[j] = grand/n;
        }
        // �ɤJ�ƾ�
        double temp;
        for (int i = 0; i < n; ++i){
            temp = S[(int)img_data.at(i)];
            img_data.at(i) = (int)(temp * (double)this->max);
        }
    }
}