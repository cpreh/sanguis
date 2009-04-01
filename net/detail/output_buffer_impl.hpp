template<
	typename Char,
	typename Traits>
void sanguis::net::detail::output_buffer<Char,Traits>::push_back(
	string const &s)
{
	if (current.empty())
		current = s;
	else
		appendix += s;
}

template<
	typename Char,
	typename Traits>
void sanguis::net::detail::output_buffer<Char,Traits>::erase(
	typename string::size_type const bytes)
{
	current = current.substr(bytes)+appendix;
	appendix.clear();
}

template<
	typename Char,
	typename Traits>
bool sanguis::net::detail::output_buffer<Char,Traits>::characters_left() const 
{ 
	return !current.empty(); 
}

template<
	typename Char,
	typename Traits>
typename sanguis::net::detail::output_buffer<Char,Traits>::string const &
	sanguis::net::detail::output_buffer<Char,Traits>::buffer() const 
{ 
	return current; 
}
