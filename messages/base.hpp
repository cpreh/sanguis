#ifndef SANGUIS_MESSAGES_BASE_HPP_INCLUDED
#define SANGUIS_MESSAGES_BASE_HPP_INCLUDED

#include <sge/shared_ptr.hpp>
#include <boost/serialization/access.hpp>
#include <memory>

namespace sanguis
{
namespace messages
{

class base {
public:
	base();
	virtual ~base();
private:
	friend class boost::serialization::access;
	template<typename Archive>
	void serialize(Archive &ar, unsigned);
};

typedef std::auto_ptr<messages::base> auto_ptr;

}

typedef sge::shared_ptr<messages::base> message_ptr;

}

#endif
