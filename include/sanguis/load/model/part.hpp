#ifndef SANGUIS_LOAD_MODEL_PART_HPP_INCLUDED
#define SANGUIS_LOAD_MODEL_PART_HPP_INCLUDED

#include <sanguis/optional_primary_weapon_type_fwd.hpp>
#include <sanguis/load/model/global_parameters_fwd.hpp>
#include <sanguis/load/model/part_fwd.hpp>
#include <sanguis/load/model/weapon_category_fwd.hpp>
#include <sanguis/load/model/weapon_category_map.hpp>
#include <sanguis/model/part_fwd.hpp>
#include <fcppt/noncopyable.hpp>


namespace sanguis
{
namespace load
{
namespace model
{

class part
{
	FCPPT_NONCOPYABLE(
		part
	);
public:
	part(
		sanguis::model::part const &,
		sanguis::load::model::global_parameters const &
	);

	~part();

	sanguis::load::model::weapon_category const &
	operator[](
		sanguis::optional_primary_weapon_type
	) const;
private:
	sanguis::load::model::weapon_category_map const categories_;
};

}
}
}

#endif
