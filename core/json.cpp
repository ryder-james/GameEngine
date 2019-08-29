#include "json.h"

#include <iostream>

#include "filesystem.h"

bool json::load(const char* filename, rapidjson::Document& document) {
	bool success = false;

	char* buffer;
	size_t size;

	if (filesystem::read_file(filename, (void**)& buffer, size)) {
		buffer[size - 1] = 0;
		document.Parse(buffer);
		success = document.IsObject();

		filesystem::free_file(buffer);
	}

	return success;
}

bool json::get(const rapidjson::Value& value, const char* property_name, int& _int) {
	auto iter = value.FindMember(property_name);

	if (iter == value.MemberEnd()) {
		return false;
	}

	auto& property = iter->value;
	if (!property.IsInt()) {
		return false;
	}

	_int = property.GetInt();

	return true;
}

bool json::get(const rapidjson::Value& value, const char* property_name, uint& _int) {
	auto iter = value.FindMember(property_name);

	if (iter == value.MemberEnd()) {
		return false;
	}

	auto& property = iter->value;
	if (!property.IsUint()) {
		return false;
	}

	_int = property.GetUint();

	return true;
}

bool json::get(const rapidjson::Value& value, const char* property_name, float& _float) {
	auto iter = value.FindMember(property_name);

	if (iter == value.MemberEnd()) {
		return false;
	}

	auto& property = iter->value;
	if (!property.IsFloat()) {
		return false;
	}

	_float = property.GetFloat();

	return true;
}

bool json::get(const rapidjson::Value& value, const char* property_name, std::string& _string) {
	auto iter = value.FindMember(property_name);

	if (iter == value.MemberEnd()) {
		return false;
	}

	auto& property = iter->value;
	if (!property.IsString()) {
		return false;
	}

	_string = property.GetString();

	return true;
}

bool json::get(const rapidjson::Value& value, const char* property_name, Name& _name) {
	auto iter = value.FindMember(property_name);

	if (iter == value.MemberEnd()) {
		return false;
	}

	auto& property = iter->value;
	if (!property.IsString()) {
		return false;
	}

	_name = property.GetString();

	return true;
}

bool json::get(const rapidjson::Value& value, const char* property_name, bool& _bool) {
	auto iter = value.FindMember(property_name);

	if (iter == value.MemberEnd()) {
		return false;
	}

	auto& property = iter->value;
	if (!property.IsBool()) {
		return false;
	}

	_bool = property.GetBool();

	return true;
}

bool json::get(const rapidjson::Value& value, const char* property_name, std::vector<vector2>& _vector) {
	bool success = false;

	for (rapidjson::SizeType i = 0; i < value.Size(); i++) {
		const rapidjson::Value& vertex = value[i];
		if (vertex.IsObject()) {
			vector2 v2;
			success = get(vertex, property_name, v2);
			if (!success) break;
			_vector.push_back(v2);
		}
	}

	return success;
}

bool json::get(const rapidjson::Value& value, const char* property_name, vector2& _vector2) {
	auto iter = value.FindMember(property_name);

	if (iter == value.MemberEnd()) {
		return false;
	}

	auto& property = iter->value;
	if (!property.IsArray() || property.Size() != 2) {
		return false;
	}

	for (rapidjson::SizeType i = 0; i < 2; i++) {
		if (!property[i].IsDouble()) {
			return false;
		}
	}

	_vector2.x = property[0].GetFloat();
	_vector2.y = property[1].GetFloat();

	return true;
}

bool json::get(const rapidjson::Value& value, const char* property_name, color& _color) {
	auto iter = value.FindMember(property_name);

	if (iter == value.MemberEnd()) {
		return false;
	}

	auto& property = iter->value;
	if (!property.IsArray() || property.Size() != 3) {
		return false;
	}

	for (rapidjson::SizeType i = 0; i < 3; i++) {
		if (!property[i].IsDouble()) {
			return false;
		}
	}

	_color.r = property[0].GetFloat();
	_color.g = property[1].GetFloat();
	_color.b = property[2].GetFloat();

	return true;
}

bool json::get(const rapidjson::Value& value, const char* property_name, std::vector<color>& _colors) {
	bool success = false;

	for (rapidjson::SizeType i = 0; i < value.Size(); i++) {
		const rapidjson::Value& color_value = value[i];
		if (color_value.IsObject()) {
			color c;
			success = get(color_value, property_name, c);
			if (!success) break;
			_colors.push_back(c);
		}
	}

	return success;
}
