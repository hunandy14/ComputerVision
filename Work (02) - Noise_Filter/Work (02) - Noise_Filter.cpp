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
    // ����
    void imgraw::gaussian(double dev=5){
        // �Y��
        double sq_12 = sqrt((double)12);
        double sq_10 = sqrt((double)10);
        // �����Y��
        double gau = (sq_12*dev)/sq_10;
        // �p��
        for (int j = 0; j < (int)this->high; ++j){
            for (int i = 0; i < (int)this->width; ++i){
                // ���ü�
                int ran = rand_int(-dev,dev+1);
                // ���T��
                double noise = gau*ran;
                // �g�J����
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
    // ����
    void imgraw::median_filter(ImrSize size=ImrSize(3,3)){
        this->setMaskSize(size);
        imgraw img2(ImrSize(this->high, this->width));
        int maslen = (int)size.high*(int)size.width;
        int mid=maslen/2;
        // ���I�B�z
        for (int j = 0; j < (int)this->high; ++j){
            for (int i = 0; i < (int)this->width; ++i){
                ImrMask mask=this->getMask(ImrCoor(j, i));
                mask.sort();
                img2.at2d(j, i) = mask[mid];
            }
        }
        // �g�^�¹�
        *this=img2;
    }
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
    // �J���Q���T
    void imgraw::salt_pepper(imint white, imint black=0){
        srand((unsigned)time(NULL));
        ImrSize size(this->high, this->width);
        imgraw img2(size);
        int temp;
        // �x���I
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
        // �x���I
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
        // �x���ϤW
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
    // ���ü�(���]�tup)
    int imgraw::rand_int(int low, int up){
        int temp;
        if (low < 0)
            low-=1;
        temp = (int)((rand() / (RAND_MAX+1.0)) * (up - low) + low);
        return temp;
    }
}