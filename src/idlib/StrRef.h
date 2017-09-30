#pragma once
#include "Str.h"

/*
===============================================================================

	Non-owning reference to a c style string.

===============================================================================
*/
class fhStrRef {
public:
	fhStrRef() ;
	fhStrRef( const char* s, int size ) ;
	fhStrRef( const char* s ) ;
	~fhStrRef();

	operator bool() const { return !IsNull(); }

	void Reset() ;
	void Reset( const char* s, int size ) ;

	bool IsNull() const;
	bool IsValid() const;
	bool IsEmpty() const;

	const char* c_str() const;
	int Length() const;

	bool operator==(const char* s) const;
	bool operator==(fhStrRef s) const;
	bool operator==(const idStr& s) const;
	bool operator!=(const char* s) const;
	bool operator!=(fhStrRef s) const;
	bool operator!=(const idStr& s) const;
	char operator[]( int n ) const;

	fhStrRef operator++() ;
	fhStrRef operator++(int);

	fhStrRef Left( int n ) const;
	fhStrRef Right( int n ) const;
	fhStrRef Substr( int from ) const;
	fhStrRef Substr( int from, int n ) const;

	bool StartsWith( fhStrRef s ) const;
	bool StartsWith( const char* s ) const;
	bool StartsWith( const idStr& s ) const;

	bool EndsWith( fhStrRef s ) const;
	bool EndsWith( const char* s ) const;
	bool EndsWith( const idStr& s ) const;

	fhStrRef TrimmedLeft() const;
	fhStrRef TrimmedRight() const;
	fhStrRef Trimmed() const;

	int OffsetIn( const idStr& s ) const;

	idStr ToString() const;

private:
	const char* s;
	int length;
};

inline fhStrRef::fhStrRef()
: s( nullptr )
, length( 0 ) {
}

inline fhStrRef::fhStrRef( const char* s )
: s( s )
, length( !s ? 0 : static_cast<int>(strlen( s )) ) {
}

inline fhStrRef::fhStrRef( const char* s, int size )
: s( s )
, length( size ) {
//	assert( (!s && !length) || (!!s && length <= (int)strlen( s )) );
}

inline fhStrRef::~fhStrRef() {
}

inline void fhStrRef::Reset() {
	(*this) = fhStrRef();
}

inline void fhStrRef::Reset( const char* s, int size ) {
	s = s;
	length = size;
//	assert( (!s && !length) || (!!s && length <= strlen( s )) );
}

inline bool fhStrRef::IsNull() const {
	return !s;
}

inline bool fhStrRef::IsValid() const {
	return !IsNull();
}

inline bool fhStrRef::IsEmpty() const {
	return !length;
}

inline const char* fhStrRef::c_str() const {
	return s;
}

inline int fhStrRef::Length() const {
	return length;
}

inline bool fhStrRef::operator==(fhStrRef ref) const {
	if (IsNull() && ref.IsNull())
		return true;

	if (IsNull() || ref.IsNull())
		return false;

	if (length != ref.length)
		return false;

	return !strncmp( s, ref.s, length );
}

inline bool fhStrRef::operator==(const char* s) const {
	return *this == fhStrRef( s );
}

inline bool fhStrRef::operator!=(fhStrRef ref) const {
	return !(*this == ref);
}

inline bool fhStrRef::operator!=(const char* s) const {
	return !(*this == s);
}

inline char fhStrRef::operator[]( int n ) const {
	assert( n < length );
	return s[n];
}

inline fhStrRef fhStrRef::operator++() {
	if (IsEmpty())
		return fhStrRef();

	++s;
	--length;

	return *this;
}

inline fhStrRef fhStrRef::operator++(int) {
	if (IsEmpty())
		return fhStrRef();

	fhStrRef ret = *this;

	++s;
	--length;

	return ret;
}

inline fhStrRef fhStrRef::Left( int n ) const {
	return fhStrRef( s, Min( n, length ) );
}

inline fhStrRef fhStrRef::Right( int n ) const {
	return fhStrRef( &s[length - Min( n, length )], Min( n, length ) );
}

inline fhStrRef fhStrRef::Substr( int from ) const {
	return Substr( from, length );
}

inline fhStrRef fhStrRef::Substr( int from, int n ) const {
	from = Min( from, length );
	n = Min( n, length - from );

	return fhStrRef( &s[from], n );
}

inline fhStrRef fhStrRef::TrimmedLeft() const {
	fhStrRef ret = *this;
	while(!ret.IsEmpty() && idStr::CharIsWhitespace(ret[0])) {
		++ret;
	}
	return ret;
}

inline fhStrRef fhStrRef::TrimmedRight() const {
	fhStrRef ret = *this;
	while (!ret.IsEmpty() && idStr::CharIsWhitespace( ret[ret.Length()-1] )) {
		ret = ret.Substr(ret.Length()-2);
	}
	return ret;
}

inline fhStrRef fhStrRef::Trimmed() const {
	return TrimmedLeft().TrimmedRight();
}

inline bool fhStrRef::StartsWith( fhStrRef sr ) const {
	if (IsNull() || sr.IsNull())
		return false;

	if (sr.IsEmpty())
		return true;

	if (length < sr.length)
		return false;

	return !strncmp( s, sr.s, sr.length );
}

inline bool fhStrRef::StartsWith( const char* s ) const {
	return StartsWith( fhStrRef( s ) );
}

inline bool fhStrRef::EndsWith( fhStrRef sr ) const {
	if (IsNull() || sr.IsNull())
		return false;

	if (sr.IsEmpty())
		return true;

	if (length < sr.length)
		return false;

	return !strncmp( &s[length - sr.length], sr.s, sr.length );
}

inline bool fhStrRef::EndsWith( const char* s ) const {
	return EndsWith( fhStrRef( s ) );
}


inline idStr fhStrRef::ToString() const {
	return idStr(this->c_str(), 0, this->Length());
}