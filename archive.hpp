#ifndef SANGUIS_ARCHIVE_HPP_INCLUDED
#define SANGUIS_ARCHIVE_HPP_INCLUDED

#include <boost/archive/text_iarchive.hpp>
#include <boost/archive/text_oarchive.hpp>
//#include <boost/archive/binary_iarchive.hpp>
//#include <boost/archive/binary_oarchive.hpp>

namespace sanguis
{

typedef boost::archive::text_iarchive iarchive;
typedef boost::archive::text_oarchive oarchive;

}

#endif
