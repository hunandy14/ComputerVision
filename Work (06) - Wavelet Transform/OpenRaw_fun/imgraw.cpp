/**********************************************************
Name : imgraw 實作
Date : 2016/10/03
By   : CharlotteHonG
Final: 2016/10/13
**********************************************************/
#include "OpenRAW"
namespace imr{
    /*
           ##

         ####     ### ##    ######  ## ###    ######  ##   ##
           ##     ## # ##  ##   ##  ###      ##   ##  ## # ##
           ##     ## # ##  ##   ##  ##       ##   ##  ## # ##
           ##     ## # ##   ######  ##       ##  ###  ## # ##
         ######   ##   ##       ##  ##        ### ##   ## ##
                            #####
    */
    // 匯入檔案
    void imgraw::read(string filename) {
        this->filename = filename;
        // 二進位模式開檔測試
        fstream img;
        img.open(filename, ios::in | ios::binary);
        // 如果開啟檔案失敗，fp為0；成功，fp為非0
        if(!img) {
            img.close();
            cout << "No file." << endl;
            exit(1);
        }
        else {
            // cout << "File ok." << endl;
        } img.close();
        // 二進位模式讀檔
        // 取得總長
        img.open(this->filename, ios::in | ios::binary);
        img.seekg(0, ios::end);
        this->filesize = img.tellg();
        img.seekg(0, ios::beg);
        // 讀取值
        this->img_data.vector::resize(this->filesize);
        img.read((char*)&this->img_data[0], this->filesize);
        img.close();
    }
    // 將記憶體資料匯出
    void imgraw::write(string filename) {
        // 進位模式寫檔
        fstream img;
        img.open(filename, ios::out | ios::binary);
        img.write((char*)&img_data[0], this->filesize);
        img.close();
    }
    // 讀檔單點(檢查邊界)
    imch imgraw::point_read(imint y, imint x) {
        imint pos = (y*this->width)+x;
        return this->img_data.at(pos);
    }
    // 寫入記憶體單點(檢查邊界)
    void imgraw::point_write(imint y, imint x, imch value) {
        imint pos = (y*this->width)+x;
        this->img_data.vector::at(pos) = value;
    }
    // 以二維方式讀取或寫入(檢查邊界)
    imch& imgraw::at2d(size_t y, size_t x){
        size_t pos = (y*this->width)+x;
        return this->img_data.at(pos);
    }
    const imch& imgraw::at2d(size_t y, size_t x) const{
        size_t pos = (y*this->width)+x;
        return this->img_data.at(pos);
    }
    // 調整畫布大小
    void imgraw::resize_canvas(ImrSize size) {
        imint x = size.width;
        imint y = size.high;
        // cout << "x=" << x << endl;
        // cout << "y=" << y << endl;
        this->width = x;
        this->high = y;
    }
    // 獲得寬
    imint imgraw::w() {
        return this->width;
    }
    // 獲得高
    imint imgraw::h() {
        return this->high;
    }
    // 印出畫布大小
    void imgraw::info(){
        cout << "畫布大小(寬x長) = " << this->width
             << " x " << this->high << endl;
    }
    // 二值化(界線, 填色數值, 背景數值)
    void imgraw::binarizae(imch value=128,
            imch high=255, imch low=0)
    {
        int len = this->width * this->high;
        // cout << "this[0]=" << (*this)[0] << endl;
        for (int i = 0; i < len; ++i)
        {
            if( (*this)[i] > value ) {
                (*this)[i] = high;
            }else{
                (*this)[i] = low;
            }
        }
    }
    // 一次更改所有像素(更改的數值)
    void imgraw::value(imch value){
        int len = this->width * this->high;
        for (int i = 0; i < len; ++i){
            (*this)[i] = value;
        }
    }
    /*
         ##   ##                    ##
         ##   ##                    ##
         ### ###   ######   #####   ##  ##
         ## # ##  ##   ##  ##       ## ##
         ## # ##  ##   ##   ####    ####
         ##   ##  ##  ###      ##   ## ##
         ##   ##   ### ##  #####    ##  ##

    */
    // 取得遮罩值 (原點，遮罩座標，位移)
    imch& imgraw::maskVal(ImrCoor ori, ImrCoor mas, 
            ImrCoor shi=ImrCoor(-1,-1))
    {
        // 取得對應位置
        ImrCoor pos = ori + mas + shi;
        // 修正邊緣
        if (pos.y <0){
            pos.y = 0;
        }
        if (pos.y > (int)this->high-1){
            pos.y = (int)this->high-1;
        }
        if (pos.x <0){
            pos.x = 0;
        }
        if (pos.x > (int)this->width-1){
            pos.x = (int)this->width-1;
        }
        // 回傳正確位置的數值
        return this->at2d((pos.y), (pos.x));
    }
    const imch& imgraw::maskVal(ImrCoor ori, ImrCoor mas, 
            ImrCoor shi=ImrCoor(-1,-1)) const
    {
        // 取得對應位置
        ImrCoor pos = ori + mas + shi;
        // 修正邊緣
        if (pos.y <0){
            pos.y = 0;
        }
        if (pos.y > (int)this->high-1){
            pos.y = (int)this->high-1;
        }
        if (pos.x <0){
            pos.x = 0;
        }
        if (pos.x > (int)this->width-1){
            pos.x = (int)this->width-1;
        }
        // 回傳正確位置的數值
        return this->at2d((pos.y), (pos.x));
    }
    // 取得遮罩，回傳一維陣列(原點位置，位移維度)
    ImrMask imgraw::getMask(ImrCoor ori, 
            ImrCoor shi = ImrCoor(-1,-1))
    {
        if (this->masksize.high == 0
            && this->masksize.width == 0){
            cout << "Error! Uninit masksize." << endl;
            return ImrMask(ImrSize(0, 0));
        }
        // 創建動態陣列
        ImrMask mask(this->masksize);
        // 複製遮罩
        for (int j = 0; j < (int)this->masksize.high; ++j){
            for (int i = 0; i < (int)this->masksize.width; ++i){
                // 遮罩位置
                ImrCoor mas(j,i);
                // 複製遮罩數值
                mask.at2d(j,i)=this->maskVal(ori, mas, shi);
            }
        }
        // 印出
        // for (int j = 0; j < 3; ++j){
        //     for (int i = 0; i < 3; ++i){
        //         cout << mask.at2d(j,i);
        //     }cout << endl;
        // }
        // return ImrMask();
        return mask;
    }
    // 設定遮罩
    void imgraw::setMaskSize(ImrSize masksize){
        this->masksize = masksize;
    }
    /*

        #    # #  ####  #####  ####   ####  #####    ##   #    #
        #    # # #        #   #    # #    # #    #  #  #  ##  ##
        ###### #  ####    #   #    # #      #    # #    # # ## #
        #    # #      #   #   #    # #  ### #####  ###### #    #
        #    # # #    #   #   #    # #    # #   #  #    # #    #
        #    # #  ####    #    ####   ####  #    # #    # #    #
    */
    // 印出直方圖
    void imgraw::pri_htg(string title=""){
        // 取得數據
        this->histogram();
        // 壓縮數據
        int htg_comp[32]={0};
        for (int i = 0; i < 32; ++i){
            htg_comp[i]=(
                htg_data[(i*8)+0]+
                htg_data[(i*8)+1]+ 
                htg_data[(i*8)+2]+ 
                htg_data[(i*8)+3]+
                htg_data[(i*8)+4]+
                htg_data[(i*8)+5]+
                htg_data[(i*8)+6]+
                htg_data[(i*8)+7]
            );
        }
        // 找最高值
        int htg_high=0;
        for (int i = 0; i < 32; ++i){
            if (htg_comp[i]>htg_high){
                htg_high = htg_comp[i];
            }
        }
        // 轉換等比
        int htg_rate[32]={0};
        for (int i = 0; i < 32; ++i){
            htg_rate[i] = (int)((double)htg_comp[i]
                / (double)htg_high*32);
        }
        // 轉換字串
        string str[32][32];
        for (int j = 0; j < 32; ++j){
            for (int i = 0; i < htg_rate[j]; ++i){
                str[j][i]+=" ▌";
            }
        }
        // 取得整數長度
        string temp;
        stringstream ss;
        ss << htg_high;
        temp.clear();
        ss >> temp;
        ss.clear();
        // 印出
        cout << endl << setw((64-3)-(title.length()/2));
        cout << title << endl;
        for (int i = 31; i >= 0; --i){
            cout << setw(temp.length()) 
                 << htg_high/32*(i+1) << " ";
            for (int j = 0; j < 32; ++j){
                cout << setw(3) <<str[j][i];
            }
            cout << endl;   
        }
        // 數據說明欄
        cout << setw(3) << "";
        for (int i = 0; i < 32/2; ++i){
            cout << setw(6) << (i+1)*16;  
        }
        cout << "" << endl;
    }
    // 取得數據統計(數值0~255有幾個)
    void imgraw::histogram(){
        int s=this->width * this->high;
        int temp;
        // 歸零
        for (int i = 0; i < 256; ++i)
            this->htg_data[i]=0;
        // 取得數據
        for (int i = 0; i < s; ++i){
            temp = (int)this->img_data.at(i);
            ++this->htg_data[temp];
        }
    }
    // 取得數據極值
    void imgraw::extremum(){
        imch temp;
        this->min=255;
        this->max=0;
        for (int j = 0; j < (int)this->high; ++j){
            for (int i = 0; i < (int)this->width; ++i){
                temp = this->at2d(j,i);
                if (temp > this->max){
                    this->max = temp;
                }else if (temp < this->min){
                    this->min = temp;
                }
            }
        }
    }
}