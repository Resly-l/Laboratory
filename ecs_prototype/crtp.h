#pragma once
#include <string>

// base class has virtual functions to query ids
// child class overrides the functions with unique ids

#define DECLARE_CRTP(type, idType) \
class type##Base : public type##Interface \
{ \
public: \
	inline static idType gid = 0; \
public: \
	virtual idType GetID() const = 0; \
	virtual std::string GetStringID() const = 0; \
}; \
\
template <typename T> \
class type : public type##Base \
{ \
public: \
	static const idType id; \
	static const std::string stringId; \
\
public: \
	idType GetID() const override { return id; } \
	std::string GetStringID() const override { return stringId; } \
}; \
\
template<typename T> \
const idType type<T>::id = gid++; \
\
template<typename T> \
const std::string type<T>::stringId(std::string(typeid(T).name()), 6);