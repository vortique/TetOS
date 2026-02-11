/** TetOS - Kernel Entry
 * 
 * @file kmain.c
 * @author Vortique (wayw04321@gmail.com)
 * @brief Kernel entry point and initialization logic.
 * @version 0.1
 * @date 2026-02-11
 *
 * @copyright Copyright (c) 2026
 * @note This program is free software: you can redistribute it and/or modify it under the terms of the MIT License.
 *
 */

#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include <limine.h>

#pragma region Limine Requests

// Setting base revision number to 4, because this is latest recommended
// base revision described by the Limine boot protocol specification

__attribute__((used, section(".limine_requests"))) static volatile uint64_t limine_base_revision[] = LIMINE_BASE_REVISION(4);

// Limine requests can be placed everywhere, but its important to
// make them volatile and "used" so compiler doesn't optimize it randomly.
// And with "used" we say compiler don't delete this.

__attribute__((used, section(".limine_requests"))) static volatile struct limine_framebuffer_request framebuffer_request = {
    .id = LIMINE_FRAMEBUFFER_REQUEST_ID,
    .revision = 0};

// Markers for start and ends in the Limine requests.

__attribute__((used, section(".limine_request_start"))) static volatile uint64_t limine_requests_start_marker[] = LIMINE_REQUESTS_START_MARKER;

__attribute__((used, section(".limine_request_end"))) static volatile uint64_t limine_requests_end_marker = LIMINE_REQUESTS_END_MARKER;

#pragma endregion

#pragma region Memory Manipulations

// DO NOT rename or rename these functions! GCC and Clang needs it.
// But these can be edited, because being not optimized
// and possibly the logic of code will be edited and get optimized in future.
// They can be moved to another .c file too.

void *memcpy(void *restrict dest, const void *restrict src, size_t n)
{
    uint64_t *d64 = (uint64_t *)dest;
    const uint64_t *s64 = (const uint64_t *)src;

    // First read and write as chunks
    for (size_t i = 0; i < (n / 8); i++)
    {
        d64[i] = s64[i];
    }

    // Fill the remainders byte by byte
    uint8_t *d8 = (uint8_t *)dest;
    const uint8_t *s8 = (uint8_t *)src;

    for (int i = (n / 8) * 8; i < n; i++)
    {
        d8[i] = s8[i];
    }

    return dest;
}

void *memset(void *s, int c, size_t n)
{
    uint8_t *p = (uint8_t *)s;

    for (size_t i = 0; i < n; i++)
    {
        p[i] = (uint8_t)c;
    }

    return s;
}

void *memmove(void *dest, const void *src, size_t n)
{
    uint8_t *pdest = (uint8_t *)dest;
    const uint8_t *psrc = (const uint8_t *)src;

    if (src > dest)
    {
        for (size_t i = 0; i < n; i++)
        {
            pdest[i] = psrc[i];
        }
    }
    else if (src < dest)
    {
        for (size_t i = n; i > 0; i--)
        {
            pdest[i - 1] = psrc[i - 1];
        }
    }

    return dest;
}

int memcmp(const void *s1, const void *s2, size_t n)
{
    const uint8_t *p1 = (const uint8_t *)s1;
    const uint8_t *p2 = (const uint8_t *)s2;

    for (size_t i = 0; i < n; i++)
    {
        if (p1[i] != p2[i])
        {
            return p1[i] < p2[i] ? -1 : 1;
        }
    }

    return 0;
}

#pragma endregion

// Halt and catch fire function.
static void hcf(void)
{
    for (;;)
    {
        asm("hlt");
    }
}

#pragma region Kernel Entry

// The rest of the code is the entry of the kernel's entry point.
// If you rename it please edit the linker script accordingly.

void kmain(void)
{
    // Ask if the bootloader(Limine) understands our base revision.
    if (LIMINE_BASE_REVISION_SUPPORTED(limine_base_revision) == false)
    {
        hcf();
    }

    // Ensure we got a framebuffer.
    if (framebuffer_request.response == NULL || framebuffer_request.response->framebuffer_count < 1)
    {
        hcf();
    }

    // Get the first framebuffer.
    struct limine_framebuffer *framebuffer = framebuffer_request.response->framebuffers[0];

    volatile uint32_t *fb_ptr = framebuffer->address;

    // Paint the screen full red, because its Teto's color!
    for (size_t y = 0; y < framebuffer->height; y++)
    {
        for (size_t x = 0; x < framebuffer->width; x++)
        {
            size_t index = y * (framebuffer->pitch / 4) + x;
            fb_ptr[index] = 0xFF0000;
        }
    }

    hcf();
}

#pragma endregion
