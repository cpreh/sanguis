#ifndef SANGUIS_LOAD_MODEL_BASE_ANIMATION_NOT_FOUND_HPP_INCLUDED
#define SANGUIS_LOAD_MODEL_BASE_ANIMATION_NOT_FOUND_HPP_INCLUDED

#include <sanguis/exception.hpp>
#include <sanguis/load/animation_type.hpp>


namespace sanguis
{
namespace load
{
namespace model
{

class base_animation_not_found
:
	public sanguis::exception
{
public:
	explicit
	base_animation_not_found(
		sanguis::load::animation_type
	);

	sanguis::load::animation_type
	anim_type() const;
private:
	sanguis::load::animation_type anim_type_;
};

}
}
}

#endif
