#ifndef DIVERT_H
#define DIVERT_H

#ifdef _WIN32
    #define DIVERT_PLATFORM_WINDOWS
#elif __linux__
    #define DIVERT_PLATFORM_LINUX
#elif __APPLE__
    #include "TargetConditionals.h"
    #if TARGET_OS_MAC
        #define DIVERT_PLATFORM_MACOS
    #endif
#endif

#if !defined(DIVERT_PLATFORM_WINDOWS) &&\
    !defined(DIVERT_PLATFORM_LINUX) &&\
    !defined(DIVERT_PLATFORM_MACOS)
    #error "libdivert: unsupported platform"
#endif

typedef unsigned char dv_byte_t;
typedef unsigned int dv_size_t;
typedef void* dv_ptr_t;

typedef enum
{
    DV_ERROR_NONE       = 0
} dv_error_t;

typedef enum
{
    DV_TYPE_IPV4_UDP    = 0xA,
    DV_TYPE_IPV4_ICMP   = 0xB,
    DV_TYPE_IPV4_TCP    = 0xC,
    DV_TYPE_IPV6_UDP    = 0xD,
    DV_TYPE_IPV6_ICMP   = 0xE,
    DV_TYPE_IPV6_TCP    = 0xF
} dv_packet_type_t;

typedef enum
{
    DV_MODE_DIVERT      = 0xA,
    DV_MODE_SNIFF       = 0xB,
    DV_MODE_INFO        = 0xC
} dv_capture_mode_t;

typedef enum
{
    DV_STATUS_IDLE      = 0x0,
    DV_STATUS_READY     = 0xA,
    DV_STATUS_ACTIVE    = 0xF
} dv_status_t;

typedef struct { /* TODO */ } dv_ipv4_header_t;
typedef struct { /* TODO */ } dv_ipv6_header_t;
typedef struct { /* TODO */ } dv_udp_header_t;
typedef struct { /* TODO */ } dv_icmp_header_t;
typedef struct { /* TODO */ } dv_tcp_header_t;

typedef void (*dv_handler_func_t)(dv_packet_type_t type, const dv_ptr_t ip_header, const dv_ptr_t protocol_header, const dv_byte_t* buffer, dv_size_t length);

dv_error_t divert_status(dv_status_t* status);

dv_error_t divert_open(dv_handler_func_t handler);
dv_error_t divert_close(void);

dv_error_t divert_filter_add(const dv_byte_t* buffer, dv_size_t length);
dv_error_t divert_filter_get(dv_size_t index, dv_byte_t* buffer, dv_size_t* length);
dv_error_t divert_filter_remove(dv_size_t index);
dv_error_t divert_filter_count(dv_size_t* count);
dv_error_t divert_filter_clear(void);

dv_error_t divert_start(dv_capture_mode_t mode);
dv_error_t divert_inject(dv_packet_type_t type, const dv_ptr_t ip_header, const dv_ptr_t protocol_header, const dv_byte_t* buffer, dv_size_t length);
dv_error_t divert_stop(void);

#endif // DIVERT_H
