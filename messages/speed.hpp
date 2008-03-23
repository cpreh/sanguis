#ifndef SANGUIS_MESSAGES_SPEED_HPP_INCLUDED
#define SANGUIS_MESSAGES_SPEED_HPP_INCLUDED

#include "base.hpp"
#include "types.hpp"
#include "../sge_serialization.hpp"
#include <boost/serialization/base_object.hpp>

namespace sanguis
{
namespace messages
{

class speed : public base {
public:
	speed() {}
	speed(const entity_id id,
	      const vector2&);
	
	const vector2& get() const;
private:
	vector2 speed_;

	friend class boost::serialization::access;
	template<class Archive>
	void serialize(Archive &ar, const unsigned)
	{
		ar & boost::serialization::base_object<base>(*this);
		ar & speed_;
	}
};

}
}

#endif
