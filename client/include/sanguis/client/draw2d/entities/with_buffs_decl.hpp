#ifndef SANGUIS_CLIENT_DRAW2D_ENTITIES_WITH_BUFFS_DECL_HPP_INCLUDED
#define SANGUIS_CLIENT_DRAW2D_ENTITIES_WITH_BUFFS_DECL_HPP_INCLUDED

#include <sanguis/buff_type_fwd.hpp>
#include <sanguis/diff_clock_fwd.hpp>
#include <sanguis/client/draw2d/entities/with_buffs_parameters_fwd.hpp>
#include <sanguis/client/draw2d/entities/buffs/base_fwd.hpp>
#include <sanguis/client/draw2d/entities/ifaces/with_buffs.hpp>
#include <sanguis/client/draw2d/sprite/normal/system_fwd.hpp>
#include <sanguis/client/load/model/collection_fwd.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/ptr_container/ptr_map.hpp>
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

	~with_buffs()
	override;
protected:
	void
	update()
	override;
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

	sanguis::diff_clock const &diff_clock_;

	sanguis::client::draw2d::sprite::normal::system &normal_system_;

	sanguis::client::load::model::collection const &model_collection_;

	typedef
	boost::ptr_map<
		sanguis::buff_type,
		sanguis::client::draw2d::entities::buffs::base
	>
	buff_map;

	buff_map buffs_;
};

}
}
}
}

#endif
