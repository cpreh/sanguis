#ifndef SANGUIS_CLIENT_DRAW2D_ENTITIES_FRIEND_HPP_INCLUDED
#define SANGUIS_CLIENT_DRAW2D_ENTITIES_FRIEND_HPP_INCLUDED

#include <sanguis/aura_type_vector.hpp>
#include <sanguis/buff_type_vector.hpp>
#include <sanguis/friend_type_fwd.hpp>
#include <sanguis/client/draw2d/entities/order_vector.hpp>
#include <sanguis/client/draw2d/entities/with_buffs_auras_model.hpp>
#include <sanguis/client/draw2d/entities/model/load_parameters_fwd.hpp>
#include <sanguis/load/auras/context_fwd.hpp>
#include <fcppt/noncopyable.hpp>


namespace sanguis
{
namespace client
{
namespace draw2d
{
namespace entities
{

class friend_
:
	public sanguis::client::draw2d::entities::with_buffs_auras_model
{
	FCPPT_NONCOPYABLE(
		friend_
	);
public:
	friend_(
		sanguis::client::draw2d::entities::model::load_parameters const &,
		sanguis::load::auras::context &,
		sanguis::friend_type,
		sanguis::aura_type_vector const &,
		sanguis::buff_type_vector const &,
		sanguis::client::draw2d::entities::order_vector const &
	);

	~friend_();
};

}
}
}
}

#endif
