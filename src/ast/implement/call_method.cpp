#include "call_method.hpp"

model_object* call_method(model_object* obj, std::wstring name, std::vector<model_object*> arglist) {
	if (auto method = dynamic_cast<model_method*> (obj->get_member(name)); method != NULL) {
		return method->call(obj, arglist);
	}
	else {
		throw "not method";
	}
}