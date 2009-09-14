#ifndef SANGUIS_LOAD_MODEL_WEAPON_CATEGORY_HPP_INCLUDED
#define SANGUIS_LOAD_MODEL_WEAPON_CATEGORY_HPP_INCLUDED

#include "../resource/context_fwd.hpp"
#include "animation.hpp"
#include "global_parameters_fwd.hpp"
#include "../../animation_type.hpp"
#include "../../animation_state.hpp"
#include <sge/parse/json/object_fwd.hpp>
#include <map>

namespace sanguis
{
namespace load
{
namespace model
{

class weapon_category {
public:
	animation const &
	operator[](
		animation_type::type) const;
	animation_state::type state(
		animation_type::type) const;
private:
	explicit weapon_category(
		sge::parse::json::object const &,
		global_parameters const &);
	
	friend class part;

	typedef std::map<
		animation_type::type,
		animation
	> animation_map;

	animation_map animations;
};

}
}
}

#endif
