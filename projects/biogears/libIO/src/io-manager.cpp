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
#include <biogears/filesystem/path.h>

#include <biogears/io/directories/config.h>
#include <biogears/io/directories/ecg.h>
#include <biogears/io/directories/environments.h>
#include <biogears/io/directories/nutrition.h>
#include <biogears/io/directories/override.h>
#include <biogears/io/directories/patients.h>
#include <biogears/io/directories/xsd.h>
#include <biogears/io/io-manager.h>

#ifdef IO_EMBED_STATES
#include <biogears/io/directories/states.h>
#endif

#include <biogears/io/directories/substances.h>

#include <biogears/io/utils.h>

namespace biogears {
namespace io {
  //!
  //!  Writes the contents to the embded runtime_directory to disk
  //!
  //!  //TODO: Optional overwrite protection
  //!  //TODO: Optional temporary directory construction to prevent partial write
  //!  //TODO: Optional empty dir check with cleanup

  bool IOManager::generate_runtime_directory(const char* file)
  {
    biogears::filesystem::create_directories(file);

    biogears::filesystem::path runtime_directory { file };

    bool result = generate_xsd_directory(runtime_directory / "xsd");
    result &= generate_config_directory(runtime_directory / "config");
    result &= generate_ecg_directory(runtime_directory / "directory");
    result &= generate_environments_directory(runtime_directory / "environments");
    result &= generate_nutrition_directory(runtime_directory / "nutrition");
    result &= generate_override_directory(runtime_directory / "override");
    result &= generate_patients_directory(runtime_directory / "patients");
#ifdef IO_EMBED_STATES
    result &= generate_states_directory(runtime_directory / "states");
#endif
    result &= generate_substances_directory(runtime_directory / "substances");

    return result;
  }
  //---------------------------------------------------------------------------
  bool IOManager::does_embedded_file_exist(const char* file)
  {

    biogears::filesystem::path embeded_path { file };

    return does_embedded_xsd_file_exist(embeded_path)
      || does_embedded_config_file_exist(embeded_path)
      || does_embedded_ecg_file_exist(embeded_path)
      || does_embedded_environments_file_exist(embeded_path)
      || does_embedded_nutrition_file_exist(embeded_path)
      || does_embedded_override_file_exist(embeded_path)
      || does_embedded_patients_file_exist(embeded_path)
#ifdef IO_EMBED_STATES
      || does_embedded_states_file_exist(embeded_path)
#endif
      || does_embedded_substances_file_exist(embeded_path);
  }
  //---------------------------------------------------------------------------
  size_t IOManager::find_resource_file(char const* file, char* buffer, size_t buffer_size)
  {

    size_t bytes_written = 0;
    if (bytes_written = find_xsd_file(file, _biogears_schema_root, buffer, buffer_size)) {
      return bytes_written;
    }

    if (bytes_written = find_config_file(file, _biogears_data_root, buffer, buffer_size)) {
      return bytes_written;
    }

    if (bytes_written = find_ecg_file(file, _biogears_data_root, buffer, buffer_size)) {
      return bytes_written;
    }

    if (bytes_written = find_environment_file(file, _biogears_data_root, buffer, buffer_size)) {
      return bytes_written;
    }

    if (bytes_written = find_nutrition_file(file, _biogears_data_root, buffer, buffer_size)) {
      return bytes_written;
    }

    if (bytes_written = find_override_file(file, _biogears_data_root, buffer, buffer_size)) {
      return bytes_written;
    }

    if (bytes_written = find_patients_file(file, _biogears_data_root, buffer, buffer_size)) {
      return bytes_written;
    }
#ifdef IO_EMBED_STATES
    if (bytes_written = find_states_file(file, _biogears_data_root, buffer, buffer_size)) {
      return bytes_written;
    }
#endif
    if (bytes_written = find_substances_file(file, _biogears_data_root, buffer, buffer_size)) {
      return bytes_written;
    }
    return 0;
  }
  //---------------------------------------------------------------------------
  char const* IOManager::get_expected_sha1(const char* file)
  {
    char const* result = nullptr;
    result = get_xsd_file_sha1(file);
    if (*result) {
      return result;
    }
    result = get_config_file_sha1(file);
    if (*result) {
      return result;
    }
    result = get_ecg_file_sha1(file);
    if (*result) {
      return result;
    }
    result = get_environments_file_sha1(file);
    if (*result) {
      return result;
    }
    result = get_nutrition_file_sha1(file);
    if (*result) {
      return result;
    }
    result = get_override_file_sha1(file);
    if (*result) {
      return result;
    }
    result = get_patients_file_sha1(file);
    if (*result) {
      return result;
    }
#ifdef IO_EMBED_STATES
    result = get_states_file_sha1(file);
    if (*result) {
      return result;
    }
#endif
    result = get_substances_file_sha1(file);
    if (*result) {
      return result;
    }

    return "";
  }
  //---------------------------------------------------------------------------
  std::string IOManager::calculate_sha1(const char* path)
  {
    return generate_file_sha1(path);
  }
  //---------------------------------------------------------------------------
  std::string IOManager::calculate_sha1(const char* buffer, size_t buffer_size)
  {
    return generate_sha1(buffer, buffer_size);
  }
  //---------------------------------------------------------------------------
  //!
  //!  This function does not provide fall back mechanics. This is intentional
  //!  It should be used to compare two file locations exsactly
  bool IOManager::validate_file(const char* path, const char* embeded_path)
  {
    if (embeded_path) {
      std::string embeded_hash = get_expected_sha1(embeded_path);
      std::string file_hash = calculate_sha1(path);

      return embeded_hash == file_hash;
    } else {
      if (does_embedded_file_exist(path)) {
        std::string embeded_hash = get_expected_sha1(path);
        std::string file_hash = calculate_sha1(path);

        return embeded_hash == file_hash;
      }
      return false;
    }
  }
  //---------------------------------------------------------------------------
  char const* IOManager::get_embedded_resource_file(const char* file)
  {
    char const* result = nullptr;
    if (result = get_embedded_xsd_file(file)) {
      return result;
    }

    if (result = get_embedded_config_file(file)) {
      return result;
    }

    if (result = get_embedded_ecg_file(file)) {
      return result;
    }

    if (result = get_embedded_environments_file(file)) {
      return result;
    }

    if (result = get_embedded_nutrition_file(file)) {
      return result;
    }

    if (result = get_embedded_override_file(file)) {
      return result;
    }

    if (result = get_embedded_patients_file(file)) {
      return result;
    }
#ifdef IO_EMBED_STATES
    if (result = get_embedded_states_file(file)) {
      return result;
    }
#endif
    if (result = get_embedded_substances_file(file)) {
      return result;
    }
    return nullptr;
  }

  size_t IOManager::get_directory_count()
  {
	size_t sum = biogears::io::config_file_count() 
		+ biogears::io::ecg_file_count()
		+ biogears::io::environments_file_count()
        + biogears::io::nutrition_file_count()
        + biogears::io::override_file_count()
	    + biogears::io::patients_file_count()
        + biogears::io::substances_file_count()
        + biogears::io::xsd_file_count();
#ifdef IO_EMBED_STATES 
	sum += states_file_count();
#endif
	return sum;
  }

  char const** IOManager::get_directory_list() 
  {
	std::vector<char const* const*> directory_lists;
    directory_lists.push_back(biogears::io::list_config_files());
	directory_lists.push_back(biogears::io::list_ecg_files());
    directory_lists.push_back(biogears::io::list_environments_files());
	directory_lists.push_back(biogears::io::list_nutrition_files());
    directory_lists.push_back(biogears::io::list_override_files());
	directory_lists.push_back(biogears::io::list_patients_files());
    directory_lists.push_back(biogears::io::list_substances_files());
    directory_lists.push_back(biogears::io::list_xsd_files());
#ifdef IO_EMBED_STATES
	directory_lists.push_back(biogears::io::list_states_files());
#endif
	std::vector<const char*> fileList;
	for (int i = 0;i < directory_lists.size();++i) {
		for (int k = 0;directory_lists[i][k] != '\0';++k) {
			fileList.push_back(directory_lists[i][k]);
		}
	}
	const char ** result = fileList.data();
	return result;
  }
}
}