#ifndef SANGUIS_CLIENT_DRAW2D_ENTITIES_WITH_BUFFS_DECL_HPP_INCLUDED
#define SANGUIS_CLIENT_DRAW2D_ENTITIES_WITH_BUFFS_DECL_HPP_INCLUDED

#include <sanguis/buff_type_fwd.hpp>
#include <sanguis/client/draw2d/entities/with_buffs_parameters_fwd.hpp>
#include <sanguis/client/draw2d/entities/ifaces/with_buffs.hpp>
#include <fcppt/noncopyable.hpp>


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
class with_buffs
:
	public sanguis::client::draw2d::entities::ifaces::with_buffs,
	public Base
{
	FCPPT_NONCOPYABLE(
		with_buffs
	);
public:
	typedef
	typename
	Base::parameters_type
	base_parameters;

	typedef
	sanguis::client::draw2d::entities::with_buffs_parameters<
		base_parameters
	>
	parameters_type;

	explicit
	with_buffs(
		parameters_type const &
	);

	~with_buffs();
private:
	void
	add_buff(
		sanguis::buff_type
	)
	override;

	void
	remove_buff(
		sanguis::buff_type
	)
	override;

};

}
}
}
}

#endif
