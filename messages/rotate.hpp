#ifndef SANGUIS_MESSAGES_ROTATE_HPP_INCLUDED
#define SANGUIS_MESSAGES_ROTATE_HPP_INCLUDED

#include "base.hpp"
#include "types.hpp"
#include <sge/types.hpp>
#include <boost/serialization/base_object.hpp>

namespace sanguis
{
namespace messages
{

class rotate : public base {
public:
	rotate() {}
	rotate(const entity_id id,
	       const space_unit rot);
	
	space_unit rot() const;
private:
	space_unit rot_;

	friend class boost::serialization::access;
	template<class Archive>
	void serialize(Archive &ar, const unsigned)
	{
		ar & boost::serialization::base_object<base>(*this);
		ar & rot_;
	}
};

}
}

#endif
