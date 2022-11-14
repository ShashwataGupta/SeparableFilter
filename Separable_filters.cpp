/* 

Problem statement :- Create a solution whr you take fx and fy as filter co-efficients. The size of the filter is 31(radius being 15). 

1)	Input is an image with size varying from 64x64 to 1920x1920.
2)	Fx and fy each value can be from 0 to 1024. The sum of all the co-efficients is going to be less than 4096 and always pto the power of 2(like,2,4,8,16,32..etc)
3)	Output of always as 16 bit.

*/
#include <stdio.h>
#include <iostream>
#include <vector>
#include <bits/stdc++.h>
//#include <opencv2/opencv.hpp>

using namespace std;

typedef struct {
    std::vector<uint16_t> fx;
    std::vector<uint16_t> fy;
    uint16_t sumx;
    uint16_t sumy;
} coefs;
class conv
{
    std::vector<std::vector<uint8_t>> input_img;
    coefs filt;
    bool pad_status;
    
    
    public:
    
    conv()
    {
        float i=0.0f;
        uint16_t c= 1;
        int len=0;
        pad_status = 0;
        input_img.assign(64, std::vector<uint8_t>(64,0));
        for (int i=0; i<64; i++)
            input_img[i][i]=255;
        while(len < 31)
        {
            len++;
            filt.fx.push_back(c);
            filt.fy.push_back(c);
            if (len < 16)
            {
                if (len%2 ==0 || len==15)
                    c = c << 1;
            }
            else
            {
                if (len%2 ==0)
                    c = c >> 1;
            }
            
        }
        filt.sumx = accumulate(filt.fx.begin(), filt.fx.end(), 0);
        filt.sumy = accumulate(filt.fy.begin(), filt.fy.end(), 0);
        
    }
    
    void show()
    {
        int sz=input_img.size();
        cout << "input image:" << endl;
        for (int i=0; i<sz; i++)
        {
            for (int j=0; j<sz; j++)
              cout << int(input_img[i][j]) << "\t";
            
            cout << "\n";
        }
        
        cout << "fx:" << endl;
        for (int j=0; j<31; j++)
              cout << filt.fx[j] << "\t";
        cout << "\n";
        cout << "fy:" << endl;
        for (int j=0; j<31; j++)
              cout << filt.fy[j] << "\t";
        cout << "\n";
        cout << "Sum of fx: " << filt.sumx <<"\n";
        cout << "Sum of fy: " << filt.sumy <<"\n";
        
    }
    uint16_t mult(std::vector<uint8_t> a, bool dim)
    {
        uint16_t res = 0;
        for (int i=0; i<31; i++)
        {
            if (dim == 0)
                res += (a[i] * filt.fx[i]);
            else
                res += (a[i] * filt.fy[i]);
        }
        if (dim == 0)
            res = res / filt.sumx;
        else
            res = res / filt.sumy;
        
        return(res);
    }
    
    
    std::vector<std::vector<uint16_t>> filterx()
    {
        std::vector<uint8_t> temp;
        std::vector<uint16_t> temp1;
        std::vector<std::vector<uint16_t>> res;
        std::vector<uint8_t>::iterator it;
        int szb = input_img[0].size() - 30;
        int szl = input_img.size();
        uint16_t sum;
        
        for (int i = 0; i<szl; i++)
        {
            it = input_img[i].begin();
            for (int j = 0; j<szb; j++)
            {
                temp.assign(it+j,it+j+30);
                sum = mult(temp,0);
                temp1.push_back(sum);
                temp.clear();
            }
            res.push_back(temp1);
            temp1.clear();
        }
        
        cout << "Filtered on X:\n";
        for (int i=0; i<szl; i++)
        {
            for (int j=0; j<szb; j++)
              cout << int(res[i][j]) << "\t";
            
            cout << "\n";
        }
        return(res);
    }
    
    std::vector<std::vector<uint16_t>> filter()
    {
        std::vector<uint8_t> temp;
        std::vector<uint16_t> temp1;
        std::vector<std::vector<uint16_t>> res, filteredx;
        std::vector<std::vector<uint16_t>>::iterator it;
        
        filteredx = filterx();
        
        int szb = filteredx[0].size();
        int szl = filteredx.size()-30;
        uint16_t sum;
        
        
        for (int i = 0; i<szl; i++)
        {
            for (int j = 0; j<szb; j++)
            {
                for ( int k = 0; k<31; k++ )
                {
                    temp.push_back(filteredx[i+k][j]);
                }
                sum = mult(temp,0);
                temp1.push_back(sum);
                temp.clear();
            }
            res.push_back(temp1);
            temp1.clear();
        }
        
        cout << "Filtered on Y:\n";
        for (int i=0; i<szl; i++)
        {
            for (int j=0; j<szb; j++)
              cout << int(res[i][j]) << "\t";
            
            cout << "\n";
        }
        return(res);
    }
    
    
    
};

int main() {
	//code
	conv obj;
	obj.show();
	obj.filter();
	return 0;
}