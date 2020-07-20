#include <stdint.h>
#include <math.h>
#include <fcntl.h>
#include <signal.h>
#include <time.h>
#include <stdint.h>
#include <sys/types.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <time.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/mman.h>
#include <linux/stddef.h>

#include "RgaUtils.h"
#include "RockchipRga.h"

float get_bpp_from_format(int format) {
    float bpp = 0;

    switch (format) {
#ifdef ANDROID
        case HAL_PIXEL_FORMAT_RGB_565:
            bpp = 2;
            break;
        case HAL_PIXEL_FORMAT_RGB_888:
            bpp = 3;
            break;
        case HAL_PIXEL_FORMAT_RGBA_8888:
        case HAL_PIXEL_FORMAT_RGBX_8888:
        case HAL_PIXEL_FORMAT_BGRA_8888:
            bpp = 4;
            break;
        case HAL_PIXEL_FORMAT_YCrCb_420_SP:
        case HAL_PIXEL_FORMAT_YCrCb_NV12:
        case HAL_PIXEL_FORMAT_YCrCb_NV12_VIDEO:
            bpp = 1.5;
            break;
        case HAL_PIXEL_FORMAT_YCrCb_NV12_10:
            bpp = 1.875;
            break;
#endif
#ifdef LINUX
        case RK_FORMAT_RGB_565:
            bpp = 2;
            break;
        case RK_FORMAT_BGR_888:
        case RK_FORMAT_RGB_888:
            bpp = 3;
            break;
        case RK_FORMAT_RGBA_8888:
        case RK_FORMAT_RGBX_8888:
        case RK_FORMAT_BGRA_8888:
            bpp = 4;
            break;
        case RK_FORMAT_YCbCr_422_SP:
        case RK_FORMAT_YCbCr_422_P:
        case RK_FORMAT_YCrCb_422_SP:
        case RK_FORMAT_YCrCb_422_P:
            bpp = 2;
            break;
        case RK_FORMAT_YCbCr_420_SP:
        case RK_FORMAT_YCbCr_420_P:
        case RK_FORMAT_YCrCb_420_P:
        case RK_FORMAT_YCrCb_420_SP:
            bpp = 1.5;
            break;
        case RK_FORMAT_YCbCr_420_SP_10B:
        case RK_FORMAT_YCrCb_420_SP_10B:
            bpp = 1.875;
            break;
#endif
        default:
            printf("Is unsupport format now,please fix \n");
            return 0;
    }

    return bpp;
}

int get_buf_size_by_w_h_f(int w, int h, int f) {
    float bpp = get_bpp_from_format(f);
    int size = 0;

    size = (int)w * h * bpp;
    return size;
}

int get_string_by_format(char *value, int format) {
    if (!value)
        return -EINVAL;

    switch (format) {
#ifdef ANDROID
        case HAL_PIXEL_FORMAT_RGB_565:
            memcpy(value, "rgb565", sizeof("rgb565"));
            break;
        case HAL_PIXEL_FORMAT_RGB_888:
            memcpy(value, "rgb888", sizeof("rgb888"));
            break;
        case HAL_PIXEL_FORMAT_RGBA_8888:
            memcpy(value, "rgba8888", sizeof("rgba8888"));
            break;
        case HAL_PIXEL_FORMAT_RGBX_8888:
            memcpy(value, "rgbx8888", sizeof("rgbx8888"));
            break;
        case HAL_PIXEL_FORMAT_BGRA_8888:
            memcpy(value, "bgra8888", sizeof("bgra8888"));
            break;
        case HAL_PIXEL_FORMAT_YCrCb_420_SP:
            memcpy(value, "crcb420sp", sizeof("crcb420sp"));
            break;
        case HAL_PIXEL_FORMAT_YCrCb_NV12:
            memcpy(value, "nv12", sizeof("nv12"));
            break;
        case HAL_PIXEL_FORMAT_YCrCb_NV12_VIDEO:
            memcpy(value, "nv12", sizeof("nv12"));
            break;
        case HAL_PIXEL_FORMAT_YCrCb_NV12_10:
            memcpy(value, "nv12_10", sizeof("nv12_10"));
            break;
#endif
#ifdef LINUX
        case RK_FORMAT_RGB_565:
            memcpy(value, "rgb565", sizeof("rgb565"));
            break;
        case RK_FORMAT_RGB_888:
            memcpy(value, "rgb888", sizeof("rgb888"));
            break;
        case RK_FORMAT_RGBA_8888:
            memcpy(value, "rgba8888", sizeof("rgba8888"));
            break;
        case RK_FORMAT_RGBX_8888:
            memcpy(value, "rgbx8888", sizeof("rgbx8888"));
            break;
        case RK_FORMAT_BGRA_8888:
            memcpy(value, "bgra8888", sizeof("bgra8888"));
            break;
        case RK_FORMAT_YCrCb_420_SP:
            memcpy(value, "crcb420sp", sizeof("crcb420sp"));
            break;
        case RK_FORMAT_BGR_888:
            memcpy(value, "bgr888", sizeof("bgr888"));
            break;
        case RK_FORMAT_YCrCb_420_P:
            memcpy(value, "crcb420p", sizeof("crcb420p"));
            break;
        case RK_FORMAT_YCbCr_422_SP:
            memcpy(value, "cbcr422sp", sizeof("cbcr422sp"));
            break;
        case RK_FORMAT_YCbCr_422_P:
            memcpy(value, "cbcr422p", sizeof("cbcr422p"));
            break;
        case RK_FORMAT_YCbCr_420_SP:
            memcpy(value, "nv12", sizeof("nv12"));
            break;
        case RK_FORMAT_YCbCr_420_P:
            memcpy(value, "cbcr420p", sizeof("cbcr420p"));
            break;
        case RK_FORMAT_YCrCb_422_SP:
            memcpy(value, "crcb422sp", sizeof("crcb422sp"));
            break;
        case RK_FORMAT_YCrCb_422_P:
            memcpy(value, "crcb422p", sizeof("crcb422p"));
            break;
        case RK_FORMAT_YCbCr_420_SP_10B:
            memcpy(value, "nv12_10", sizeof("nv12_10"));
            break;
        case RK_FORMAT_YCrCb_420_SP_10B:
            memcpy(value, "crcb420sp_10", sizeof("crcb420sp_10"));
            break;
#endif
        default:
            printf("Is unsupport format now,please fix");
            return 0;
    }

    return 0;
}

int get_buf_from_file(void *buf, int f, int sw, int sh, int index) {
#ifdef ANDROID
    const char *inputFilePath = "/data/in%dw%d-h%d-%s.bin";
#endif

#ifdef LINUX
    const char *inputFilePath = "/usr/data/in%dw%d-h%d-%s.bin";
#endif

    char filePath[100];
    char fstring[30];
    int ret = 0;

    ret = get_string_by_format(fstring, f);
    snprintf(filePath, 100, inputFilePath, index, sw, sh, fstring);

    FILE *file = fopen(filePath, "rb");
    if (!file) {
        fprintf(stderr, "Could not open %s\n", filePath);
        return -EINVAL;
    }
    fread(buf, get_buf_size_by_w_h_f(sw, sh, f), 1, file);
    fclose(file);

    return 0;
}

int output_buf_data_to_file(void *buf, int f, int sw, int sh, int index) {
#ifdef ANDROID
    const char *outputFilePath = "/data/out%dw%d-h%d-%s.bin";
#endif

#ifdef LINUX
    const char *outputFilePath = "/usr/data/out%dw%d-h%d-%s.bin";
#endif

    char filePath[100];
    char fstring[30];
    int ret = 0;

    ret = get_string_by_format(fstring, f);
    snprintf(filePath, 100, outputFilePath, index, sw, sh, fstring);

    FILE *file = fopen(filePath, "wb+");
    if (!file) {
        fprintf(stderr, "Could not open %s\n", filePath);
        return false;
    } else
        fprintf(stderr, "open %s and write ok\n", filePath);
    fwrite(buf, get_buf_size_by_w_h_f(sw, sh, f), 1, file);
    fclose(file);

    return 0;
}
