#include "mbed.h"
#include "HEPTA_CDH.h"
#include "HEPTA_EPS.h"
#include "HeptaCamera_GPS.h"

HEPTA_CDH cdh(PB_5, PB_4, PB_3, PA_8, "sd");
RawSerial pc(USBTX,USBRX,9600);
HEPTA_EPS eps(PA_0,PA_4);
HeptaCamera_GPS sensor(PA_9,PA_10);

int main()
{
    mkdir("/sd/mydir", 0777);
        //pc.printf("a");
    FILE *fp = fopen("/sd/mydir/sdtest.txt", "w");
    if(fp == NULL) {
        error("Could not open file for write\r\n");
        pc.printf("not SD card!\r\n");
    }
    fclose(fp);

    while (!pc.readable()){
        sensor.Sync();
        sensor.initialize(HeptaCamera_GPS::Baud115200, HeptaCamera_GPS::JpegResolution320x240);
        sensor.test_jpeg_snapshot_picture("/sd/test.jpg");
    }
    
}