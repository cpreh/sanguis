#ifndef SANGUIS_CLIENT_LOAD_MODEL_BASE_ANIMATION_NOT_FOUND_HPP_INCLUDED
#define SANGUIS_CLIENT_LOAD_MODEL_BASE_ANIMATION_NOT_FOUND_HPP_INCLUDED

#include <sanguis/exception.hpp>
#include <sanguis/client/load/animation_type.hpp>


namespace sanguis
{
namespace client
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
		sanguis::client::load::animation_type
	);

	sanguis::client::load::animation_type
	anim_type() const;
private:
	sanguis::client::load::animation_type anim_type_;
};

}
}
}
}

#endif
