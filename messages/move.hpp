#ifndef SANGUIS_MESSAGES_MOVE_HPP_INCLUDED
#define SANGUIS_MESSAGES_MOVE_HPP_INCLUDED

#include "../sge_serialization.hpp"
#include "base.hpp"
#include "types.hpp"
#include <sge/sprite/sprite.hpp>
#include <boost/serialization/base_object.hpp>

namespace sanguis
{
namespace messages
{

class move : public base {
public:
	move() {}
	move(const entity_id id,
	     const pos_type& pos);
	
	const pos_type& pos() const;
private:
	pos_type pos_;

	friend class boost::serialization::access;
	template<class Archive>
	void serialize(Archive &ar, const unsigned)
	{
		ar & boost::serialization::base_object<base>(*this);
		ar & pos_;
	}
};

}
}

#endif
