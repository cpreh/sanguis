#ifndef SANGUIS_CLIENT_DRAW2D_ENTITIES_WITH_BUFFS_DECL_HPP_INCLUDED
#define SANGUIS_CLIENT_DRAW2D_ENTITIES_WITH_BUFFS_DECL_HPP_INCLUDED

#include <sanguis/buff_type_fwd.hpp>
#include <sanguis/diff_clock_cref.hpp>
#include <sanguis/client/draw2d/entities/with_buffs_parameters_fwd.hpp>
#include <sanguis/client/draw2d/entities/buffs/unique_ptr.hpp>
#include <sanguis/client/draw2d/entities/ifaces/with_buffs.hpp>
#include <sanguis/client/draw2d/sprite/normal/system_ref.hpp>
#include <sanguis/client/load/model/collection_cref.hpp>
#include <fcppt/nonmovable.hpp>
#include <fcppt/config/external_begin.hpp>
#include <map>
#include <fcppt/config/external_end.hpp>


namespace sanguis::client::draw2d::entities
{

template<
	typename Base
>
class with_buffs
:
	public sanguis::client::draw2d::entities::ifaces::with_buffs,
	public Base
{
	FCPPT_NONMOVABLE(
		with_buffs
	);
public:
	using
	base_parameters
	=
	typename
	Base::parameters_type;

	using
	parameters_type
	=
	sanguis::client::draw2d::entities::with_buffs_parameters<
		base_parameters
	>;

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

	sanguis::diff_clock_cref const diff_clock_;

	sanguis::client::draw2d::sprite::normal::system_ref const normal_system_;

	sanguis::client::load::model::collection_cref const model_collection_;

	using
	buff_map
	=
	std::map<
		sanguis::buff_type,
		sanguis::client::draw2d::entities::buffs::unique_ptr
	>;

	buff_map buffs_;
};

}

#endif
