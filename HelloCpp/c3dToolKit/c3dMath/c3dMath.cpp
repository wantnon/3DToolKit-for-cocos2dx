//
//  c3dMath.cpp
//  HelloCpp
//
//  Created by apple on 14-1-4.
//
//

#include "c3dMath.h"
Cc3dMatrix4 unitMat(){
    Cc3dMatrix4 mat(1,0,0,0,//col 1
                    0,1,0,0,
                    0,0,1,0,
                    0,0,0,1);
    return mat;
}
Cc3dMatrix4 zeroMat(){
    Cc3dMatrix4 mat(0,0,0,0,//col 1
                    0,0,0,0,
                    0,0,0,0,
                    0,0,0,0);
    return mat;
}
bool isEqual(const Cc3dMatrix4&mat1,const Cc3dMatrix4&mat2,float eps){
    for(int i=0;i<16;i++){
        float d=fabsf(mat1.getAt(i)-mat2.getAt(i));
        if(d>eps)return false;
    }
    return true;
}
bool isEqual(const Cc3dVector4&v1,const Cc3dVector4&v2,float eps){
    for(int i=0;i<4;i++){
        float d=fabsf(v1.getAt(i)-v2.getAt(i));
        if(d>eps)return false;
    }
    return true;
}
bool isUnitMat(const Cc3dMatrix4&mat){
    return isEqual(mat, unitMat());
}
Cc3dVector4 normalize(const Cc3dVector4&v){
    assert(v.w()==0);
    float r2=v.x()*v.x()+v.y()*v.y()+v.z()*v.z();
    if(r2==0){
        return Cc3dVector4(0,0,0,0);
    }
    float r=sqrtf(r2);
    Cc3dVector4 rs(v.x()/r,v.y()/r,v.z()/r,0);
    return rs;
}
float dot(const Cc3dVector4&v1,const Cc3dVector4&v2){
    return v1.x()*v2.x()+v1.y()*v2.y()+v1.z()*v2.z();
}
Cc3dVector4 cross(const Cc3dVector4&v1,const Cc3dVector4&v2)
{
    assert(v1.w()==0);
    assert(v2.w()==0);
    Cc3dVector4 rs(v1.y()*v2.z()-v1.z()*v2.y(),
                   v1.z()*v2.x()-v1.x()*v2.z(),
                   v1.x()*v2.y()-v1.y()*v2.x(),
                   0);//cross product result must be a vector, so the fourth component set to zero
    return rs;
}
Cc3dMatrix4 transpose(const Cc3dMatrix4&mat){
    
    const float* m=mat.getArray();
    float rs[16]={
        m[0],m[4],m[8],m[12],//col 1
        m[1],m[5],m[9],m[13],//col 2
        m[2],m[6],m[10],m[14],//col 3
        m[3],m[7],m[11],m[15]//col 4
    };
    return Cc3dMatrix4(rs);
}
Cc3dMatrix4 inverse(const Cc3dMatrix4&mat){
    float src[16];
    for(int i=0;i<16;i++)src[i]=mat.getAt(i);
    float inverse[16]={1,0,0,0,//col 1
        0,1,0,0,
        0,0,1,0,
        0,0,0,1};
    //----inverse src
    int i, j, k, swap;
    float t;
    float temp[4][4];
    
    for (i=0; i<4; i++) {
        for (j=0; j<4; j++) {
            temp[i][j] = src[i*4+j];
        }
    }
    
    for (i = 0; i < 4; i++) {
        //
        // Look for largest element in column
        //
        swap = i;
        for (j = i + 1; j < 4; j++) {
            if (fabsf(temp[j][i]) > fabsf(temp[i][i])) {
                swap = j;
            }
        }
        
        if (swap != i) {
            //
            // Swap rows.
            //
            for (k = 0; k < 4; k++) {
                t = temp[i][k];
                temp[i][k] = temp[swap][k];
                temp[swap][k] = t;
                
                t = inverse[i*4+k];
                inverse[i*4+k] = inverse[swap*4+k];
                inverse[swap*4+k] = t;
            }
        }
        
        if (temp[i][i] == 0) {
            //No non-zero pivot.  The matrix is singular, which shouldn't
            // happen.  This means the user gave us a bad matrix.
            assert(false);
            //return false;
        }
        
        t = temp[i][i];
        for (k = 0; k < 4; k++) {
            temp[i][k] /= t;
            inverse[i*4+k] /= t;
        }
        for (j = 0; j < 4; j++) {
            if (j != i) {
                t = temp[j][i];
                for (k = 0; k < 4; k++) {
                    temp[j][k] -= temp[i][k]*t;
                    inverse[j*4+k] -= inverse[i*4+k]*t;
                }
            }
        }
    }//got inverse
    Cc3dMatrix4 rs(inverse);
    return rs;
    
}
Cc3dVector4 toV4(const Cc3dVector2&v2,float z,float w){
    return Cc3dVector4(v2.x(), v2.y(), z, w);
}
Cc3dVector2 toV2(const Cc3dVector4&v4){
    return Cc3dVector2(v4.x(), v4.y());
}
float getLength2(const Cc3dVector4&v){//square of length
    assert(v.w()==0);
    return v.x()*v.x()+v.y()*v.y()+v.z()*v.z();
}
float getLength(const Cc3dVector4&v){
    assert(v.w()==0);
    return sqrtf(v.x()*v.x()+v.y()*v.y()+v.z()*v.z());
}
