#pragma once

namespace filesystem {
	bool file_exists(const char* filename);
	bool file_size(const char* filename, size_t& size);

	bool read_file(const char* filename, void** buffer, size_t& size);
	bool write_file(const char* filename, void* buffer, size_t size);

	void free_file(void* buffer);
	bool delete_file(const char* filename);
	bool copy_file(const char* source, const char* destination, bool overwrite);

	bool directory_exists(const char* directory);
	bool copy_directory(const char* source, const char* destination, bool recursive = true);
	bool create_directory(const char* directory);
	bool delete_directory(const char* directory);
	bool delete_empty_directory(const char* directory);

	void set_current_path(const char* pathname);
	void get_current_path(char* pathname, size_t size);
}