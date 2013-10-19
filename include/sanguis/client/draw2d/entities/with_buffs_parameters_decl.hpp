#ifndef SANGUIS_CLIENT_DRAW2D_ENTITIES_WITH_BUFFS_PARAMETERS_DECL_HPP_INCLUDED
#define SANGUIS_CLIENT_DRAW2D_ENTITIES_WITH_BUFFS_PARAMETERS_DECL_HPP_INCLUDED

#include <sanguis/buff_type_vector.hpp>
#include <fcppt/nonassignable.hpp>


namespace sanguis
{
namespace client
{
namespace draw2d
{
namespace entities
{

template<
	typename Base
>
class with_buffs_parameters
{
	FCPPT_NONASSIGNABLE(
		with_buffs_parameters
	);
public:
	with_buffs_parameters(
		sanguis::buff_type_vector const &,
		Base const &
	);

	sanguis::buff_type_vector const &
	buffs() const;

	Base const &
	base() const;
private:
	sanguis::buff_type_vector const buffs_;

	Base const base_;
};

}
}
}
}

#endif
