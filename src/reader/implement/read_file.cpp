#include <fstream>
#include <string>
#include <sstream>

#include "read_file.hpp"
#include "exceptions/fserrs.hpp"

std::pair<file_input_device*, string_char_stream*> read_file(std::wstring filepath, codec_type Codec_type) {

	std::ifstream file(encode(filepath), std::ios::in);
	std::stringstream buffer;
	buffer << file.rdbuf();
	file.close();
	std::wstring content = decode(buffer.str(), Codec_type);
	return { new file_input_device { filepath, content }, new string_char_stream(content) };
}

// std::wstring get_content(std::wstring filepath) {
// 	return content_map[filepath];
// }