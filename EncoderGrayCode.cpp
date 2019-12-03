#include "EncoderGrayCode.h"

//设置的水平方向的条纹数是10，垂直方向的条纹数是6
static unsigned int Nhorz = 10;
static unsigned int Nvert = 6;
 
#ifndef log2f
#define log2f(x) (log(x)/log(2.0))
#endif
 
using namespace std;
 
/*
 * The purpose of this function is to convert an unsigned
 * binary number to reflected binary Gray code.
 *
 * The operator >> is shift right. The operator ^ is exclusive or.
 * Source: http://en.wikipedia.org/wiki/Gray_code
 */
static unsigned int binaryToGray(unsigned int num) {
    return (num >> 1) ^ num;
}
 
/*
 * From Wikipedia: http://en.wikipedia.org/wiki/Gray_code
 * The purpose of this function is to convert a reflected binary
 * Gray code number to a binary number.
*/
static unsigned grayToBinary(unsigned num, unsigned numBits)
{
    for (unsigned shift = 1; shift < numBits; shift <<= 1){
        num ^= num >> shift;
    }
    return num;
}
 
/*
 * Function takes the decimal number
 * Function takes the Nth bit (1 to 31)
 * Return the value of Nth bit from decimal
 * Source: http://icfun.blogspot.com/2009/04/get-n-th-bit-value-of-any-integer.html
 */
static int get_bit(int decimal, int N){
 
    // Shifting the 1 for N-1 bits   
    int constant = 1 << (N-1);   //将00000001左移N-1位
 
    // If the bit is set, return 1
    if( decimal & constant ){
        return 1;
    }
 
    // If the bit is not set, return 0
    return 0;
}
 
static inline int powi(int num, unsigned int exponent){
    // NOT EQUIVALENT TO pow()
    if(exponent == 0)
        return 1;
 
    float res = num;
    for(unsigned int i=0; i<exponent-1; i++)
        res *= num;
 
    return res;
}
 
// Encoder参数为：行 列 方向
EncoderGrayCode::EncoderGrayCode(unsigned int _screenCols, unsigned int _screenRows, CodecDir _dir) : Encoder(_screenCols, _screenRows, _dir){
 
    N = 2;  //初始值为2
 
    // Set total pattern number
    if(dir & CodecDirHorizontal)
        this->N += Nhorz;         //如果编码为水平方向，N为2+Nhorz  N=12
 
    if(dir & CodecDirVertical)    //如果编码为水平方向，N为2+Nvert  N=8
        this->N += Nvert;
 
    // Encode every pixel column     //编码每一像素列  NbitsHor=10
    int NbitsHorz = ceilf(log2f((float)screenCols));  //先将列数转变为浮点数，再将列数取log2f运算，将float类型的小数去掉，然后进一，
 
    // Number of vertical encoding patterns  同上 针对每一行  9.58去掉小数进1为10，即NbitsVert=10
    int NbitsVert = ceilf(log2f((float)screenRows));
 
	//patterns的前两个元素为patternOn和patternOff
    cv::Mat patternOn(1, 1, CV_8UC3, cv::Scalar(0));  //定义一个1x1的patternOn矩阵
    patternOn.at<cv::Vec3b>(0,0) = cv::Vec3b(255, 255, 255);   //矩阵的（0,0）点定义为(255, 255, 255)白色
    patterns.push_back(patternOn); 
 
    cv::Mat patternOff(1, 1, CV_8UC3, cv::Scalar(0));  //定义一个1x1的patternOff矩阵
    patterns.push_back(patternOff);
 
 
    if(dir & CodecDirHorizontal){
        // Precompute horizontally encoding patterns
        for(unsigned int p=0; p<Nhorz; p++){
            cv::Mat patternP(1, screenCols, CV_8UC3);   //定义一个1行xscreenCols列的patternP矩阵
 
            // Loop through columns in first row       从第一行遍历所有列
            for(unsigned int j=0; j<screenCols; j++){
                unsigned int jGray = binaryToGray(j);   //将二进制转换为格雷码
 
                // Amplitude of channels   设置每个通道的灰度值
                float amp = get_bit(jGray, NbitsHorz-p);
                patternP.at<cv::Vec3b>(0,j) = cv::Vec3b(255.0*amp,255.0*amp,255.0*amp);
            }
            patterns.push_back(patternP);
        }
    }
    if(dir & CodecDirVertical){
        // Precompute vertical encoding patterns     
        for(unsigned int p=0; p<Nvert; p++){
            cv::Mat patternP(screenRows, 1, CV_8UC3);    //定义一个screenRows行x1列的patternP矩阵
 
            // Loop through rows in first column       从第一列遍历所有行
            for(unsigned int i=0; i<screenRows; i++){
 
                unsigned int iGray = binaryToGray(i);
 
                // Amplitude of channels
                float amp = get_bit(iGray, NbitsVert-p);
                patternP.at<cv::Vec3b>(i,0) = cv::Vec3b(255.0*amp,255.0*amp,255.0*amp);
            }
            patterns.push_back(patternP);
        }
    }
 
    #if 0
        for(unsigned int i=0; i<patterns.size(); i++){
            std::stringstream fileNameStream;
            fileNameStream << "pattern_" << std::setw(2) << std::setfill('0') << i << ".bmp";
            cv::imwrite(fileNameStream.str(), patterns[i]);
        }
 
    #endif
}