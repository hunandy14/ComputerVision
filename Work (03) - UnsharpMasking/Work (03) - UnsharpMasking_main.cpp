/**********************************************************
Name : OpenRAW_main
Date : 2016/08/03
By   : CharlotteHonG
Final: 2016/10/13
**********************************************************/
#include <iostream>
#include "OpenRAW_fun\OpenRAW"
// Visual Studio �sĶ -> �[�J��main�ɧY�i
#include "OpenRAW.cpp" // GCC���ɽsĶ��

using namespace std;
using namespace imr;

#define AutoOpen 1
#define Pic_name_in "IMG.raw"
#define Pic_name_out "IMG_OUT.raw"
#define Pic_x 256
#define Pic_y 256

int main(int argc, char const *argv[]) {
    // �Ыصe��
    imgraw img(ImrSize(Pic_y, Pic_x));
    // Ū���ɮ�
    img.read(Pic_name_in);
    imgraw img2 = img;
    //---------------------------------------------------------
    img.pri_htg("Original");
    // �C�q
    img.low_pass();
    // ���Y
    img.shrink(ImrIntv(0,120));
    // �۴�
    img = img2-img;
    // �٭�
    img.stretch(ImrIntv(0,255));
    // �L�X�����
    img.pri_htg("shrink");
    //---------------------------------------------------------
    // ���ܰT��
    img.info();
    // ��X�ɮ�
    img.write(Pic_name_out);
    // �}���ɮ�
    if(AutoOpen==1)
        system(Pic_name_out);
    return 0;
}