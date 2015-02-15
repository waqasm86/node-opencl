#include "common.h"
#include "commandqueue.h"
#include "context.h"
#include "device.h"
#include "event.h"
#include "kernel.h"
#include "memobj.h"
#include "platform.h"
#include "program.h"
#include "sampler.h"

#define JS_CL_CONSTANT(name) exports->Set(JS_STR( #name ), JS_INT(CL_ ## name))

#define NODE_DEFINE_CONSTANT_VALUE(exports, name, value)                   \
  (exports)->Set(NanNew<v8::String>(name),                         \
                NanNew<v8::Integer>((uint)value), \
                static_cast<v8::PropertyAttribute>(v8::ReadOnly|v8::DontDelete))

#ifdef _WIN32
/*-
 * Copyright (c) 1990, 1993
 *  The Regents of the University of California.  All rights reserved.
 *
 * This code is derived from software contributed to Berkeley by
 * Chris Torek.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. All advertising materials mentioning features or use of this software
 *    must display the following acknowledgement:
 *  This product includes software developed by the University of
 *  California, Berkeley and its contributors.
 * 4. Neither the name of the University nor the names of its contributors
 *    may be used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE REGENTS AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE REGENTS OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 */
char *strcasestr(const char *s, char *find) {
  char c, sc;
  size_t len;

  if ((c = *find++) != 0) {
    c = tolower((unsigned char)c);
    len = strlen(find);

    do {
      do {
        if ((sc = *s++) == 0)
          return (NULL);
      } while ((char)tolower((unsigned char)sc) != c);
    } while (strncasecmp(s, find, len) != 0);
    s--;
  }
  return ((char *)s);
}
#endif

extern "C" {

void init(Handle<Object> exports)
{
#ifdef CL_VERSION_1_2
  exports->Set(JS_STR("CL_VERSION_1_2" ), JS_BOOL(true));
#else
  exports->Set(JS_STR("CL_VERSION_1_2" ), JS_BOOL(false));
#endif

  // OpenCL 1.x methods
  opencl::CommandQueue::init(exports);
  opencl::Context::init(exports);
  opencl::Device::init(exports);
//  opencl::Event::init(exports);
  opencl::Kernel::init(exports);
  opencl::MemObj::init(exports);
  opencl::Platform::init(exports);
  opencl::Program::init(exports);
  opencl::Sampler::init(exports);

  /**
   * Platform-dependent byte sizes
   */
  NODE_DEFINE_CONSTANT_VALUE(exports, "size_CHAR", sizeof(char));
  NODE_DEFINE_CONSTANT_VALUE(exports, "size_SHORT", sizeof(short));
  NODE_DEFINE_CONSTANT_VALUE(exports, "size_INT", sizeof(int));
  NODE_DEFINE_CONSTANT_VALUE(exports, "size_LONG", sizeof(long));
  NODE_DEFINE_CONSTANT_VALUE(exports, "size_FLOAT", sizeof(float));
  NODE_DEFINE_CONSTANT_VALUE(exports, "size_DOUBLE", sizeof(double));
  NODE_DEFINE_CONSTANT_VALUE(exports, "size_HALF", sizeof(float) >> 1);

  // OpenCL 1.x constants

  /* Error Codes */
  JS_CL_CONSTANT(SUCCESS);
  JS_CL_CONSTANT(DEVICE_NOT_FOUND);
  JS_CL_CONSTANT(DEVICE_NOT_AVAILABLE);
  JS_CL_CONSTANT(COMPILER_NOT_AVAILABLE);
  JS_CL_CONSTANT(MEM_OBJECT_ALLOCATION_FAILURE);
  JS_CL_CONSTANT(OUT_OF_RESOURCES);
  JS_CL_CONSTANT(OUT_OF_HOST_MEMORY);
  JS_CL_CONSTANT(PROFILING_INFO_NOT_AVAILABLE);
  JS_CL_CONSTANT(MEM_COPY_OVERLAP);
  JS_CL_CONSTANT(IMAGE_FORMAT_MISMATCH);
  JS_CL_CONSTANT(IMAGE_FORMAT_NOT_SUPPORTED);
  JS_CL_CONSTANT(BUILD_PROGRAM_FAILURE);
  JS_CL_CONSTANT(MAP_FAILURE);
  JS_CL_CONSTANT(MISALIGNED_SUB_BUFFER_OFFSET);
  JS_CL_CONSTANT(EXEC_STATUS_ERROR_FOR_EVENTS_IN_WAIT_LIST);
#ifdef CL_VERSION_1_2
  JS_CL_CONSTANT(COMPILE_PROGRAM_FAILURE);
  JS_CL_CONSTANT(LINKER_NOT_AVAILABLE);
  JS_CL_CONSTANT(LINK_PROGRAM_FAILURE);
  JS_CL_CONSTANT(DEVICE_PARTITION_FAILED);
  JS_CL_CONSTANT(KERNEL_ARG_INFO_NOT_AVAILABLE);
#endif

  JS_CL_CONSTANT(INVALID_VALUE);
  JS_CL_CONSTANT(INVALID_DEVICE_TYPE);
  JS_CL_CONSTANT(INVALID_PLATFORM);
  JS_CL_CONSTANT(INVALID_DEVICE);
  JS_CL_CONSTANT(INVALID_CONTEXT);
  JS_CL_CONSTANT(INVALID_QUEUE_PROPERTIES);
  JS_CL_CONSTANT(INVALID_COMMAND_QUEUE);
  JS_CL_CONSTANT(INVALID_HOST_PTR);
  JS_CL_CONSTANT(INVALID_MEM_OBJECT);
  JS_CL_CONSTANT(INVALID_IMAGE_FORMAT_DESCRIPTOR);
  JS_CL_CONSTANT(INVALID_IMAGE_SIZE);
  JS_CL_CONSTANT(INVALID_SAMPLER);
  JS_CL_CONSTANT(INVALID_BINARY);
  JS_CL_CONSTANT(INVALID_BUILD_OPTIONS);
  JS_CL_CONSTANT(INVALID_PROGRAM);
  JS_CL_CONSTANT(INVALID_PROGRAM_EXECUTABLE);
  JS_CL_CONSTANT(INVALID_KERNEL_NAME);
  JS_CL_CONSTANT(INVALID_KERNEL_DEFINITION);
  JS_CL_CONSTANT(INVALID_KERNEL);
  JS_CL_CONSTANT(INVALID_ARG_INDEX);
  JS_CL_CONSTANT(INVALID_ARG_VALUE);
  JS_CL_CONSTANT(INVALID_ARG_SIZE);
  JS_CL_CONSTANT(INVALID_KERNEL_ARGS);
  JS_CL_CONSTANT(INVALID_WORK_DIMENSION);
  JS_CL_CONSTANT(INVALID_WORK_GROUP_SIZE);
  JS_CL_CONSTANT(INVALID_WORK_ITEM_SIZE);
  JS_CL_CONSTANT(INVALID_GLOBAL_OFFSET);
  JS_CL_CONSTANT(INVALID_EVENT_WAIT_LIST);
  JS_CL_CONSTANT(INVALID_EVENT);
  JS_CL_CONSTANT(INVALID_OPERATION);
  JS_CL_CONSTANT(INVALID_GL_OBJECT);
  JS_CL_CONSTANT(INVALID_BUFFER_SIZE);
  JS_CL_CONSTANT(INVALID_MIP_LEVEL);
  JS_CL_CONSTANT(INVALID_GLOBAL_WORK_SIZE);
  JS_CL_CONSTANT(INVALID_PROPERTY);
#ifdef CL_VERSION_1_2
  JS_CL_CONSTANT(INVALID_IMAGE_DESCRIPTOR);
  JS_CL_CONSTANT(INVALID_COMPILER_OPTIONS);
  JS_CL_CONSTANT(INVALID_LINKER_OPTIONS);
  JS_CL_CONSTANT(INVALID_DEVICE_PARTITION_COUNT);
#endif
#ifdef CL_VERSION_2_0
  JS_CL_CONSTANT(INVALID_PIPE_SIZE);
  JS_CL_CONSTANT(INVALID_DEVICE_QUEUE);
#endif

  /* OpenCL Version */
  JS_CL_CONSTANT(VERSION_1_0);
  JS_CL_CONSTANT(VERSION_1_1);
#ifdef CL_VERSION_1_2
  JS_CL_CONSTANT(VERSION_1_2);
#endif
#ifdef CL_VERSION_2_0
  JS_CL_CONSTANT(VERSION_2_0);
#endif

  /* cl_bool */
  JS_CL_CONSTANT(FALSE);
  JS_CL_CONSTANT(TRUE);
#ifdef CL_VERSION_1_2
  JS_CL_CONSTANT(BLOCKING);
  JS_CL_CONSTANT(NON_BLOCKING);
#endif

  /* cl_platform_info */
  JS_CL_CONSTANT(PLATFORM_PROFILE);
  JS_CL_CONSTANT(PLATFORM_VERSION);
  JS_CL_CONSTANT(PLATFORM_NAME);
  JS_CL_CONSTANT(PLATFORM_VENDOR);
  JS_CL_CONSTANT(PLATFORM_EXTENSIONS);

  /* cl_device_type - bitfield */
  JS_CL_CONSTANT(DEVICE_TYPE_DEFAULT);
  JS_CL_CONSTANT(DEVICE_TYPE_CPU);
  JS_CL_CONSTANT(DEVICE_TYPE_GPU);
  JS_CL_CONSTANT(DEVICE_TYPE_ACCELERATOR);
#ifdef CL_VERSION_1_2
  JS_CL_CONSTANT(DEVICE_TYPE_CUSTOM);
#endif
  JS_CL_CONSTANT(DEVICE_TYPE_ALL);

  /* cl_device_info */
  JS_CL_CONSTANT(DEVICE_TYPE);
  JS_CL_CONSTANT(DEVICE_VENDOR_ID);
  JS_CL_CONSTANT(DEVICE_MAX_COMPUTE_UNITS);
  JS_CL_CONSTANT(DEVICE_MAX_WORK_ITEM_DIMENSIONS);
  JS_CL_CONSTANT(DEVICE_MAX_WORK_GROUP_SIZE);
  JS_CL_CONSTANT(DEVICE_MAX_WORK_ITEM_SIZES);
  JS_CL_CONSTANT(DEVICE_PREFERRED_VECTOR_WIDTH_CHAR);
  JS_CL_CONSTANT(DEVICE_PREFERRED_VECTOR_WIDTH_SHORT);
  JS_CL_CONSTANT(DEVICE_PREFERRED_VECTOR_WIDTH_INT);
  JS_CL_CONSTANT(DEVICE_PREFERRED_VECTOR_WIDTH_LONG);
  JS_CL_CONSTANT(DEVICE_PREFERRED_VECTOR_WIDTH_FLOAT);
  JS_CL_CONSTANT(DEVICE_PREFERRED_VECTOR_WIDTH_DOUBLE);
  JS_CL_CONSTANT(DEVICE_MAX_CLOCK_FREQUENCY);
  JS_CL_CONSTANT(DEVICE_ADDRESS_BITS);
  JS_CL_CONSTANT(DEVICE_MAX_READ_IMAGE_ARGS);
  JS_CL_CONSTANT(DEVICE_MAX_WRITE_IMAGE_ARGS);
  JS_CL_CONSTANT(DEVICE_MAX_MEM_ALLOC_SIZE);
  JS_CL_CONSTANT(DEVICE_IMAGE2D_MAX_WIDTH);
  JS_CL_CONSTANT(DEVICE_IMAGE2D_MAX_HEIGHT);
  JS_CL_CONSTANT(DEVICE_IMAGE3D_MAX_WIDTH);
  JS_CL_CONSTANT(DEVICE_IMAGE3D_MAX_HEIGHT);
  JS_CL_CONSTANT(DEVICE_IMAGE3D_MAX_DEPTH);
  JS_CL_CONSTANT(DEVICE_IMAGE_SUPPORT);
  JS_CL_CONSTANT(DEVICE_MAX_PARAMETER_SIZE);
  JS_CL_CONSTANT(DEVICE_MAX_SAMPLERS);
  JS_CL_CONSTANT(DEVICE_MEM_BASE_ADDR_ALIGN);
  JS_CL_CONSTANT(DEVICE_MIN_DATA_TYPE_ALIGN_SIZE);
  JS_CL_CONSTANT(DEVICE_SINGLE_FP_CONFIG);
  JS_CL_CONSTANT(DEVICE_GLOBAL_MEM_CACHE_TYPE);
  JS_CL_CONSTANT(DEVICE_GLOBAL_MEM_CACHELINE_SIZE);
  JS_CL_CONSTANT(DEVICE_GLOBAL_MEM_CACHE_SIZE);
  JS_CL_CONSTANT(DEVICE_GLOBAL_MEM_SIZE);
  JS_CL_CONSTANT(DEVICE_MAX_CONSTANT_BUFFER_SIZE);
  JS_CL_CONSTANT(DEVICE_MAX_CONSTANT_ARGS);
  JS_CL_CONSTANT(DEVICE_LOCAL_MEM_TYPE);
  JS_CL_CONSTANT(DEVICE_LOCAL_MEM_SIZE);
  JS_CL_CONSTANT(DEVICE_ERROR_CORRECTION_SUPPORT);
  JS_CL_CONSTANT(DEVICE_PROFILING_TIMER_RESOLUTION);
  JS_CL_CONSTANT(DEVICE_ENDIAN_LITTLE);
  JS_CL_CONSTANT(DEVICE_AVAILABLE);
  JS_CL_CONSTANT(DEVICE_COMPILER_AVAILABLE);
  JS_CL_CONSTANT(DEVICE_EXECUTION_CAPABILITIES);
  JS_CL_CONSTANT(DEVICE_QUEUE_PROPERTIES); //deprecated in 2.0
#ifdef CL_VERSION_2_0
  JS_CL_CONSTANT(DEVICE_QUEUE_ON_HOST_PROPERTIES);
#endif
  JS_CL_CONSTANT(DEVICE_NAME);
  JS_CL_CONSTANT(DEVICE_VENDOR);
  JS_CL_CONSTANT(DRIVER_VERSION);
  JS_CL_CONSTANT(DEVICE_PROFILE);
  JS_CL_CONSTANT(DEVICE_VERSION);
  JS_CL_CONSTANT(DEVICE_EXTENSIONS);
  JS_CL_CONSTANT(DEVICE_PLATFORM);
#ifdef CL_VERSION_1_2
  JS_CL_CONSTANT(DEVICE_DOUBLE_FP_CONFIG);
#endif
  JS_CL_CONSTANT(DEVICE_HALF_FP_CONFIG);
  JS_CL_CONSTANT(DEVICE_PREFERRED_VECTOR_WIDTH_HALF);
  JS_CL_CONSTANT(DEVICE_HOST_UNIFIED_MEMORY); // deprecated in 2.0
  JS_CL_CONSTANT(DEVICE_NATIVE_VECTOR_WIDTH_CHAR);
  JS_CL_CONSTANT(DEVICE_NATIVE_VECTOR_WIDTH_SHORT);
  JS_CL_CONSTANT(DEVICE_NATIVE_VECTOR_WIDTH_INT);
  JS_CL_CONSTANT(DEVICE_NATIVE_VECTOR_WIDTH_LONG);
  JS_CL_CONSTANT(DEVICE_NATIVE_VECTOR_WIDTH_FLOAT);
  JS_CL_CONSTANT(DEVICE_NATIVE_VECTOR_WIDTH_DOUBLE);
  JS_CL_CONSTANT(DEVICE_NATIVE_VECTOR_WIDTH_HALF);
  JS_CL_CONSTANT(DEVICE_OPENCL_C_VERSION);
#ifdef CL_VERSION_1_2
  JS_CL_CONSTANT(DEVICE_LINKER_AVAILABLE);
  JS_CL_CONSTANT(DEVICE_BUILT_IN_KERNELS);
  JS_CL_CONSTANT(DEVICE_IMAGE_MAX_BUFFER_SIZE);
  JS_CL_CONSTANT(DEVICE_IMAGE_MAX_ARRAY_SIZE);
  JS_CL_CONSTANT(DEVICE_PARENT_DEVICE);
  JS_CL_CONSTANT(DEVICE_PARTITION_MAX_SUB_DEVICES);
  JS_CL_CONSTANT(DEVICE_PARTITION_PROPERTIES);
  JS_CL_CONSTANT(DEVICE_PARTITION_AFFINITY_DOMAIN);
  JS_CL_CONSTANT(DEVICE_PARTITION_TYPE);
  JS_CL_CONSTANT(DEVICE_REFERENCE_COUNT);
  JS_CL_CONSTANT(DEVICE_PREFERRED_INTEROP_USER_SYNC);
  JS_CL_CONSTANT(DEVICE_PRINTF_BUFFER_SIZE);
#endif
#ifdef CL_VERSION_2_0
  JS_CL_CONSTANT(DEVICE_MAX_READ_WRITE_IMAGE_ARGS);
  JS_CL_CONSTANT(DEVICE_MAX_GLOBAL_VARIABLE_SIZE);
  JS_CL_CONSTANT(DEVICE_QUEUE_ON_DEVICE_PROPERTIES);
  JS_CL_CONSTANT(DEVICE_QUEUE_ON_DEVICE_PREFERRED_SIZE);
  JS_CL_CONSTANT(DEVICE_QUEUE_ON_DEVICE_MAX_SIZE);
  JS_CL_CONSTANT(DEVICE_MAX_ON_DEVICE_QUEUES);
  JS_CL_CONSTANT(DEVICE_MAX_ON_DEVICE_EVENTS);
  JS_CL_CONSTANT(DEVICE_SVM_CAPABILITIES);
  JS_CL_CONSTANT(DEVICE_GLOBAL_VARIABLE_PREFERRED_TOTAL_SIZE);
  JS_CL_CONSTANT(DEVICE_MAX_PIPE_ARGS);
  JS_CL_CONSTANT(DEVICE_PIPE_MAX_ACTIVE_RESERVATIONS);
  JS_CL_CONSTANT(DEVICE_PIPE_MAX_PACKET_SIZE);
  JS_CL_CONSTANT(DEVICE_PREFERRED_PLATFORM_ATOMIC_ALIGNMENT);
  JS_CL_CONSTANT(DEVICE_PREFERRED_GLOBAL_ATOMIC_ALIGNMENT);
  JS_CL_CONSTANT(DEVICE_PREFERRED_LOCAL_ATOMIC_ALIGNMENT);
#endif

  /* cl_device_fp_config - bitfield */
  JS_CL_CONSTANT(FP_DENORM);
  JS_CL_CONSTANT(FP_INF_NAN);
  JS_CL_CONSTANT(FP_ROUND_TO_NEAREST);
  JS_CL_CONSTANT(FP_ROUND_TO_ZERO);
  JS_CL_CONSTANT(FP_ROUND_TO_INF);
  JS_CL_CONSTANT(FP_FMA);
  JS_CL_CONSTANT(FP_SOFT_FLOAT);
#ifdef CL_VERSION_1_2
  JS_CL_CONSTANT(FP_CORRECTLY_ROUNDED_DIVIDE_SQRT);
#endif

  /* cl_device_mem_cache_type */
  JS_CL_CONSTANT(NONE);
  JS_CL_CONSTANT(READ_ONLY_CACHE);
  JS_CL_CONSTANT(READ_WRITE_CACHE);

  /* cl_device_local_mem_type */
  JS_CL_CONSTANT(LOCAL);
  JS_CL_CONSTANT(GLOBAL);

  /* cl_device_exec_capabilities - bitfield */
  JS_CL_CONSTANT(EXEC_KERNEL);
  JS_CL_CONSTANT(EXEC_NATIVE_KERNEL);

  /* cl_command_queue_properties - bitfield */
  JS_CL_CONSTANT(QUEUE_OUT_OF_ORDER_EXEC_MODE_ENABLE);
  JS_CL_CONSTANT(QUEUE_PROFILING_ENABLE);
#ifdef CL_VERSION_2_0
  JS_CL_CONSTANT(QUEUE_ON_DEVICE);
  JS_CL_CONSTANT(QUEUE_ON_DEVICE_DEFAULT);
#endif

  /* cl_context_info  */
  JS_CL_CONSTANT(CONTEXT_REFERENCE_COUNT);
  JS_CL_CONSTANT(CONTEXT_DEVICES);
  JS_CL_CONSTANT(CONTEXT_PROPERTIES);
  JS_CL_CONSTANT(CONTEXT_NUM_DEVICES);

  /* cl_context_info + cl_context_properties */
  JS_CL_CONSTANT(CONTEXT_PLATFORM);
#ifdef CL_VERSION_1_2
  JS_CL_CONSTANT(CONTEXT_INTEROP_USER_SYNC);
#endif

#ifdef CL_VERSION_1_2
  /* cl_device_partition_property */
  JS_CL_CONSTANT(DEVICE_PARTITION_EQUALLY);
  JS_CL_CONSTANT(DEVICE_PARTITION_BY_COUNTS);
  JS_CL_CONSTANT(DEVICE_PARTITION_BY_COUNTS_LIST_END);
  JS_CL_CONSTANT(DEVICE_PARTITION_BY_AFFINITY_DOMAIN);

  /* cl_device_affinity_domain */
  JS_CL_CONSTANT(DEVICE_AFFINITY_DOMAIN_NUMA);
  JS_CL_CONSTANT(DEVICE_AFFINITY_DOMAIN_L4_CACHE);
  JS_CL_CONSTANT(DEVICE_AFFINITY_DOMAIN_L3_CACHE);
  JS_CL_CONSTANT(DEVICE_AFFINITY_DOMAIN_L2_CACHE);
  JS_CL_CONSTANT(DEVICE_AFFINITY_DOMAIN_L1_CACHE);
  JS_CL_CONSTANT(DEVICE_AFFINITY_DOMAIN_NEXT_PARTITIONABLE);
#endif

#ifdef CL_VERSION_2_0
  /* cl_device_svm_capabilities */
  JS_CL_CONSTANT(DEVICE_SVM_COARSE_GRAIN_BUFFER);
  JS_CL_CONSTANT(DEVICE_SVM_FINE_GRAIN_BUFFER);
  JS_CL_CONSTANT(DEVICE_SVM_FINE_GRAIN_SYSTEM);
  JS_CL_CONSTANT(DEVICE_SVM_ATOMICS);
#endif

  /* cl_command_queue_info */
  JS_CL_CONSTANT(QUEUE_CONTEXT);
  JS_CL_CONSTANT(QUEUE_DEVICE);
  JS_CL_CONSTANT(QUEUE_REFERENCE_COUNT);
  JS_CL_CONSTANT(QUEUE_PROPERTIES);
#ifdef CL_VERSION_2_0
  JS_CL_CONSTANT(QUEUE_SIZE);
#endif

  /* cl_mem_flags - bitfield */
  JS_CL_CONSTANT(MEM_READ_WRITE);
  JS_CL_CONSTANT(MEM_WRITE_ONLY);
  JS_CL_CONSTANT(MEM_READ_ONLY);
  JS_CL_CONSTANT(MEM_USE_HOST_PTR);
  JS_CL_CONSTANT(MEM_ALLOC_HOST_PTR);
  JS_CL_CONSTANT(MEM_COPY_HOST_PTR);
#ifdef CL_VERSION_1_2
  JS_CL_CONSTANT(MEM_HOST_WRITE_ONLY);
  JS_CL_CONSTANT(MEM_HOST_READ_ONLY);
  JS_CL_CONSTANT(MEM_HOST_NO_ACCESS);
#endif
#ifdef CL_VERSION_2_0
  JS_CL_CONSTANT(MEM_SVM_FINE_GRAIN_BUFFER); /* used by cl_svm_mem_flags only */
  JS_CL_CONSTANT(MEM_SVM_ATOMICS); /* used by cl_svm_mem_flags only */
#endif

#ifdef CL_VERSION_1_2
  /* cl_mem_migration_flags - bitfield */
  JS_CL_CONSTANT(MIGRATE_MEM_OBJECT_HOST);
  JS_CL_CONSTANT(MIGRATE_MEM_OBJECT_CONTENT_UNDEFINED);
#endif

  /* cl_channel_order */
  JS_CL_CONSTANT(R);
  JS_CL_CONSTANT(A);
  JS_CL_CONSTANT(RG);
  JS_CL_CONSTANT(RA);
  JS_CL_CONSTANT(RGB);
  JS_CL_CONSTANT(RGBA);
  JS_CL_CONSTANT(BGRA);
  JS_CL_CONSTANT(ARGB);
  JS_CL_CONSTANT(INTENSITY);
  JS_CL_CONSTANT(LUMINANCE);
  JS_CL_CONSTANT(Rx);
  JS_CL_CONSTANT(RGx);
  JS_CL_CONSTANT(RGBx);
  JS_CL_CONSTANT(DEPTH);
  JS_CL_CONSTANT(DEPTH_STENCIL);
#ifdef CL_VERSION_2_0
  JS_CL_CONSTANT(sRGB);
  JS_CL_CONSTANT(sRGBx);
  JS_CL_CONSTANT(sRGBA);
  JS_CL_CONSTANT(sBGRA);
  JS_CL_CONSTANT(ABGR);
#endif

  /* cl_channel_type */
  JS_CL_CONSTANT(SNORM_INT8);
  JS_CL_CONSTANT(SNORM_INT16);
  JS_CL_CONSTANT(UNORM_INT8);
  JS_CL_CONSTANT(UNORM_INT16);
  JS_CL_CONSTANT(UNORM_SHORT_565);
  JS_CL_CONSTANT(UNORM_SHORT_555);
  JS_CL_CONSTANT(UNORM_INT_101010);
  JS_CL_CONSTANT(SIGNED_INT8);
  JS_CL_CONSTANT(SIGNED_INT16);
  JS_CL_CONSTANT(SIGNED_INT32);
  JS_CL_CONSTANT(UNSIGNED_INT8);
  JS_CL_CONSTANT(UNSIGNED_INT16);
  JS_CL_CONSTANT(UNSIGNED_INT32);
  JS_CL_CONSTANT(HALF_FLOAT);
  JS_CL_CONSTANT(FLOAT);

  /* cl_mem_object_type */
  JS_CL_CONSTANT(MEM_OBJECT_BUFFER);
  JS_CL_CONSTANT(MEM_OBJECT_IMAGE2D);
  JS_CL_CONSTANT(MEM_OBJECT_IMAGE3D);
#ifdef CL_VERSION_1_2
  JS_CL_CONSTANT(MEM_OBJECT_IMAGE2D_ARRAY);
  JS_CL_CONSTANT(MEM_OBJECT_IMAGE1D);
  JS_CL_CONSTANT(MEM_OBJECT_IMAGE1D_ARRAY);
  JS_CL_CONSTANT(MEM_OBJECT_IMAGE1D_BUFFER);
#endif
#ifdef CL_VERSION_2_0
  JS_CL_CONSTANT(MEM_OBJECT_PIPE);
#endif

  /* cl_mem_info */
  JS_CL_CONSTANT(MEM_TYPE);
  JS_CL_CONSTANT(MEM_FLAGS);
  JS_CL_CONSTANT(MEM_SIZE);
  JS_CL_CONSTANT(MEM_HOST_PTR);
  JS_CL_CONSTANT(MEM_MAP_COUNT);
  JS_CL_CONSTANT(MEM_REFERENCE_COUNT);
  JS_CL_CONSTANT(MEM_CONTEXT);
  JS_CL_CONSTANT(MEM_ASSOCIATED_MEMOBJECT);
  JS_CL_CONSTANT(MEM_OFFSET);
#ifdef CL_VERSION_2_0
  JS_CL_CONSTANT(MEM_USES_SVM_POINTER);
#endif

  /* cl_image_info */
  JS_CL_CONSTANT(IMAGE_FORMAT);
  JS_CL_CONSTANT(IMAGE_ELEMENT_SIZE);
  JS_CL_CONSTANT(IMAGE_ROW_PITCH);
  JS_CL_CONSTANT(IMAGE_SLICE_PITCH);
  JS_CL_CONSTANT(IMAGE_WIDTH);
  JS_CL_CONSTANT(IMAGE_HEIGHT);
  JS_CL_CONSTANT(IMAGE_DEPTH);
#ifdef CL_VERSION_1_2
  JS_CL_CONSTANT(IMAGE_ARRAY_SIZE);
  JS_CL_CONSTANT(IMAGE_BUFFER);
  JS_CL_CONSTANT(IMAGE_NUM_MIP_LEVELS);
  JS_CL_CONSTANT(IMAGE_NUM_SAMPLES);
#endif

#ifdef CL_VERSION_2_0
  /* cl_pipe_info */
  JS_CL_CONSTANT(PIPE_PACKET_SIZE);
  JS_CL_CONSTANT(PIPE_MAX_PACKETS);
#endif

  /* cl_addressing_mode */
  JS_CL_CONSTANT(ADDRESS_NONE);
  JS_CL_CONSTANT(ADDRESS_CLAMP_TO_EDGE);
  JS_CL_CONSTANT(ADDRESS_CLAMP);
  JS_CL_CONSTANT(ADDRESS_REPEAT);
  JS_CL_CONSTANT(ADDRESS_MIRRORED_REPEAT);

  /* cl_filter_mode */
  JS_CL_CONSTANT(FILTER_NEAREST);
  JS_CL_CONSTANT(FILTER_LINEAR);

  /* cl_sampler_info */
  JS_CL_CONSTANT(SAMPLER_REFERENCE_COUNT);
  JS_CL_CONSTANT(SAMPLER_CONTEXT);
  JS_CL_CONSTANT(SAMPLER_NORMALIZED_COORDS);
  JS_CL_CONSTANT(SAMPLER_ADDRESSING_MODE);
  JS_CL_CONSTANT(SAMPLER_FILTER_MODE);
#ifdef CL_VERSION_2_0
  JS_CL_CONSTANT(SAMPLER_MIP_FILTER_MODE);
  JS_CL_CONSTANT(SAMPLER_LOD_MIN);
  JS_CL_CONSTANT(SAMPLER_LOD_MAX);
#endif

  /* cl_map_flags - bitfield */
  JS_CL_CONSTANT(MAP_READ);
  JS_CL_CONSTANT(MAP_WRITE);
#ifdef CL_VERSION_1_2
  JS_CL_CONSTANT(MAP_WRITE_INVALIDATE_REGION);
#endif

  /* cl_program_info */
  JS_CL_CONSTANT(PROGRAM_REFERENCE_COUNT);
  JS_CL_CONSTANT(PROGRAM_CONTEXT);
  JS_CL_CONSTANT(PROGRAM_NUM_DEVICES);
  JS_CL_CONSTANT(PROGRAM_DEVICES);
  JS_CL_CONSTANT(PROGRAM_SOURCE);
  JS_CL_CONSTANT(PROGRAM_BINARY_SIZES);
  JS_CL_CONSTANT(PROGRAM_BINARIES);
#ifdef CL_VERSION_1_2
  JS_CL_CONSTANT(PROGRAM_NUM_KERNELS);
  JS_CL_CONSTANT(PROGRAM_KERNEL_NAMES);
#endif
#ifdef CL_VERSION_2_0
  JS_CL_CONSTANT(PROGRAM_BUILD_GLOBAL_VARIABLE_TOTAL_SIZE);
#endif

  /* cl_program_build_info */
  JS_CL_CONSTANT(PROGRAM_BUILD_STATUS);
  JS_CL_CONSTANT(PROGRAM_BUILD_OPTIONS);
  JS_CL_CONSTANT(PROGRAM_BUILD_LOG);
#ifdef CL_VERSION_1_2
  JS_CL_CONSTANT(PROGRAM_BINARY_TYPE);
#endif

#ifdef CL_VERSION_1_2
  /* cl_program_binary_type */
  JS_CL_CONSTANT(PROGRAM_BINARY_TYPE_NONE);
  JS_CL_CONSTANT(PROGRAM_BINARY_TYPE_COMPILED_OBJECT);
  JS_CL_CONSTANT(PROGRAM_BINARY_TYPE_LIBRARY);
  JS_CL_CONSTANT(PROGRAM_BINARY_TYPE_EXECUTABLE);
#endif

  /* cl_build_status */
  JS_CL_CONSTANT(BUILD_SUCCESS);
  JS_CL_CONSTANT(BUILD_NONE);
  JS_CL_CONSTANT(BUILD_ERROR);
  JS_CL_CONSTANT(BUILD_IN_PROGRESS);

  /* cl_kernel_info */
  JS_CL_CONSTANT(KERNEL_FUNCTION_NAME);
  JS_CL_CONSTANT(KERNEL_NUM_ARGS);
  JS_CL_CONSTANT(KERNEL_REFERENCE_COUNT);
  JS_CL_CONSTANT(KERNEL_CONTEXT);
  JS_CL_CONSTANT(KERNEL_PROGRAM);
#ifdef CL_VERSION_1_2
  JS_CL_CONSTANT(KERNEL_ATTRIBUTES);
#endif

#ifdef CL_VERSION_1_2
  /* cl_kernel_arg_info */
  JS_CL_CONSTANT(KERNEL_ARG_ADDRESS_QUALIFIER);
  JS_CL_CONSTANT(KERNEL_ARG_ACCESS_QUALIFIER);
  JS_CL_CONSTANT(KERNEL_ARG_TYPE_NAME);
  JS_CL_CONSTANT(KERNEL_ARG_TYPE_QUALIFIER);
  JS_CL_CONSTANT(KERNEL_ARG_NAME);

  /* cl_kernel_arg_address_qualifier */
  JS_CL_CONSTANT(KERNEL_ARG_ADDRESS_GLOBAL);
  JS_CL_CONSTANT(KERNEL_ARG_ADDRESS_LOCAL);
  JS_CL_CONSTANT(KERNEL_ARG_ADDRESS_CONSTANT);
  JS_CL_CONSTANT(KERNEL_ARG_ADDRESS_PRIVATE);

  /* cl_kernel_arg_access_qualifier */
  JS_CL_CONSTANT(KERNEL_ARG_ACCESS_READ_ONLY);
  JS_CL_CONSTANT(KERNEL_ARG_ACCESS_WRITE_ONLY);
  JS_CL_CONSTANT(KERNEL_ARG_ACCESS_READ_WRITE);
  JS_CL_CONSTANT(KERNEL_ARG_ACCESS_NONE);

  /* cl_kernel_arg_type_qualifer */
  JS_CL_CONSTANT(KERNEL_ARG_TYPE_NONE);
  JS_CL_CONSTANT(KERNEL_ARG_TYPE_CONST);
  JS_CL_CONSTANT(KERNEL_ARG_TYPE_RESTRICT);
  JS_CL_CONSTANT(KERNEL_ARG_TYPE_VOLATILE);
#endif
#ifdef CL_VERSION_2_0
  JS_CL_CONSTANT(KERNEL_ARG_TYPE_PIPE);
#endif

  /* cl_kernel_work_group_info */
  JS_CL_CONSTANT(KERNEL_WORK_GROUP_SIZE);
  JS_CL_CONSTANT(KERNEL_COMPILE_WORK_GROUP_SIZE);
  JS_CL_CONSTANT(KERNEL_LOCAL_MEM_SIZE);
  JS_CL_CONSTANT(KERNEL_PREFERRED_WORK_GROUP_SIZE_MULTIPLE);
  JS_CL_CONSTANT(KERNEL_PRIVATE_MEM_SIZE);
#ifdef CL_VERSION_1_2
  JS_CL_CONSTANT(KERNEL_GLOBAL_WORK_SIZE);
#endif

#ifdef CL_VERSION_2_0
  /* cl_kernel_exec_info */
  JS_CL_CONSTANT(KERNEL_EXEC_INFO_SVM_PTRS);
  JS_CL_CONSTANT(KERNEL_EXEC_INFO_SVM_FINE_GRAIN_SYSTEM);
#endif

  /* cl_event_info  */
  JS_CL_CONSTANT(EVENT_COMMAND_QUEUE);
  JS_CL_CONSTANT(EVENT_COMMAND_TYPE);
  JS_CL_CONSTANT(EVENT_REFERENCE_COUNT);
  JS_CL_CONSTANT(EVENT_COMMAND_EXECUTION_STATUS);
  JS_CL_CONSTANT(EVENT_CONTEXT);

  /* cl_command_type */
  JS_CL_CONSTANT(COMMAND_NDRANGE_KERNEL);
  JS_CL_CONSTANT(COMMAND_TASK);
  JS_CL_CONSTANT(COMMAND_NATIVE_KERNEL);
  JS_CL_CONSTANT(COMMAND_READ_BUFFER);
  JS_CL_CONSTANT(COMMAND_WRITE_BUFFER);
  JS_CL_CONSTANT(COMMAND_COPY_BUFFER);
  JS_CL_CONSTANT(COMMAND_READ_IMAGE);
  JS_CL_CONSTANT(COMMAND_WRITE_IMAGE);
  JS_CL_CONSTANT(COMMAND_COPY_IMAGE);
  JS_CL_CONSTANT(COMMAND_COPY_IMAGE_TO_BUFFER);
  JS_CL_CONSTANT(COMMAND_COPY_BUFFER_TO_IMAGE);
  JS_CL_CONSTANT(COMMAND_MAP_BUFFER);
  JS_CL_CONSTANT(COMMAND_MAP_IMAGE);
  JS_CL_CONSTANT(COMMAND_UNMAP_MEM_OBJECT);
  JS_CL_CONSTANT(COMMAND_MARKER);
  JS_CL_CONSTANT(COMMAND_ACQUIRE_GL_OBJECTS);
  JS_CL_CONSTANT(COMMAND_RELEASE_GL_OBJECTS);
  JS_CL_CONSTANT(COMMAND_READ_BUFFER_RECT);
  JS_CL_CONSTANT(COMMAND_WRITE_BUFFER_RECT);
  JS_CL_CONSTANT(COMMAND_COPY_BUFFER_RECT);
  JS_CL_CONSTANT(COMMAND_USER);
#ifdef CL_VERSION_1_2
  JS_CL_CONSTANT(COMMAND_BARRIER);
  JS_CL_CONSTANT(COMMAND_MIGRATE_MEM_OBJECTS);
  JS_CL_CONSTANT(COMMAND_FILL_BUFFER);
  JS_CL_CONSTANT(COMMAND_FILL_IMAGE);
#endif
#ifdef CL_VERSION_2_0
  JS_CL_CONSTANT(COMMAND_SVM_FREE);
  JS_CL_CONSTANT(COMMAND_SVM_MEMCPY);
  JS_CL_CONSTANT(COMMAND_SVM_MEMFILL);
  JS_CL_CONSTANT(COMMAND_SVM_MAP);
  JS_CL_CONSTANT(COMMAND_SVM_UNMAP);
#endif

  /* command execution status */
  JS_CL_CONSTANT(COMPLETE);
  JS_CL_CONSTANT(RUNNING);
  JS_CL_CONSTANT(SUBMITTED);
  JS_CL_CONSTANT(QUEUED);

  /* cl_buffer_create_type  */
  JS_CL_CONSTANT(BUFFER_CREATE_TYPE_REGION);

  /* cl_profiling_info  */
  JS_CL_CONSTANT(PROFILING_COMMAND_QUEUED);
  JS_CL_CONSTANT(PROFILING_COMMAND_SUBMIT);
  JS_CL_CONSTANT(PROFILING_COMMAND_START);
  JS_CL_CONSTANT(PROFILING_COMMAND_END);
#ifdef CL_VERSION_2_0
  JS_CL_CONSTANT(PROFILING_COMMAND_COMPLETE);
#endif

  /*
   * cl_ext.h
   */
  /* cl_khr_fp64 extension - no extension exports.since it has no functions  */
  JS_CL_CONSTANT(DEVICE_DOUBLE_FP_CONFIG);

  /* cl_khr_fp16 extension - no extension exports.since it has no functions  */
  JS_CL_CONSTANT(DEVICE_HALF_FP_CONFIG);

  /************************
  * cl_khr_icd extension *
  ************************/
#if !defined (__APPLE__) && !defined(MACOSX)
  /* cl_platform_info                                                        */
  JS_CL_CONSTANT(PLATFORM_ICD_SUFFIX_KHR);

  /* Additional Error Codes                                                  */
  JS_CL_CONSTANT(PLATFORM_NOT_FOUND_KHR);
#endif

  /******************************************
  * cl_nv_device_attribute_query extension *
  ******************************************/
#if !defined (__APPLE__) && !defined(MACOSX)
  /* cl_nv_device_attribute_query extension - no extension exports.since it has no functions */
  JS_CL_CONSTANT(DEVICE_COMPUTE_CAPABILITY_MAJOR_NV);
  JS_CL_CONSTANT(DEVICE_COMPUTE_CAPABILITY_MINOR_NV);
  JS_CL_CONSTANT(DEVICE_REGISTERS_PER_BLOCK_NV);
  JS_CL_CONSTANT(DEVICE_WARP_SIZE_NV);
  JS_CL_CONSTANT(DEVICE_GPU_OVERLAP_NV);
  JS_CL_CONSTANT(DEVICE_KERNEL_EXEC_TIMEOUT_NV);
  JS_CL_CONSTANT(DEVICE_INTEGRATED_MEMORY_NV);
#endif

  /*********************************
  * cl_amd_device_attribute_query *
  *********************************/
#if !defined (__APPLE__) && !defined(MACOSX)
  JS_CL_CONSTANT(DEVICE_PROFILING_TIMER_OFFSET_AMD);

  /* cl_device_partition_property_ext */
  JS_CL_CONSTANT(DEVICE_PARTITION_EQUALLY_EXT);
  JS_CL_CONSTANT(DEVICE_PARTITION_BY_COUNTS_EXT);
  JS_CL_CONSTANT(DEVICE_PARTITION_BY_NAMES_EXT);
  JS_CL_CONSTANT(DEVICE_PARTITION_BY_AFFINITY_DOMAIN_EXT);

  /* clDeviceGetInfo selectors */
  JS_CL_CONSTANT(DEVICE_PARENT_DEVICE_EXT);
  JS_CL_CONSTANT(DEVICE_PARTITION_TYPES_EXT);
  JS_CL_CONSTANT(DEVICE_AFFINITY_DOMAINS_EXT);
  JS_CL_CONSTANT(DEVICE_REFERENCE_COUNT_EXT);
  JS_CL_CONSTANT(DEVICE_PARTITION_STYLE_EXT);

  /* error codes */
  JS_CL_CONSTANT(DEVICE_PARTITION_FAILED_EXT);
  JS_CL_CONSTANT(INVALID_PARTITION_COUNT_EXT);
  JS_CL_CONSTANT(INVALID_PARTITION_NAME_EXT);

  /* CL_AFFINITY_DOMAINs */
  JS_CL_CONSTANT(AFFINITY_DOMAIN_L1_CACHE_EXT);
  JS_CL_CONSTANT(AFFINITY_DOMAIN_L2_CACHE_EXT);
  JS_CL_CONSTANT(AFFINITY_DOMAIN_L3_CACHE_EXT);
  JS_CL_CONSTANT(AFFINITY_DOMAIN_L4_CACHE_EXT);
  JS_CL_CONSTANT(AFFINITY_DOMAIN_NUMA_EXT);
  JS_CL_CONSTANT(AFFINITY_DOMAIN_NEXT_FISSIONABLE_EXT);

  /* cl_device_partition_property_ext list terminators */
  JS_CL_CONSTANT(PROPERTIES_LIST_END_EXT);
  JS_CL_CONSTANT(PARTITION_BY_COUNTS_LIST_END_EXT);
  exports->Set(JS_STR( "PARTITION_BY_NAMES_LIST_END_EXT" ), JS_NUM((double)CL_PARTITION_BY_NAMES_LIST_END_EXT));

  /*********************************
  * cl_amd_device_attribute_query *
  *********************************/
#endif

  /* cl_gl_object_type */
  JS_CL_CONSTANT(GL_OBJECT_BUFFER);
  JS_CL_CONSTANT(GL_OBJECT_TEXTURE2D);
  JS_CL_CONSTANT(GL_OBJECT_TEXTURE3D);
  JS_CL_CONSTANT(GL_OBJECT_RENDERBUFFER);

  /* cl_gl_texture_info */
  JS_CL_CONSTANT(GL_TEXTURE_TARGET);
  JS_CL_CONSTANT(GL_MIPMAP_LEVEL);

  /* Additional Error Codes  */
#if !defined (__APPLE__) && !defined(MACOSX)
  JS_CL_CONSTANT(INVALID_GL_SHAREGROUP_REFERENCE_KHR);

  /* cl_gl_context_info  */
  JS_CL_CONSTANT(CURRENT_DEVICE_FOR_GL_CONTEXT_KHR);
  JS_CL_CONSTANT(DEVICES_FOR_GL_CONTEXT_KHR);
#endif

  /* Additional cl_context_properties  */
  JS_CL_CONSTANT(GL_CONTEXT_KHR);
  JS_CL_CONSTANT(EGL_DISPLAY_KHR);
#if !defined (__APPLE__) && !defined(MACOSX)
  JS_CL_CONSTANT(GLX_DISPLAY_KHR);
  JS_CL_CONSTANT(WGL_HDC_KHR);
  JS_CL_CONSTANT(CGL_SHAREGROUP_KHR);
#endif

  /*
   *  cl_khr_gl_event  extension
   *  See section 9.9 in the OpenCL 1.1 spec for more information
   */
  JS_CL_CONSTANT(COMMAND_GL_FENCE_SYNC_OBJECT_KHR);
}

NODE_MODULE(opencl, init)
}
