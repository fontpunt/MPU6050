#ifndef _MPU6050DMP_H_
#define _MPU6050DMP_H_

/* 
Demonstration Arduino sketch for MPU6050.
MPU6050DMP class is placed under the MIT license

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


#include "I2Cdev.h"
#include "helper3dmath.h"
#include "MPU6050.h"
#include <stdint.h>

class MPU6050DMP : public MPU6050 {
public:
    MPU6050DMP();
    virtual ~MPU6050DMP();
    uint8_t dmpInitialize(); 
    bool dmpPacketAvailable();
    uint8_t dmpGetAccel(int32_t *data, const uint8_t* packet); 
    uint8_t dmpGetAccel(int16_t *data, const uint8_t* packet); 
    uint8_t dmpGetAccel(VectorInt16 *v, const uint8_t* packet); 
    uint8_t dmpGetQuaternion(int32_t *data, const uint8_t* packet);
    uint8_t dmpGetQuaternion(int16_t *data, const uint8_t* packet);
    uint8_t dmpGetQuaternion(Quaternion *q, const uint8_t* packet);
    uint8_t dmpGetGyro(int32_t *data, const uint8_t* packet);
    uint8_t dmpGetGyro(int16_t *data, const uint8_t* packet);
    uint8_t dmpGetLinearAccel(VectorInt16 *v, VectorInt16 *vRaw, VectorFloat *gravity);
    uint8_t dmpGetLinearAccelInWorld(VectorInt16 *v, VectorInt16 *vReal, Quaternion *q);
    uint8_t dmpGetGravity(VectorFloat *v, Quaternion *q);
    uint8_t dmpGetEuler(float *data, Quaternion *q);
    uint8_t dmpGetYawPitchRoll(float *data, Quaternion *q, VectorFloat *gravity);
    uint8_t dmpProcessFIFOPacket(const unsigned char *dmpData);
    uint8_t dmpReadAndProcessFIFOPacket(uint8_t numPackets, uint8_t *processed);
    uint16_t dmpGetFIFOPacketSize();
private:
    uint16_t dmpPacketSize;
    uint8_t *dmpPacketBuffer;
};

#endif /* _MPU6050DMP_H_ */
