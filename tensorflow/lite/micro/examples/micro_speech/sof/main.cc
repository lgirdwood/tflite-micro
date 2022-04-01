/* Copyright 2019 The TensorFlow Authors. All Rights Reserved.

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

    http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.
==============================================================================*/
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
#include <assert.h>

#include "tensorflow/lite/micro/examples/micro_speech/main_functions.h"

extern "C" {

//_reent* _impure_ptr;

/* should not be needed at runtime */
void abort(void)
{
	while(1) {}
}

/* assert */
void __assert_func(const char *fmt, int, const char *a, const char *b)
{
	assert(0);
}

/* should not be needed at runtime */
int atexit(void (*)())
{
	return 0;
}

#define SOF_MEM_CAPS_RAM			(1 << 0)

void *rballoc_align(uint32_t flags, uint32_t caps, size_t bytes,
		    uint32_t alignment);

void *malloc(size_t size)
{
	return rballoc_align(0, SOF_MEM_CAPS_RAM, size, 64);
}

void rfree(void *ptr);

void free(void *ptr)
{
	rfree(ptr);
}

void *rbrealloc_align(void *ptr, uint32_t flags, uint32_t caps, size_t bytes,
		      size_t old_bytes, uint32_t alignment);

// TODO get old bytes.
void *realloc(void *ptr, size_t bytes)
{
	return rbrealloc_align(ptr, 0, SOF_MEM_CAPS_RAM, bytes, bytes, 64);
}

int rstrlen(const char *s);

size_t strlen(const char *s)
{
	return rstrlen(s);
}

int rstrcmp(const char *s1, const char *s2);

int strcmp(const char *s1, const char *s2)
{
	return rstrcmp(s1, s2);
}

char *strcpy(char *dest, const char *src)
{
	size_t i;

	for (i = 0; src[i] != '\0'; i++)
	  dest[i] = src[i];
	dest[i + 1] = '\0';

	return dest;
}

int rstrncmp(const char *s1, const char *s2, size_t n)
{
	return 0;
}

int strncmp(const char *s1, const char *s2, size_t n)
{
	return rstrncmp(s1, s2, n);
}

double round(double x)
{
	return 0;
}

double floor(double x)
{
	return 0;
}

float roundf(float x)
{
	return 0;
}

double frexp(double x, int *exp)
{
	return 0;
}

float expf(float x)
{
	return 0;
}

float logf(float x)
{
	return 0;
}

float fmaxf(float x, float y)
{
	return 0;
}

float fminf(float x, float y)
{
	return 0;
}

size_t fwrite(const void *ptr, size_t size, size_t nmemb,
                     FILE *stream)
{
	return 0;
}

///home/lrg/work/sof/xtensa-cnl-elf/bin/../lib/gcc/xtensa-cnl-elf/9.3.0/../../../../xtensa-cnl-elf/bin/ld: ../src/audio/../../libtf-speech.a: in function `__gnu_cxx::__verbose_terminate_handler()':
//(.text._ZN9__gnu_cxx27__verbose_terminate_handlerEv+0xb2): undefined reference to `fputc'

int fputc(int c, FILE *stream)
{
	return 0;
}
#if 0
int fputs(const char *s, FILE *stream)
{
	return 0;
}
#endif

ssize_t write(int fd, const void *buf, size_t count)
{
	return 0;
}

int sprintf(char *str, const char *format, ...)
{
	return 0;
}

int _lseek_r(int)
{
return 0;
}

int _read_r(int)
{
return 0;
}

int _write_r(int)
{
return 0;
}

int _close_r(int)
{
return 0;
}

int _fstat_r(int)
{
return 0;
}
int _sbrk_r(int)
{
return 0;
}

int __dso_handle;

float __ieee754_sqrtf(float)
{
return 0;
}



#if 0
struct FrontendState;

int FrontendPopulateState(const struct FrontendConfig* config,
                          struct FrontendState* state, int sample_rate)
{
	return 0;
}

struct FrontendOutput {
  const uint16_t* values;
  size_t size;
};

struct FrontendOutput FrontendProcessSamples(struct FrontendState* state,
                                             const int16_t* samples,
                                             size_t num_samples,
                                             size_t* num_samples_read)
{
	struct FrontendOutput o;
	return o;
}

} // extern C

void tf_main(void) {
  setup();
  while (true) {
    loop();
  }
}
#endif
}
extern "C" void app_main() {
 // C entry point
	//tf_main();
}
