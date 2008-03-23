#ifndef SGE_SERIALIZATION_HPP_INCLUDED
#define SGE_SERIALIZATION_HPP_INCLUDED

#include <boost/serialization/base_object.hpp>
#include <sge/math/vector.hpp>
#include <sge/math/dim.hpp>

namespace sge
{
namespace math
{
template<class T,std::size_t Dim,class Archive> 
inline void serialize(Archive &ar,sge::math::basic_vector<T,Dim> &v,const unsigned)
{
	for (std::size_t i = 0; i < Dim; ++i)
		ar & v[i];
}

template<class T,std::size_t Dim,class Archive> 
inline void serialize(Archive &ar,sge::math::basic_dim<T,Dim> &v,const unsigned)
{
	for (std::size_t i = 0; i < Dim; ++i)
		ar & v[i];
}
}
}

#endif
