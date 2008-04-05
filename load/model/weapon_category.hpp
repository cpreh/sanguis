#ifndef SANGUIS_LOAD_MODEL_WEAPON_CATEGORY_HPP_INCLUDED
#define SANGUIS_LOAD_MODEL_WEAPON_CATEGORY_HPP_INCLUDED

#include "animation.hpp"
#include "../../animation_type.hpp"
#include <sge/path.hpp>
#include <map>

namespace sanguis
{
namespace load
{
namespace model
{

class weapon_category {
public:
	weapon_category(sge::path const&);
	animation const& none() const;
	animation const& attacking() const;
	animation const& walking() const;
	animation const& dying() const;
private:
	typedef std::map<animation_type::type, animation> animation_map;
	animation_map animations;
};

}
}
}

#endif
