/*
 * Copyright (C) 2018 Jianhui Zhao <jianhuizhao329@gmail.com>
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301
 * USA
 */

#ifndef _BUFFER_H
#define _BUFFER_H

#include <stdint.h>
#include <stdarg.h>
#include <sys/types.h>

/*
 *  buffer:
 *  +--------------+--------------+--------------+--------------+--------------+
 *  | buffer_chain | buffer_chain | buffer_chain | buffer_chain | buffer_chain |
 *  +--------------+--------------+--------------+--------------+--------------+
 *
 *  buffer_chain:
 *  head   data                      end
 *  +---------+---------------+------+
 *  | drained |    content    | free |
 *  +---------+---------------+------+
 */

struct buffer_chain {
    struct buffer_chain *next;

    uint8_t *data;
    uint8_t *tail;
    uint8_t *end;

    uint8_t head[0];
};

struct buffer {
    struct buffer_chain *head;
    struct buffer_chain *tail;
};

void buffer_free(struct buffer *b);

/* Append data to the end of a buffer. Returns the remaining unadded bytes */
int buffer_add(struct buffer *b, const void *source, size_t len);

/* Read data from a buffer and drain the bytes read. Return the number of bytes read, */
int buffer_remove(struct buffer *b, char *dest, size_t len);

/* Remove a specified number of bytes data from the beginning of a buffer. */
void buffer_drain(struct buffer *b, size_t len);

/* Append a string to the end of a buffer. Returns the remaining unadded bytes */
int buffer_add_string(struct buffer *b, const char *s);

/* Append a va_list formatted string to the end of a buffer. Return the number of characters printed */
int buffer_add_vprintf(struct buffer *b, const char *fmt, va_list ap) __attribute__((format(printf, 2, 0)));

/* Append a formatted string to the end of a buffer. Return the number of characters printed */
int buffer_add_printf(struct buffer *b, const char *fmt, ...) __attribute__((format(printf, 2, 3)));

#endif
