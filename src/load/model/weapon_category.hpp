#ifndef SANGUIS_LOAD_MODEL_WEAPON_CATEGORY_HPP_INCLUDED
#define SANGUIS_LOAD_MODEL_WEAPON_CATEGORY_HPP_INCLUDED

#include "weapon_category_fwd.hpp"
#include "animation_fwd.hpp"
#include "global_parameters_fwd.hpp"
#include "../resource/context_fwd.hpp"
#include "../../animation_type.hpp"
#include <sge/parse/json/object_fwd.hpp>
#include <fcppt/noncopyable.hpp>
#include <boost/ptr_container/ptr_map.hpp>

namespace sanguis
{
namespace load
{
namespace model
{

class weapon_category
{
	FCPPT_NONCOPYABLE(
		weapon_category
	);
public:
	animation const &
	operator[](
		animation_type::type
	) const;

	bool
	has_animation(
		animation_type::type
	) const;

	~weapon_category();

	explicit weapon_category(
		sge::parse::json::object const &,
		global_parameters const &
	);
private:
	typedef boost::ptr_map<
		animation_type::type,
		animation
	> animation_map;

	animation_map animations;
};

}
}
}

#endif
