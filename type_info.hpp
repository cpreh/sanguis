#ifndef TYPE_INFO_HPP_INCLUDED
#define TYPE_INFO_HPP_INCLUDED

#include <typeinfo>
#include <cassert>

class type_info
{
	public:
	type_info();
	type_info(const std::type_info&);

	const std::type_info& get() const;
	bool before(const type_info& rhs) const;
	const char* name() const;

	private:
	const std::type_info* info_;
};

// Implementation

inline type_info::type_info()
{
	class Nil {};
	info_ = &typeid(Nil);
	assert(info_);
}

inline type_info::type_info(const std::type_info& ti)
	: info_(&ti)
{ 
	assert(info_); 
}

inline bool type_info::before(const type_info& rhs) const
{
	assert(info_);
	return info_->before(*rhs.info_);
}

inline const std::type_info& type_info::get() const
{
	assert(info_);
	return *info_;
}

inline const char* type_info::name() const
{
	assert(info_);
	return info_->name();
}

inline bool operator==(const type_info& lhs, const type_info& rhs)
{ return lhs.get() == rhs.get(); }

inline bool operator<(const type_info& lhs, const type_info& rhs)
{ return lhs.before(rhs); }

inline bool operator!=(const type_info& lhs, const type_info& rhs)
{ return !(lhs == rhs); }

inline bool operator>(const type_info& lhs, const type_info& rhs)
{ return rhs < lhs; }

inline bool operator<=(const type_info& lhs, const type_info& rhs)
{ return !(lhs > rhs); }

inline bool operator>=(const type_info& lhs, const type_info& rhs)
{ return !(lhs < rhs); }

#endif
