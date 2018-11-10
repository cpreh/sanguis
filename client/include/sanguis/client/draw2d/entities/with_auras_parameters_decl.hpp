#ifndef SANGUIS_CLIENT_DRAW2D_ENTITIES_WITH_AURAS_PARAMETERS_DECL_HPP_INCLUDED
#define SANGUIS_CLIENT_DRAW2D_ENTITIES_WITH_AURAS_PARAMETERS_DECL_HPP_INCLUDED

#include <sanguis/aura_type_vector.hpp>
#include <sanguis/diff_clock_fwd.hpp>
#include <sanguis/client/draw2d/sprite/normal/system_fwd.hpp>
#include <sanguis/client/load/auras/context_fwd.hpp>
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
class with_auras_parameters
{
public:
	with_auras_parameters(
		sanguis::diff_clock const &,
		sanguis::client::load::auras::context &,
		sanguis::client::draw2d::sprite::normal::system &,
		sanguis::aura_type_vector const &,
		Base const &
	);

	sanguis::diff_clock const &
	diff_clock() const;

	sanguis::client::load::auras::context &
	aura_load_context() const;

	sanguis::client::draw2d::sprite::normal::system &
	normal_system() const;

	sanguis::aura_type_vector const &
	auras() const;

	Base const &
	base() const;
private:
	fcppt::reference<
		sanguis::diff_clock const
	> diff_clock_;

	fcppt::reference<
		sanguis::client::load::auras::context
	> aura_load_context_;

	fcppt::reference<
		sanguis::client::draw2d::sprite::normal::system
	> normal_system_;

	sanguis::aura_type_vector auras_;

	Base base_;
};

}
}
}
}

#endif
