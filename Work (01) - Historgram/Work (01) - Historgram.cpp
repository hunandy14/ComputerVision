/**********************************************************
Name : OpenRAW_main
Date : 2016/08/03
By   : CharlotteHonG
Final: 2016/10/13
**********************************************************/
namespace imr{
    ImrIntv::ImrIntv(int min, int max){
        this->min = min;
        this->max = max;
    }
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