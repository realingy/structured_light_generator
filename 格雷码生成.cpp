#include <opencv2/opencv.hpp>

// Generate Gray codes.     格雷码在生成时 通过sl_scan_cols和sl_scan_rows的状态来判断生成行还是列条纹图案 

int generateGrayCodes(int width, int height,     //以1024 * 768为例
					  IplImage**& gray_codes,    
					  int& n_cols, int& n_rows,
					  int& col_shift, int& row_shift, 
					  bool sl_scan_cols, bool sl_scan_rows){
 
	// Determine number of required codes and row/column offsets.
	if(sl_scan_cols){                            //判断是生成哪种条纹
		n_cols = (int)ceil(log2(width));         //n_cols  格雷码的张数，即格雷码的最小宽度   n_cols=10 ;ceil是求大于该数的整数
		col_shift = (int)floor((pow(2.0,n_cols)-width)/2);       //列偏移量  比宽度多出来的？  col_shift=0；foolr是求小于该数的整数
	}
	else{
		n_cols = 0;
		col_shift = 0;
	}
	if(sl_scan_rows){
		n_rows = (int)ceil(log2(height));      //ceil(9.58) = 10 =n_rows
		row_shift = (int)floor((pow(2.0,n_rows)-height)/2);      //行偏移量 row_shift = floor(（1024-768）/2)=128
	}
	else{
		n_rows = 0;
		row_shift = 0;
	}	
 
	// Allocate Gray codes.   分配内存  
	gray_codes = new IplImage* [n_cols+n_rows+1];   //为什么要加1？加一张白色图案
 
	for(int i=0; i<(n_cols+n_rows+1); i++)  //i<21
		gray_codes[i] = cvCreateImage(cvSize(width,height), IPL_DEPTH_8U, 1);   //创建n_cols+n_rows+1 = 21张空图像内存，其中第一张为 全白图案
 
	int step = gray_codes[0]->widthStep/sizeof(uchar);  //widthStep=图像的宽度*通道数，即每一行需要的内存长度;step即每一行有多少个uchar类型的数据
 
	// Define first code as a white image.
	cvSet(gray_codes[0], cvScalar(255));
 
	// Define Gray codes for projector columns.    投影仪的列         三层循环！！！
	for(int c=0; c<width; c++){
		for(int i=0; i<n_cols; i++){     //i从0到9共循环10次，一行的每一像素都要循环10次，每循环一次就是对每一张图像的操作
			uchar* data = (uchar*)gray_codes[i+1]->imageData;       //data指针 指向格雷码图像的数据的地址
 
			if(i>0)  //从第二张图案开始  data[c]是一维数组，只能放一个值，应该是0或者1
				data[c] = (((c+col_shift) >> (n_cols-i-1)) & 1)^(((c+col_shift) >> (n_cols-i)) & 1);//先右移后与   i=1时，c分为3个部分，0-255,255-767,768-1023，编码分别为0,1,0 
			else
				data[c] = (((c+col_shift) >> (n_cols-i-1)) & 1);    //如果i=0时，c<=511,data[c]=0,c>511,data[c]=1
 
			//col_shift的作用：如果投影仪尺寸为912*1140，n_cols为10，则在编码时是以1024位来进行编码的，以c=0为例，会导致0-511=0,512-912=1，左右不等长
			//所以仍需要以512为中心，通过将0-912后移56变为56-968，这样512则变为了中心，左右编码位数相等。
			//像素值全部乘以255
			data[c] *= 255;  
 
			for(int r=1; r<height; r++)     //得到一行的编码后执行的平铺操作 
				data[r*step+c] = data[c];	//r*step为每一行所占的内存
		}
	}
 
	// Define Gray codes for projector rows.       投影仪的行
	for(int r=0; r<height; r++){
		for(int i=0; i<n_rows; i++){
			uchar* data = (uchar*)gray_codes[i+n_cols+1]->imageData; //格雷码的行列图案数据内存地址是连续的  
			if(i>0)
				data[r*step] = (((r+row_shift) >> (n_rows-i-1)) & 1)^(((r+row_shift) >> (n_rows-i)) & 1);
			else
				data[r*step] = (((r+row_shift) >> (n_rows-i-1)) & 1);
			data[r*step] *= 255;                   //data[r*step] = data[r*step]*255
			for(int c=1; c<width; c++)
				data[r*step+c] = data[r*step];	
		}
	}
 
	// Return without errors.
	return 0;
}

int main()
{
	// 生成格雷码条纹光栅
	// 以1024 * 768为例
	int generateGrayCodes(1024, 768, ,int& n_cols, int& n_rows, int& col_shift, int& row_shift, bool sl_scan_cols, bool sl_scan_rows)

}



