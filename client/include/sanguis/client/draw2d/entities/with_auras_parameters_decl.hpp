#ifndef SANGUIS_CLIENT_DRAW2D_ENTITIES_WITH_AURAS_PARAMETERS_DECL_HPP_INCLUDED
#define SANGUIS_CLIENT_DRAW2D_ENTITIES_WITH_AURAS_PARAMETERS_DECL_HPP_INCLUDED

#include <sanguis/aura_type_vector.hpp>
#include <sanguis/diff_clock_cref.hpp>
#include <sanguis/diff_clock_fwd.hpp>
#include <sanguis/client/draw2d/sprite/normal/system_fwd.hpp>
#include <sanguis/client/draw2d/sprite/normal/system_ref.hpp>
#include <sanguis/client/load/auras/context_fwd.hpp>
#include <sanguis/client/load/auras/context_ref.hpp>


namespace sanguis::client::draw2d::entities
{

template<
	typename Base
>
class with_auras_parameters
{
public:
	with_auras_parameters(
		sanguis::diff_clock_cref,
		sanguis::client::load::auras::context_ref,
		sanguis::client::draw2d::sprite::normal::system_ref,
		sanguis::aura_type_vector &&,
		Base &&
	);

	[[nodiscard]]
	sanguis::diff_clock const &
	diff_clock() const;

	[[nodiscard]]
	sanguis::client::load::auras::context &
	aura_load_context() const;

	[[nodiscard]]
	sanguis::client::draw2d::sprite::normal::system &
	normal_system() const;

	[[nodiscard]]
	sanguis::aura_type_vector const &
	auras() const;

	[[nodiscard]]
	Base const &
	base() const;
private:
	sanguis::diff_clock_cref diff_clock_;

	sanguis::client::load::auras::context_ref aura_load_context_;

	sanguis::client::draw2d::sprite::normal::system_ref normal_system_;

	sanguis::aura_type_vector auras_;

	Base base_;
};

}

#endif
