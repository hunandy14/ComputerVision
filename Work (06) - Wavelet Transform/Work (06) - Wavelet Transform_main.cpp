/**********************************************************
Name : OpenRAW_main
Date : 2016/08/03
By   : CharlotteHonG
Final: 2016/10/05
**********************************************************/

#include <iostream>
#include "OpenRaw_fun\OpenRAW"
// Visual Studio �sĶ -> "��W"�[�J��main�ɧY�i
#include "Work (06) - Wavelet Transform.cpp" // GCC���ɽsĶ��

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
    //---------------------------------------------------------
    // �p�i�ഫ
    img.wavelet(2);
    //---------------------------------------------------------
    // ���ܰT��
    img.info();
    //---------------------------------------------------------
    // ��X�ɮ�
    img.write(Pic_name_out);
    // �}���ɮ�
    if(AutoOpen==1)
        system(Pic_name_out);
    return 0;
}