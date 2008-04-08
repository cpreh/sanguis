#ifndef SANGUIS_MESSAGES_RESIZE_HPP_INCLUDED
#define SANGUIS_MESSAGES_RESIZE_HPP_INCLUDED

#include "entity_message.hpp"
#include "types.hpp"
#include <boost/serialization/access.hpp>

namespace sanguis
{
namespace messages
{

class resize : public entity_message {
public:
	resize();
	resize(
		entity_id,
		dim_type const&);
	
	dim_type const& dim() const;
private:
	dim_type dim_;

	friend class boost::serialization::access;
	template<typename Archive>
	void serialize(Archive &ar, unsigned);
};

}
}

#endif
