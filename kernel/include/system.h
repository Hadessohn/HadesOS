#include "stdint.h"

#ifndef SYSTEM_H
#define SYSTEM_H

static inline void outb(uint16_t port, uint8_t data) {
    asm volatile("outb %0, %1" : : "a" (data), "Nd" (port));
}

static inline void outw(uint16_t port, uint16_t data) {
    asm volatile("outw %0, %1" : : "a" (data), "Nd" (port));
}

static inline uint8_t inb(uint16_t port) {
    uint8_t data;
    asm volatile("inb %1, %0" : "=a" (data) : "Nd" (port));
    return data;
}

static inline void qemu_shutdown() {
    outw(0x604, 0x2000);
}

/*
// @params void* buf - pointer to the start
// @params int c - the value to be set
// @params int n - the size in bytes to be set
static void* memset(void* buf, int c, int n);
*/
// buf = Zeiger auf Speicheradresse
// c = zu setzender Wert
// n = größe des Speichers
static void* memset(void* buf, int c, int n) {
    uint8_t* p = (uint8_t*) buf;
    
    while (n--) {
        *p++ = c;
    }
    
    return buf;
}

static void* memcpy(void* dest, void* src, int size) {
    uint8_t* d = (uint8_t*) dest;
    uint8_t* s = (uint8_t*) src;
    for(int i = 0; i < size; i++) {
        d[i] = s[i];
    }
    return dest;
}

struct cpu_state {
    uint32_t    eax;
    uint32_t    ebx;
    uint32_t    ecx;
    uint32_t    edx;
    uint32_t    esi;
    uint32_t    edi;
    uint32_t    ebp;
    
    uint32_t    interrupt;
    uint32_t    error;
    
    uint32_t    eip;
    uint32_t    cs;
    uint32_t    eflags;
    uint32_t    esp;
    uint32_t    ss;
};

void panic(char* msg);

#endif
