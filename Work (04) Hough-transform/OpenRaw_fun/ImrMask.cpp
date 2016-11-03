/**********************************************************
Name : ImrMask 實作
Date : 2016/10/03
By   : CharlotteHonG
Final: 2016/10/13
**********************************************************/
#include "OpenRAW"
namespace imr{
    /*
        ###               #     #
         #  #    # #####  ##   ##   ##    ####  #    #
         #  ##  ## #    # # # # #  #  #  #      #   #
         #  # ## # #    # #  #  # #    #  ####  ####
         #  #    # #####  #     # ######      # #  #
         #  #    # #   #  #     # #    # #    # #   #
        ### #    # #    # #     # #    #  ####  #    #
    */
    // 排序陣列(長度，起始點)
    void ImrMask::sort(size_t len=0, size_t start=0) {
        imch temp;
        imch* arr = &this->mask[start];
        if (len == 0){
            len = this->masksize.high*this->masksize.width; 
        }
        // // 插入排序法
        for (int i=1, j; i<(int)len; i++) {
            temp = arr[i];
            for (j=i-1; j>=0 && arr[j]>temp; j--)
                arr[j + 1] = arr[j];
            arr[j + 1] = temp;
        }
    }
    // 以二維方式讀取或寫入
    imch& ImrMask::at2d(size_t y, size_t x){
        size_t pos = (y*this->masksize.width) + x;
        return this->mask[pos];
    }
    const imch& ImrMask::at2d(size_t y, size_t x) const{
        size_t pos = (y*this->masksize.width) + x;
        return this->mask[pos];
    }
    // 印出資訊
    void ImrMask::info(){
        for (int j = 0; j < (int)masksize.high; ++j){
            for (int i = 0; i < (int)masksize.width; ++i){
                cout << setw(4) << (int)this->at2d(j, i);
            }cout << endl;
        }
    }
    // 取得平均值
    imch ImrMask::avg(){
        double long temp=0;
        imint len=this->masksize.high * this->masksize.width;
        for (int i = 0; i < (int)len; ++i){
            temp += (double)(*this)[i];
        }
        return (imch)((temp/len)+0.5);
    }
}