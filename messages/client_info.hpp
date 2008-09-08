#ifndef SANGUIS_MESSAGES_CLIENT_INFO_HPP_INCLUDED
#define SANGUIS_MESSAGES_CLIENT_INFO_HPP_INCLUDED

#include "types.hpp"
#include "base.hpp"
#include <boost/serialization/access.hpp>

namespace sanguis
{
namespace messages
{

class client_info : public base {
public:
	client_info();
	explicit client_info(
		string const &);

	string const &name() const;
private:
	string name_;

	friend class boost::serialization::access;
	template<typename Archive>
	void serialize(Archive &ar, unsigned);
};

}
}

#endif
