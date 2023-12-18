//
// Created by Vlad Boroday on 2023-11-26.
//

////////////////////////////////////////////////////////////
//
// SFML - Simple and Fast Multimedia Library
// Copyright (C) 2007-2023 Laurent Gomila (laurent@sfml-dev.org)
//
// This software is provided 'as-is', without any express or implied warranty.
// In no event will the authors be held liable for any damages arising from the use of this software.
//
// Permission is granted to anyone to use this software for any purpose,
// including commercial applications, and to alter it and redistribute it freely,
// subject to the following restrictions:
//
// 1. The origin of this software must not be misrepresented;
//    you must not claim that you wrote the original software.
//    If you use this software in a product, an acknowledgment
//    in the product documentation would be appreciated but is not required.
//
// 2. Altered source versions must be plainly marked as such,
//    and must not be misrepresented as being the original software.
//
// 3. This notice may not be removed or altered from any source distribution.
//
////////////////////////////////////////////////////////////

#include "Time.h"

////////////////////////////////////////////////////////////
constexpr SEngine::Time::Time() = default;

////////////////////////////////////////////////////////////
template<typename Rep, typename Period>
constexpr SEngine::Time::Time(const std::chrono::duration<Rep, Period>& duration) : m_microseconds(duration)
{
}

////////////////////////////////////////////////////////////
constexpr float SEngine::Time::asSeconds() const
{
	return std::chrono::duration<float>(m_microseconds).count();
}

////////////////////////////////////////////////////////////
constexpr std::int32_t SEngine::Time::asMilliseconds() const
{
	return std::chrono::duration_cast<std::chrono::duration<std::int32_t, std::milli>>(m_microseconds).count();
}

////////////////////////////////////////////////////////////
constexpr std::int64_t SEngine::Time::asMicroseconds() const
{
	return m_microseconds.count();
}

////////////////////////////////////////////////////////////
constexpr std::chrono::microseconds SEngine::Time::toDuration() const
{
	return m_microseconds;
}

////////////////////////////////////////////////////////////
template<typename Rep, typename Period>
constexpr SEngine::Time::operator std::chrono::duration<Rep, Period>() const
{
	return m_microseconds;
}

////////////////////////////////////////////////////////////
constexpr SEngine::Time seconds(float amount)
{
	return std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::duration<float>(amount));
}

////////////////////////////////////////////////////////////
constexpr SEngine::Time milliseconds(std::int32_t amount)
{
	return std::chrono::milliseconds(amount);
}

////////////////////////////////////////////////////////////
constexpr SEngine::Time microseconds(std::int64_t amount)
{
	return std::chrono::microseconds(amount);
}

////////////////////////////////////////////////////////////
constexpr bool operator==(SEngine::Time left, SEngine::Time right)
{
	return left.asMicroseconds() == right.asMicroseconds();
}

////////////////////////////////////////////////////////////
constexpr bool operator!=(SEngine::Time left, SEngine::Time right)
{
	return left.asMicroseconds() != right.asMicroseconds();
}

////////////////////////////////////////////////////////////
constexpr bool operator<(SEngine::Time left, SEngine::Time right)
{
	return left.asMicroseconds() < right.asMicroseconds();
}

////////////////////////////////////////////////////////////
constexpr bool operator>(SEngine::Time left, SEngine::Time right)
{
	return left.asMicroseconds() > right.asMicroseconds();
}

////////////////////////////////////////////////////////////
constexpr bool operator<=(SEngine::Time left, SEngine::Time right)
{
	return left.asMicroseconds() <= right.asMicroseconds();
}

////////////////////////////////////////////////////////////
constexpr bool operator>=(SEngine::Time left, SEngine::Time right)
{
	return left.asMicroseconds() >= right.asMicroseconds();
}

////////////////////////////////////////////////////////////
constexpr SEngine::Time operator-(SEngine::Time right)
{
	return microseconds(-right.asMicroseconds());
}

////////////////////////////////////////////////////////////
constexpr SEngine::Time& operator+=(SEngine::Time& left, SEngine::Time right)
{
	return left = left + right;
}

////////////////////////////////////////////////////////////
constexpr SEngine::Time operator+(SEngine::Time left, SEngine::Time right)
{
	return microseconds(left.asMicroseconds() + right.asMicroseconds());
}

////////////////////////////////////////////////////////////
constexpr SEngine::Time& operator-=(SEngine::Time& left, SEngine::Time right)
{
	return left = left - right;
}

////////////////////////////////////////////////////////////
constexpr SEngine::Time operator-(SEngine::Time left, SEngine::Time right)
{
	return microseconds(left.asMicroseconds() - right.asMicroseconds());
}

////////////////////////////////////////////////////////////
constexpr SEngine::Time operator*(float left, SEngine::Time right)
{
	return right * left;
}

////////////////////////////////////////////////////////////
constexpr SEngine::Time operator*(std::int64_t left, SEngine::Time right)
{
	return right * left;
}

////////////////////////////////////////////////////////////
constexpr SEngine::Time& operator*=(SEngine::Time& left, float right)
{
	return left = left * right;
}

////////////////////////////////////////////////////////////
constexpr SEngine::Time& operator*=(SEngine::Time& left, std::int64_t right)
{
	return left = left * right;
}

////////////////////////////////////////////////////////////
constexpr SEngine::Time operator*(SEngine::Time left, std::int64_t right)
{
	return microseconds(left.asMicroseconds() * right);
}

////////////////////////////////////////////////////////////
constexpr SEngine::Time operator*(SEngine::Time left, float right)
{
	return seconds(left.asSeconds() * right);
}

////////////////////////////////////////////////////////////
constexpr SEngine::Time& operator/=(SEngine::Time& left, float right)
{
	assert(right != 0 && "Time::operator/= cannot divide by 0");
	return left = left / right;
}

////////////////////////////////////////////////////////////
constexpr SEngine::Time& operator/=(SEngine::Time& left, std::int64_t right)
{
	assert(right != 0 && "Time::operator/= cannot divide by 0");
	return left = left / right;
}

////////////////////////////////////////////////////////////
constexpr float operator/(SEngine::Time left, SEngine::Time right)
{
	assert(right.asMicroseconds() != 0 && "Time::operator/ cannot divide by 0");
	return left.asSeconds() / right.asSeconds();
}

////////////////////////////////////////////////////////////
constexpr SEngine::Time operator/(SEngine::Time left, float right)
{
	assert(right != 0 && "Time::operator/ cannot divide by 0");
	return seconds(left.asSeconds() / right);
}

////////////////////////////////////////////////////////////
constexpr SEngine::Time operator/(SEngine::Time left, std::int64_t right)
{
	assert(right != 0 && "Time::operator/ cannot divide by 0");
	return microseconds(left.asMicroseconds() / right);
}

////////////////////////////////////////////////////////////
constexpr SEngine::Time& operator%=(SEngine::Time& left, SEngine::Time right)
{
	assert(right.asMicroseconds() != 0 && "Time::operator%= cannot modulus by 0");
	return left = left % right;
}

////////////////////////////////////////////////////////////
constexpr SEngine::Time operator%(SEngine::Time left, SEngine::Time right)
{
	assert(right.asMicroseconds() != 0 && "Time::operator% cannot modulus by 0");
	return microseconds(left.asMicroseconds() % right.asMicroseconds());
}


////////////////////////////////////////////////////////////
// Static member data
////////////////////////////////////////////////////////////

// Note: the 'inline' keyword here is technically not required, but VS2019 fails
// to compile with a bogus "multiple definition" error if not explicitly used.
inline constexpr SEngine::Time SEngine::Time::Zero;