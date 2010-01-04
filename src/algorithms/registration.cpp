#include "cv.h"
#include "highgui.h"

void PrintMat(const CvMat* A)  
{  
    int i,j;  
	printf("\nMatrix = :");  
    for(i=0;i<A->rows;i++)  
    {  
         printf("\n");  
           
         switch( CV_MAT_DEPTH(A->type) )  
         {  
         case CV_32F:  
         case CV_64F:  
             for(j=0;j<A->cols;j++)  
                 printf("%9.3f ", (float) cvGetReal2D( A, i, j ));  
             break;  
         case CV_8U:  
         case CV_16U:  
             for(j=0;j<A->cols;j++)  
                 printf("%6d",(int)cvGetReal2D( A, i, j ));  
             break;  
         default:  
             break;  
         }  
    }  
    printf("\n");  
 }

void computeDerivatives2(const CvMat* src1, const CvMat* src2, CvMat* fx, CvMat* fy, CvMat* ft, int rows, int cols)
{
    float filter[] = {0.03504, 0.24878, 0.43234, 0.24878, 0.03504};
	float dfilter[] = {0.10689, 0.28461, 0.0,  -0.28461,  -0.10689};

	CvMat fMat=cvMat(5, 1, int CV_32FC1, filter);	
	CvMat dfMat=cvMat(5, 1, int CV_32FC1, dfilter);

	//void cvFilter2D(const CvArr* src, CvArr* dst, const CvMat* kernel, CvPoint anchor=cvPoint(-1, -1))
	CvMat* kernel1 = cvCreateMat(5,5,CV_32FC1);
	CvMat* kernel2 = cvCreateMat(5,5,CV_32FC1);
	CvMat* kernel3 = cvCreateMat(5,5,CV_32FC1);

	cvGEMM(&fMat, &dfMat, 1.0, NULL, 0.0, kernel1, CV_GEMM_B_T);
	cvGEMM(&dfMat, &fMat, 1.0, NULL, 0.0, kernel2, CV_GEMM_B_T);
 	cvGEMM(&fMat, &fMat, 1.0, NULL, 0.0, kernel3, CV_GEMM_B_T);
    
	

	    CvMat*  dx1 = cvCreateMat(rows,cols, CV_32FC1);
		cvFilter2D(src1, dx1, kernel1);
		

		CvMat*  dy1 = cvCreateMat(rows,cols, CV_32FC1);
		cvFilter2D(src1, dy1, kernel2);
        // CvMemStorage* storage = cvCreateMemStorage(0);
        // CvSeq* contour = 0;
        CvMat*  blur1 = cvCreateMat(rows,cols, CV_32FC1);
		cvFilter2D(src1, blur1, kernel3);
		
	    CvMat*  dx2 = cvCreateMat(rows,cols, CV_32FC1);
		cvFilter2D(src2, dx2, kernel1);
		
		CvMat*  dy2 = cvCreateMat(rows,cols, CV_32FC1);
		cvFilter2D(src2, dy2, kernel2);
        // CvMemStorage* storage = cvCreateMemStorage(0);
        // CvSeq* contour = 0;
        CvMat*  blur2 = cvCreateMat(rows,cols, CV_32FC1);;
		cvFilter2D(src2, blur2, kernel3);
        // cvThreshold( src, src, 1, 255, CV_THRESH_BINARY );

		cvAddWeighted(dx1, 0.5, dx2, 0.5, 0, fx);
		cvAddWeighted(dy1, 0.5, dy2, 0.5, 0, fy);
		cvSub(blur2, blur1, ft);
        
        // cvFindContours( src, storage, &contour, sizeof(CvContour),
                      // CV_RETR_CCOMP, CV_CHAIN_APPROX_SIMPLE );
        // cvZero( dst );

        // for( ; contour != 0; contour = contour->h_next )
        // {
            // CvScalar color = CV_RGB( rand()&255, rand()&255, rand()&255 );
            // /* replace CV_FILLED with 1 to see the outlines */
            // cvDrawContours( dst, contour, color, color, -1, CV_FILLED, 8 );
        // }

}

int main( int argc, char** argv )
{
   
	
	
	
	IplImage* src1;
	IplImage* src2;
    // the first command line parameter must be file name of binary
    // (black-n-white) image
    if((src1=cvLoadImage("test1.png", 0))!= 0 && (src2=cvLoadImage("test2.png" ,0))!= 0)
    {
        int cols=src1->width;
		int rows=src1->height;
        
		CvMat*  src1Mat = cvCreateMat(rows,cols, CV_32FC1);
        CvMat*  src2Mat= cvCreateMat(rows,cols, CV_32FC1);
        cvConvertScale(src1, src1Mat, 1.0/255.0);
        cvConvertScale(src2, src2Mat, 1.0/255.0);
     

		CvMat*  fx = cvCreateMat(rows,cols, CV_32FC1 );
		CvMat*  fy = cvCreateMat(rows,cols, CV_32FC1 );
		CvMat*  ft = cvCreateMat(rows,cols, CV_32FC1 );
		computeDerivatives2(src1Mat, src2Mat, fx, fy, ft, rows, cols);
	    /*for test
		float d1[]={1,1,1,1,1,1,1,1,1,1,1,1};
		float d2[]={2,2,2,2,2,2,2,2,2,2,2,2};
		float d3[]={3,3,3,3,3,3,3,3,3,3,3,3};
        CvMat fx1=cvMat(4, 3, int CV_32FC1, d1);	
	    CvMat fy1=cvMat(4, 3, int CV_32FC1, d2);
		CvMat ft1=cvMat(4, 3, int CV_32FC1, d3);
		rows=4;
		cols=3;
		CvMat* fx=&fx1;
		CvMat* fy=&fy1;
		CvMat* ft=&ft1;
		*/
		cvNamedWindow( "Components", 1 );
        cvShowImage( "Components", ft );
		CvMat* A=cvCreateMat(cols*rows, 8 , CV_32FC1);
		CvMat* b=cvCreateMat(cols*rows, 1 , CV_32FC1);
		printf("%f\n",CV_MAT_ELEM(*fx, float, 0, 0));
		for(int k=0;k<cols;k++)
			for(int l=0;l<rows;l++)
			{
				*((float*)CV_MAT_ELEM_PTR(*A,k*rows+l,0))=(k+1)*CV_MAT_ELEM(*fx, float, l, k);
				*((float*)CV_MAT_ELEM_PTR(*A,k*rows+l,1))=(l+1)*CV_MAT_ELEM(*fx, float, l, k);
				*((float*)CV_MAT_ELEM_PTR(*A,k*rows+l,2))=CV_MAT_ELEM(*fx, float, l, k);
				*((float*)CV_MAT_ELEM_PTR(*A,k*rows+l,3))=(k+1)*CV_MAT_ELEM(*fy, float, l, k);
                *((float*)CV_MAT_ELEM_PTR(*A,k*rows+l,4))=(l+1)*CV_MAT_ELEM(*fy, float, l, k);
				*((float*)CV_MAT_ELEM_PTR(*A,k*rows+l,5))=CV_MAT_ELEM(*fy, float, l, k);
				*((float*)CV_MAT_ELEM_PTR(*A,k*rows+l,6))=(k+1)*CV_MAT_ELEM(*ft, float, l, k)-(k+1)*(k+1)*CV_MAT_ELEM(*fx, float, l, k)-(l+1)*(k+1)*CV_MAT_ELEM(*fy, float, l, k);
				*((float*)CV_MAT_ELEM_PTR(*A,k*rows+l,7))=(l+1)*CV_MAT_ELEM(*ft, float, l, k)-(l+1)*(k+1)*CV_MAT_ELEM(*fx, float, l, k)-(l+1)*(l+1)*CV_MAT_ELEM(*fy, float, l, k);
			    *((float*)CV_MAT_ELEM_PTR(*b,k*rows+l,0))=(k+1)*CV_MAT_ELEM(*fx, float, l, k)+(l+1)*CV_MAT_ELEM(*fy, float, l, k)-CV_MAT_ELEM(*ft, float, l, k);
			}
       
	
      
        CvMat* p=cvCreateMat(8,1, CV_32FC1);
        cvSolve(A, b, p); 
		PrintMat(p); 
        cvWaitKey(0);
    }
}
