#ifndef SANGUIS_CLIENT_DRAW2D_ENTITIES_WITH_AURAS_DECL_HPP_INCLUDED
#define SANGUIS_CLIENT_DRAW2D_ENTITIES_WITH_AURAS_DECL_HPP_INCLUDED

#include <sanguis/aura_type.hpp>
#include <sanguis/diff_timer.hpp>
#include <sanguis/client/draw2d/entities/with_auras_fwd.hpp>
#include <sanguis/client/draw2d/entities/with_auras_parameters_fwd.hpp>
#include <sanguis/client/draw2d/entities/ifaces/with_auras.hpp>
#include <sanguis/client/draw2d/sprite/normal/object.hpp>
#include <sanguis/client/draw2d/sprite/normal/system_fwd.hpp>
#include <sanguis/client/load/auras/context_fwd.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/config/external_begin.hpp>
#include <map>
#include <fcppt/config/external_end.hpp>


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
class with_auras
:
	public sanguis::client::draw2d::entities::ifaces::with_auras,
	public Base
{
	FCPPT_NONCOPYABLE(
		with_auras
	);
public:
	typedef
	typename
	Base::parameters_type
	base_parameters;

	typedef
	sanguis::client::draw2d::entities::with_auras_parameters<
		base_parameters
	>
	parameters_type;

	explicit
	with_auras(
		parameters_type const &
	);

	~with_auras();
protected:
	virtual
	void
	update()
	override;
private:
	void
	on_die()
	override;

	void
	add_aura(
		sanguis::aura_type
	)
	override;

	sanguis::client::load::auras::context &aura_load_context_;

	sanguis::client::draw2d::sprite::normal::system &normal_system_;

	sanguis::diff_timer rotate_timer_;

	typedef
	std::map<
		sanguis::aura_type,
		sanguis::client::draw2d::sprite::normal::object
	>
	sprite_map;

	sprite_map sprites_;
};

}
}
}
}

#endif
