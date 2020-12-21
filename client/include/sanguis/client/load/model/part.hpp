#ifndef SANGUIS_CLIENT_LOAD_MODEL_PART_HPP_INCLUDED
#define SANGUIS_CLIENT_LOAD_MODEL_PART_HPP_INCLUDED

#include <sanguis/optional_primary_weapon_type_fwd.hpp>
#include <sanguis/client/load/model/global_parameters_fwd.hpp>
#include <sanguis/client/load/model/part_fwd.hpp>
#include <sanguis/client/load/model/weapon_category_fwd.hpp>
#include <sanguis/client/load/model/weapon_category_map.hpp>
#include <sanguis/model/part_fwd.hpp>
#include <fcppt/nonmovable.hpp>
#include <fcppt/log/object_fwd.hpp>


namespace sanguis
{
namespace client
{
namespace load
{
namespace model
{

class part
{
	FCPPT_NONMOVABLE(
		part
	);
public:
	part(
		fcppt::log::object &, // NOLINT(google-runtime-references)
		sanguis::model::part const &,
		sanguis::client::load::model::global_parameters const &
	);

	~part();

	[[nodiscard]]
	sanguis::client::load::model::weapon_category const &
	operator[](
		sanguis::optional_primary_weapon_type
	) const;
private:
	sanguis::client::load::model::weapon_category_map const categories_;
};

}
}
}
}

#endif
