#pragma once

#include <ui/window.hh>
#include <memory>

namespace ui {

class container;
using container_ptr = std::shared_ptr<container>;

class container : public window {
public:
	using window::append_child;
};

} // namespace ui
