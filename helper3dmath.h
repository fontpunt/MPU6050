/*
Demonstration Arduino sketch for MPU6050.
3D Math Helper class is placed under the MIT license

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
*/


#ifndef _HELPER_3DMATH_H_
#define _HELPER_3DMATH_H_

class Quaternion {
public:
    float w,x,y,z; 
        
    Quaternion();
    Quaternion(float nw, float nx, float ny, float nz);
    virtual ~Quaternion();

    Quaternion getProduct(Quaternion q);
    Quaternion getConjugate();
    float getMagnitude();
    void normalize();
    Quaternion getNormalized();
};

class VectorInt16 {
public:
    int16_t x,y,z;

    VectorInt16();
    VectorInt16(int16_t nx, int16_t ny, int16_t nz);
    virtual ~VectorInt16();

    float getMagnitude();
    void normalize();
    VectorInt16 getNormalized();
    void rotate(Quaternion *q);
    VectorInt16 getRotated(Quaternion *q);
};

class VectorFloat {
public:
    float x,y,z;

    VectorFloat();
    VectorFloat(float nx, float ny, float nz);
    virtual ~VectorFloat();

    float getMagnitude();
    void normalize();
    VectorFloat getNormalized();
    void rotate(Quaternion *q);
    VectorFloat getRotated(Quaternion *q);
};

#endif /* _HELPER_3DMATH_H_ */
