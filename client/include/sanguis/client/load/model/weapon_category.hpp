#ifndef SANGUIS_CLIENT_LOAD_MODEL_WEAPON_CATEGORY_HPP_INCLUDED
#define SANGUIS_CLIENT_LOAD_MODEL_WEAPON_CATEGORY_HPP_INCLUDED

#include <sanguis/client/load/animation_type_fwd.hpp>
#include <sanguis/client/load/model/animation_fwd.hpp>
#include <sanguis/client/load/model/animation_map.hpp>
#include <sanguis/client/load/model/global_parameters_fwd.hpp>
#include <sanguis/client/load/model/weapon_category_fwd.hpp>
#include <sanguis/model/weapon_category_fwd.hpp>
#include <fcppt/noncopyable.hpp>


namespace sanguis
{
namespace client
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
	weapon_category(
		sanguis::model::weapon_category const &,
		sanguis::client::load::model::global_parameters const &
	);

	~weapon_category();

	sanguis::client::load::model::animation const &
	operator[](
		sanguis::client::load::animation_type
	) const;

	bool
	has_animation(
		sanguis::client::load::animation_type
	) const;
private:
	sanguis::client::load::model::animation_map const animations_;
};

}
}
}
}

#endif
