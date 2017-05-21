/***** GCL Generated File *********************/
/* Automatically generated file, do not edit! */
/**********************************************/

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <dispatch/dispatch.h>
#include <OpenCL/opencl.h>
#include <OpenCL/gcl_priv.h>
#include "mandelbrot.cl.h"

static void initBlocks(void);

// Initialize static data structures
static block_kernel_pair pair_map[1] = {
      { NULL, NULL }
};

static block_kernel_map bmap = { 0, 1, initBlocks, pair_map };

// Block function
void (^mandelbrot_kernel)(const cl_ndrange *ndrange, cl_int width, cl_double zoom_level, cl_int max_depth, cl_double* out) =
^(const cl_ndrange *ndrange, cl_int width, cl_double zoom_level, cl_int max_depth, cl_double* out) {
  int err = 0;
  cl_kernel k = bmap.map[0].kernel;
  if (!k) {
    initBlocks();
    k = bmap.map[0].kernel;
  }
  if (!k)
    gcl_log_fatal("kernel mandelbrot does not exist for device");
  kargs_struct kargs;
  gclCreateArgsAPPLE(k, &kargs);
  err |= gclSetKernelArgAPPLE(k, 0, sizeof(width), &width, &kargs);
  err |= gclSetKernelArgAPPLE(k, 1, sizeof(zoom_level), &zoom_level, &kargs);
  err |= gclSetKernelArgAPPLE(k, 2, sizeof(max_depth), &max_depth, &kargs);
  err |= gclSetKernelArgMemAPPLE(k, 3, out, &kargs);
  gcl_log_cl_fatal(err, "setting argument for mandelbrot failed");
  err = gclExecKernelAPPLE(k, ndrange, &kargs);
  gcl_log_cl_fatal(err, "Executing mandelbrot failed");
  gclDeleteArgsAPPLE(k, &kargs);
};

// Initialization functions
static void initBlocks(void) {
  const char* build_opts = " -cl-auto-vectorize-disable";
  static dispatch_once_t once;
  dispatch_once(&once,
    ^{ int err = gclBuildProgramBinaryAPPLE("mandelbrot.cl", "", &bmap, build_opts);
       if (!err) {
          assert(bmap.map[0].block_ptr == mandelbrot_kernel && "mismatch block");
          bmap.map[0].kernel = clCreateKernel(bmap.program, "mandelbrot", &err);
       }
     });
}

__attribute__((constructor))
static void RegisterMap(void) {
  gclRegisterBlockKernelMap(&bmap);
  bmap.map[0].block_ptr = mandelbrot_kernel;
}

