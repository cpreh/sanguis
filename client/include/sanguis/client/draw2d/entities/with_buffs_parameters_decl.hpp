#ifndef SANGUIS_CLIENT_DRAW2D_ENTITIES_WITH_BUFFS_PARAMETERS_DECL_HPP_INCLUDED
#define SANGUIS_CLIENT_DRAW2D_ENTITIES_WITH_BUFFS_PARAMETERS_DECL_HPP_INCLUDED

#include <sanguis/buff_type_vector.hpp>
#include <sanguis/diff_clock_fwd.hpp>
#include <sanguis/client/draw2d/sprite/normal/system_fwd.hpp>
#include <sanguis/client/load/model/collection_fwd.hpp>
#include <fcppt/reference_impl.hpp>


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
public:
	with_buffs_parameters(
		sanguis::diff_clock const &,
		sanguis::client::draw2d::sprite::normal::system &,
		sanguis::client::load::model::collection const &,
		sanguis::buff_type_vector const &,
		Base const &
	);

	sanguis::diff_clock const &
	diff_clock() const;

	sanguis::client::draw2d::sprite::normal::system &
	normal_system() const;

	sanguis::client::load::model::collection const &
	model_collection() const;

	sanguis::buff_type_vector const &
	buffs() const;

	Base const &
	base() const;
private:
	fcppt::reference<
		sanguis::diff_clock const
	> diff_clock_;

	fcppt::reference<
		sanguis::client::draw2d::sprite::normal::system
	> normal_system_;

	fcppt::reference<
		sanguis::client::load::model::collection const
	> model_collection_;

	sanguis::buff_type_vector const buffs_;

	Base const base_;
};

}
}
}
}

#endif
