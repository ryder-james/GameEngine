#include "transform.h"

bool transform::Load(const rapidjson::Value& value) {
	bool success;

	success = json::get(value, "position", translation);
	success = json::get(value, "rotation", rotation);
	success = json::get(value, "scale", scale);

	return success;
}

bool transform::Update() {
	matrix33 mxs;
	mxs.scale(scale);

	matrix33 mxr;
	mxr.rotate(rotation);

	matrix33 mxt;
	mxt.translate(translation);

	mxWorld = mxs * mxr * mxt;

	return true;
}

void transform::Update(const transform& parent, const transform& local) {
	scale = parent.scale * local.scale;
	rotation = parent.rotation + local.rotation;
	translation = parent.translation + vector2::rotate(local.translation, rotation);
}
