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


#include <math.h>
#include <stdint.h>
#include "helper3dmath.h"


Quaternion::Quaternion() {
    w = 1.0f;
    x = 0.0f;
    y = 0.0f;
    z = 0.0f;
}
 
Quaternion::Quaternion(float nw, float nx, float ny, float nz) {
    w = nw;
    x = nx;
    y = ny;
    z = nz;
}

Quaternion::~Quaternion() {}

Quaternion Quaternion::getProduct(Quaternion q) {
    // Quaternion multiplication is defined by:
    //     (Q1 * Q2).w = (w1w2 - x1x2 - y1y2 - z1z2)
    //     (Q1 * Q2).x = (w1x2 + x1w2 + y1z2 - z1y2)
    //     (Q1 * Q2).y = (w1y2 - x1z2 + y1w2 + z1x2)
    //     (Q1 * Q2).z = (w1z2 + x1y2 - y1x2 + z1w2
    return Quaternion(
        w*q.w - x*q.x - y*q.y - z*q.z,  // new w
        w*q.x + x*q.w + y*q.z - z*q.y,  // new x
        w*q.y - x*q.z + y*q.w + z*q.x,  // new y
        w*q.z + x*q.y - y*q.x + z*q.w); // new z
}

Quaternion Quaternion::getConjugate() {
    return Quaternion(w, -x, -y, -z);
}

float Quaternion::getMagnitude() {
    return sqrt(w*w + x*x + y*y + z*z);
}

void Quaternion::normalize() {
    float m = getMagnitude();
    w /= m;
    x /= m;
    y /= m;
    z /= m;
}

Quaternion Quaternion::getNormalized() {
    Quaternion r(w, x, y, z);
    r.normalize();
    return r;
}


VectorInt16::VectorInt16() {
    x = 0;
    y = 0;
    z = 0;
}

VectorInt16::VectorInt16(int16_t nx, int16_t ny, int16_t nz) {
    x = nx;
    y = ny;
    z = nz;
}

VectorInt16::~VectorInt16() {}

float VectorInt16::getMagnitude() {
    return sqrt(x*x + y*y + z*z);
}

void VectorInt16::normalize() {
    float m = getMagnitude();
    x /= m;
    y /= m;
    z /= m;
}

VectorInt16 VectorInt16::getNormalized() {
    VectorInt16 r(x, y, z);
    r.normalize();
    return r;
}

void VectorInt16::rotate(Quaternion *q) {
    // http://www.cprogramming.com/tutorial/3d/quaternions.html
    // http://www.euclideanspace.com/maths/algebra/realNormedAlgebra/quaternions/transforms/index.htm
    // http://content.gpwiki.org/index.php/OpenGL:Tutorials:Using_Quaternions_to_represent_rotation
    // ^ or: http://webcache.googleusercontent.com/search?q=cache:xgJAp3bDNhQJ:content.gpwiki.org/index.php/OpenGL:Tutorials:Using_Quaternions_to_represent_rotation&hl=en&gl=us&strip=1
        
    // P_out = q * P_in * conj(q)
    // - P_out is the output vector
    // - q is the orientation quaternion
    // - P_in is the input vector (a*aReal)
    // - conj(q) is the conjugate of the orientation quaternion (q=[w,x,y,z], q*=[w,-x,-y,-z])
    Quaternion p(0, x, y, z);

    // quaternion multiplication: q * p, stored back in p
    p = q -> getProduct(p);

    // quaternion multiplication: p * conj(q), stored back in p
    p = p.getProduct(q -> getConjugate());

    // p quaternion is now [0, x', y', z']
    x = p.x;
    y = p.y;
    z = p.z;
}

VectorInt16 VectorInt16::getRotated(Quaternion *q) {
    VectorInt16 r(x, y, z);
    r.rotate(q);
    return r;
}


VectorFloat::VectorFloat() {
    x = 0;
    y = 0;
    z = 0;
}

VectorFloat::VectorFloat(float nx, float ny, float nz) {
    x = nx;
    y = ny;
    z = nz;
}

VectorFloat::~VectorFloat() {}

float VectorFloat::getMagnitude() {
    return sqrt(x*x + y*y + z*z);
}

void VectorFloat::normalize() {
    float m = getMagnitude();
    x /= m;
    y /= m;
    z /= m;
}

VectorFloat VectorFloat::getNormalized() {
    VectorFloat r(x, y, z);
    r.normalize();
    return r;
}

void VectorFloat::rotate(Quaternion *q) {
    Quaternion p(0, x, y, z);

    // quaternion multiplication: q * p, stored back in p
    p = q -> getProduct(p);

    // quaternion multiplication: p * conj(q), stored back in p
    p = p.getProduct(q -> getConjugate());

    // p quaternion is now [0, x', y', z']
    x = p.x;
    y = p.y;
    z = p.z;
}

VectorFloat VectorFloat::getRotated(Quaternion *q) {
    VectorFloat r(x, y, z);
    r.rotate(q);
    return r;
}
