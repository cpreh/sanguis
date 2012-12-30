#ifndef SANGUIS_LOAD_MODEL_WEAPON_CATEGORY_HPP_INCLUDED
#define SANGUIS_LOAD_MODEL_WEAPON_CATEGORY_HPP_INCLUDED

#include <sanguis/animation_type_fwd.hpp>
#include <sanguis/load/model/weapon_category_fwd.hpp>
#include <sanguis/load/model/global_parameters_fwd.hpp>
#include <sanguis/load/model/animation/object_fwd.hpp>
#include <sanguis/load/resource/context_fwd.hpp>
#include <sge/parse/json/object_fwd.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/ptr_container/ptr_map.hpp>
#include <fcppt/config/external_end.hpp>

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
	animation::object const &
	operator[](
		sanguis::animation_type
	) const;

	bool
	has_animation(
		sanguis::animation_type
	) const;

	~weapon_category();

	weapon_category(
		sge::parse::json::object const &,
		model::global_parameters const &
	);
private:
	typedef boost::ptr_map<
		sanguis::animation_type,
		animation::object
	> animation_map;

	animation_map animations_;
};

}
}
}

#endif
