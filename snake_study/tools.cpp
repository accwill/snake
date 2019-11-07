#include "tools.h"

// 这里为什么不能加const
bool findForVector(std::vector<MapPointer>& arr, MapPointer& mp) {
	for (auto mp1 : arr) {
		if (mp1 == mp) {
			return true;
		}
	}
	return false;
}
