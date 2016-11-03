/**********************************************************
Name : OpenRAW_main
Date : 2016/08/03
By   : CharlotteHonG
Final: 2016/10/13
**********************************************************/
#include <iostream>
#include "OpenRAW_fun\OpenRAW"
// Visual Studio �sĶ -> "��W"�[�J��main�ɧY�i
#include "Work (04) Hough-transform.cpp" // GCC���ɽsĶ��

using namespace std;
using namespace imr;

#define AutoOpen 0
#define Pic_name_in "Hough_868X600.raw"
#define Pic_name_out "IMG_OUT.raw"
#define Pic_x 868
#define Pic_y 600

int main(int argc, char const *argv[]) {
    // �Ыصe��
    imgraw img(ImrSize(Pic_y, Pic_x));
    // Ū���ɮ�
    img.read(Pic_name_in);
    //---------------------------------------------------------
    // ��t����
    img.sobel(250);
    // �N�ҹB��
    img.hough(300);
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