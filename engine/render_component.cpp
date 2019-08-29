#include "render_component.h"

bool RenderComponent::Load(const rapidjson::Value& value) {
	json::get(value, "z", z);
	
	return true;
}
