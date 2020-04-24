#include <typeinfo>
#include <cmath>
/*
 *
 * This Matrix Header File Created By Rahul Mishra
 * ABLE TO PERFORM BASIC OPERATION LIKE
 * +,-,/,*,Determinant
 * YET TO BE ADD
 * ADJ MATRIX AND INVERSE MATRIX
 *  --ITS NECESSAY TO USE THIS HEADER FILE WITH <cmath> <typeinfo> <iostream> <vector>--
 *  <typeinfo> IS FOR typeid() operator
 *   cmath for pow()
 */

namespace Basic{
    template<typename type>
    class Matrix
    {
        unsigned int ncol;
        unsigned int nrow;
        unsigned int size;
        type vdef;
        std::string type_name;
        std::vector < std::vector<type> > Mat;
        void init();
    public :
        Matrix();
        Matrix(unsigned int ncol,unsigned int nrow,type = 0);
        Matrix<type> operator+ (Matrix<type>);
        Matrix<type> operator- (Matrix<type>);
        Matrix<type> operator* (Matrix<type>);                             //Matrix Multiplication
        void operator* (type);                                            //Scalar Multiplication
        Matrix<type> Sub_Mat(int);
        void input();
        double det();
        void Print();
    };
    template<typename type>
    Matrix<type>::Matrix()
    {
        ncol = nrow = 1;
        size = nrow * ncol;
        init();
    }
    template<typename type>
    Matrix<type>::Matrix(unsigned int argncol,unsigned int argnrow,type def):ncol(argncol),nrow(argnrow),vdef(def)
    {
        size = nrow * ncol;
        init();
    }
    template<typename type>
    void Matrix<type>::init()
    {
        Mat.resize(size);
        type_name = typeid(type).name();
        for(unsigned int i = 0;i < size;i++)
            Mat[i].resize(ncol);
        for(unsigned int i = 0;i < nrow;i++)
            for(unsigned int j = 0;j < ncol;j++)
              Mat[i][j] = vdef;
    }
    template<typename type>
    void Matrix<type>::Print()
    {
        std::cout<<std::endl;
        for(unsigned int i = 0;i < nrow;i++)
        {
            for(unsigned int j = 0;j < ncol;j++)
                std::cout<<Mat[i][j]<<" ";
            std::cout<<std::endl;
        }
    }
    template<typename type>
    void Matrix<type>::input()
    {
        type in;
        for(unsigned int i = 0;i < nrow;i++)
        {
          for(unsigned int j = 0;j < ncol;j++)
          {
              std::cin>>in;
              Mat[i][j] = in;
          }
        }
    }
    template<typename type>
    Matrix<type>  Matrix<type>::Sub_Mat(int argcol)
    {
        Matrix<type> temp(nrow - 1,nrow - 1,0);
        if(nrow == ncol)
            for(int i = 0;i < nrow ;i++)
            {
                int k = 0;
                for(int j = 0;j < ncol;j++)
                {
                 if(i == 0 || j == argcol)
                   continue;
                 if(j > temp.ncol - 1)
                     k = j - 1;
                 temp.Mat[i-1][k] = Mat[i][j];
                 k++;
                }
            }
        else
            throw "SQUARE MATRIX";
        return temp;
    }
    template<typename type>
    double Matrix<type>::det()
    {
        double sum = 0;
        if(size == 1)
          return Mat[0][0];
        for(int i = 0;i < ncol;i++)
          sum += Mat[0][i]*pow(-1,i)*Sub_Mat(i).det();
        return sum;
    }
    template<typename type>
    Matrix<type> Matrix<type>::operator+ (Matrix<type> a)
    {
     Matrix<type> temp(nrow,ncol,type());
        if(a.nrow == nrow && a.ncol == ncol)
       for(unsigned int i = 0;i < nrow;i++)
        {
            for(unsigned int j = 0;j < ncol;j++)
                temp.Mat[i][j] = a.Mat[i][j] + Mat[i][j];
        }
        return temp;
    }
    template<typename type>
    Matrix<type> Matrix<type>::operator- (Matrix<type> a)
    {
     Matrix<type> temp(nrow,ncol,type());
        if(a.nrow == nrow && a.ncol == ncol)
       for(unsigned int i = 0;i < nrow;i++)
        {
            for(unsigned int j = 0;j < ncol;j++)
                temp.Mat[i][j] = a.Mat[i][j] - Mat[i][j];
        }
        return temp;
    }
    template<typename type>
    Matrix<type> Matrix<type>::operator* (Matrix<type> a)
    {
     Matrix<type> temp(a.nrow,ncol,type());
        if(a.nrow == ncol && a.type_name == type_name)
       for(unsigned int i = 0;i < nrow;i++)
        {
            for(unsigned int j = 0;j < ncol;j++)
                for(unsigned int k = 0;k < a.nrow;k++)
                  temp.Mat[j][i] += a.Mat[j][k] * Mat[k][i];
        }
        return temp;
    }
    template<typename type>
    void Matrix<type>::operator* (type a)
    {
        for(unsigned int i = 0;i < nrow;i++)
        {
            for(unsigned int j = 0;j < ncol;j++)
                  Mat[i][j] *= a;
        }
    }
}//END OF NAMESPACE
