#ifndef SANGUIS_MESSAGES_ADD_HPP_INCLUDED
#define SANGUIS_MESSAGES_ADD_HPP_INCLUDED

#include "../entity_type.hpp"
#include "../sge_serialization.hpp"
#include "base.hpp"
#include "types.hpp"
#include <sge/types.hpp>
#include <sge/math/vector.hpp>
#include <sge/sprite/sprite.hpp>
#include <boost/serialization/base_object.hpp>

namespace sanguis
{
namespace messages
{

class add : public base {
public:
	add();
	add(const entity_id id,
	    const entity_type::type type_,
	    const pos_type& pos,
	    const dim_type& sz,
	    const space_unit angle,
	    const vector2& speed);

	entity_type::type type() const;
	const pos_type& pos() const;
	const dim_type& sz() const;
	space_unit angle() const;
	const vector2& speed() const;
private:
	entity_type::type  type_;
	pos_type           pos_;
	dim_type           sz_;
	space_unit         angle_;
	vector2            speed_;

	friend class boost::serialization::access;
	template<class Archive>
	void serialize(Archive &ar, const unsigned)
	{
		ar & boost::serialization::base_object<base>(*this);
		ar & type_ & pos_ & sz_ & angle_ & speed_;
	}
};

}
}

#endif
