#pragma once

/**************************************************************************************
Copyright 2021 Applied Research Associates, Inc.
Licensed under the Apache License, Version 2.0 (the "License"); you may not use
this file except in compliance with the License. You may obtain a copy of the License
at:
http://www.apache.org/licenses/LICENSE-2.0
Unless required by applicable law or agreed to in writing, software distributed under
the License is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR
CONDITIONS OF ANY KIND, either express or implied. See the License for the
specific language governing permissions and limitations under the License.
**************************************************************************************/

#include <biogears/io-exports.h>
    
#include <cstddef>
//!
//!  Functions for finding resource files that were part of the current biogears release
//!  These functions are encoded as part of libbiogears_io
//!
//!  Functions are exposed as either biogears::filesystem::path or char const *
//!  TODO: Migrate Biogears C++17 and replace biogears::filesystem with std::filesystem

namespace biogears {
namespace io {
  BIOGEARS_IO_API bool generate_states_directory(const char* file);
  BIOGEARS_IO_API bool does_embedded_states_file_exist(const char* file);

  BIOGEARS_IO_API char const* get_states_file_sha1(const char* file);

  BIOGEARS_IO_API char const** list_states_files();
  BIOGEARS_IO_API size_t states_file_count();

  BIOGEARS_IO_API char const* get_embedded_states_file(const char* file, size_t& content_size);

  BIOGEARS_IO_API char const* get_default_states_directory();
  BIOGEARS_IO_API size_t      get_embedded_states_file_size( const char *  file);
}
}