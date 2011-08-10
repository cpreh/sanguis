#ifndef SANGUIS_LOAD_MODEL_BASE_ANIMATION_NOT_FOUND_HPP_INCLUDED
#define SANGUIS_LOAD_MODEL_BASE_ANIMATION_NOT_FOUND_HPP_INCLUDED

#include "../../animation_type.hpp"
#include "../../exception.hpp"

namespace sanguis
{
namespace load
{
namespace model
{

class base_animation_not_found : public exception {
public:
	base_animation_not_found(
		animation_type::type);

	animation_type::type anim_type() const;
private:
	animation_type::type anim_type_;
};

}
}
}

#endif
