/*
 * Copyright (c) 2024 The drmpp Contributors
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef INCLUDE_DRMPP_SHARED_LIBS_LIBGBM_H
#define INCLUDE_DRMPP_SHARED_LIBS_LIBGBM_H

#include "third_party/gbm/include/gbm.h"

struct LibGbmExports {
  LibGbmExports() = default;
  explicit LibGbmExports(void* lib);

  typedef gbm_bo* (*BoCreateFnPtr)(gbm_device* gbm,
                                   uint32_t width,
                                   uint32_t height,
                                   uint32_t format,
                                   uint32_t flags);
  typedef void (*BoDestroyFnPtr)(gbm_bo* bo);
  typedef gbm_bo* (*BoCreateWithModifiers2FnPtr)(gbm_device* gbm,
                                                 uint32_t width,
                                                 uint32_t height,
                                                 uint32_t format,
                                                 const uint64_t* modifiers,
                                                 unsigned int count,
                                                 uint32_t flags);
  typedef void* (*BoMapFnPtr)(gbm_bo* bo,
                              uint32_t x,
                              uint32_t y,
                              uint32_t width,
                              uint32_t height,
                              uint32_t flags,
                              uint32_t* stride,
                              void** map_data);
  typedef void (*BoUnmapFnPtr)(gbm_bo* bo, void* map_data);
  typedef gbm_bo_handle (*BoGetHandleForPlaneFnPtr)(gbm_bo* bo, int plane);
  typedef int (*BoGetPlaneCountFnPtr)(gbm_bo* bo);
  typedef uint32_t (*BoGetOffsetFnPtr)(gbm_bo* bo, int plane);
  typedef uint32_t (*BoGetStrideForPlaneFnPtr)(gbm_bo* bo, int plane);
  typedef uint32_t (*BoGetWidthFnPtr)(gbm_bo* bo);
  typedef uint32_t (*BoGetHeightFnPtr)(gbm_bo* bo);
  typedef uint32_t (*BoGetFormatFnPtr)(gbm_bo* bo);
  typedef uint64_t (*BoGetModifierFnPtr)(gbm_bo* bo);

  BoCreateFnPtr bo_create = nullptr;
  BoDestroyFnPtr bo_destroy = nullptr;
  BoCreateWithModifiers2FnPtr bo_create_with_modifiers2 = nullptr;
  BoMapFnPtr bo_map = nullptr;
  BoUnmapFnPtr bo_unmap = nullptr;
  BoGetHandleForPlaneFnPtr bo_get_handle_for_plane = nullptr;
  BoGetPlaneCountFnPtr bo_get_plane_count = nullptr;
  BoGetOffsetFnPtr bo_get_offset = nullptr;
  BoGetStrideForPlaneFnPtr bo_get_stride_for_plane = nullptr;
  BoGetWidthFnPtr bo_get_width = nullptr;
  BoGetHeightFnPtr bo_get_height = nullptr;
  BoGetFormatFnPtr bo_get_format = nullptr;
  BoGetModifierFnPtr bo_get_modifier = nullptr;
};

class LibGbm {
 public:
  static bool IsPresent(const char* library_path = nullptr) {
    return loadExports(library_path) != nullptr;
  }

  LibGbmExports* operator->() const;

 private:
  static LibGbmExports* loadExports(const char* library_path);
};

extern LibGbm LibGbm;

#endif  // INCLUDE_DRMPP_SHARED_LIBS_LIBGBM_H