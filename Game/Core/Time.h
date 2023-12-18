//
// Created by Vlad Boroday on 2023-11-26.
//

#ifndef UNTITLED1_GAME_CORE_TIME_H_
#define UNTITLED1_GAME_CORE_TIME_H_

#include <chrono>
#include <ratio>

#include <cassert>
#include <cstdint>

namespace SEngine
{
	class Time
	{
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

////////////////////////////////////////////////////////////
/// \brief Represents a time value
///
////////////////////////////////////////////////////////////

	 public:
		////////////////////////////////////////////////////////////
		/// \brief Default constructor
		///
		/// Sets the time value to zero.
		///
		////////////////////////////////////////////////////////////
		constexpr Time();

		////////////////////////////////////////////////////////////
		/// \brief Construct from std::chrono::duration
		///
		////////////////////////////////////////////////////////////
		template<typename Rep, typename Period>
		constexpr Time(const std::chrono::duration<Rep, Period>& duration);

		////////////////////////////////////////////////////////////
		/// \brief Return the time value as a number of seconds
		///
		/// \return Time in seconds
		///
		/// \see asMilliseconds, asMicroseconds
		///
		////////////////////////////////////////////////////////////
		constexpr float asSeconds() const;

		////////////////////////////////////////////////////////////
		/// \brief Return the time value as a number of milliseconds
		///
		/// \return Time in milliseconds
		///
		/// \see asSeconds, asMicroseconds
		///
		////////////////////////////////////////////////////////////
		constexpr std::int32_t asMilliseconds() const;

		////////////////////////////////////////////////////////////
		/// \brief Return the time value as a number of microseconds
		///
		/// \return Time in microseconds
		///
		/// \see asSeconds, asMilliseconds
		///
		////////////////////////////////////////////////////////////
		constexpr std::int64_t asMicroseconds() const;

		////////////////////////////////////////////////////////////
		/// \brief Return the time value as a std::chorono::duration
		///
		/// \return Time in microseconds
		///
		////////////////////////////////////////////////////////////
		constexpr std::chrono::microseconds toDuration() const;

		////////////////////////////////////////////////////////////
		/// \brief Implicit conversion to std::chrono::duration
		///
		/// \return Duration in microseconds
		///
		////////////////////////////////////////////////////////////
		template<typename Rep, typename Period>
		constexpr operator std::chrono::duration<Rep, Period>() const;

		////////////////////////////////////////////////////////////
		// Static member data
		////////////////////////////////////////////////////////////
		// NOLINTNEXTLINE(readability-identifier-naming)
		static const Time Zero; //!< Predefined "zero" time value

	 private:
		friend constexpr Time seconds(float);
		friend constexpr Time milliseconds(std::int32_t);
		friend constexpr Time microseconds(std::int64_t);

		////////////////////////////////////////////////////////////
		// Member data
		////////////////////////////////////////////////////////////
		std::chrono::microseconds m_microseconds{}; //!< Time value stored as microseconds
	};

////////////////////////////////////////////////////////////
/// \relates Time
/// \brief Construct a time value from a number of seconds
///
/// \param amount Number of seconds
///
/// \return Time value constructed from the amount of seconds
///
/// \see milliseconds, microseconds
///
////////////////////////////////////////////////////////////
	constexpr Time seconds(float amount);

////////////////////////////////////////////////////////////
/// \relates Time
/// \brief Construct a time value from a number of milliseconds
///
/// \param amount Number of milliseconds
///
/// \return Time value constructed from the amount of milliseconds
///
/// \see seconds, microseconds
///
////////////////////////////////////////////////////////////
	constexpr Time milliseconds(std::int32_t amount);

////////////////////////////////////////////////////////////
/// \relates Time
/// \brief Construct a time value from a number of microseconds
///
/// \param amount Number of microseconds
///
/// \return Time value constructed from the amount of microseconds
///
/// \see seconds, milliseconds
///
////////////////////////////////////////////////////////////
	constexpr Time microseconds(std::int64_t amount);

////////////////////////////////////////////////////////////
/// \relates Time
/// \brief Overload of == operator to compare two time values
///
/// \param left  Left operand (a time)
/// \param right Right operand (a time)
///
/// \return True if both time values are equal
///
////////////////////////////////////////////////////////////
	[[nodiscard]] constexpr bool operator==(Time left, Time right);

////////////////////////////////////////////////////////////
/// \relates Time
/// \brief Overload of != operator to compare two time values
///
/// \param left  Left operand (a time)
/// \param right Right operand (a time)
///
/// \return True if both time values are different
///
////////////////////////////////////////////////////////////
	[[nodiscard]] constexpr bool operator!=(Time left, Time right);

////////////////////////////////////////////////////////////
/// \relates Time
/// \brief Overload of < operator to compare two time values
///
/// \param left  Left operand (a time)
/// \param right Right operand (a time)
///
/// \return True if \a left is lesser than \a right
///
////////////////////////////////////////////////////////////
	[[nodiscard]] constexpr bool operator<(Time left, Time right);

////////////////////////////////////////////////////////////
/// \relates Time
/// \brief Overload of > operator to compare two time values
///
/// \param left  Left operand (a time)
/// \param right Right operand (a time)
///
/// \return True if \a left is greater than \a right
///
////////////////////////////////////////////////////////////
	[[nodiscard]] constexpr bool operator>(Time left, Time right);

////////////////////////////////////////////////////////////
/// \relates Time
/// \brief Overload of <= operator to compare two time values
///
/// \param left  Left operand (a time)
/// \param right Right operand (a time)
///
/// \return True if \a left is lesser or equal than \a right
///
////////////////////////////////////////////////////////////
	[[nodiscard]] constexpr bool operator<=(Time left, Time right);

////////////////////////////////////////////////////////////
/// \relates Time
/// \brief Overload of >= operator to compare two time values
///
/// \param left  Left operand (a time)
/// \param right Right operand (a time)
///
/// \return True if \a left is greater or equal than \a right
///
////////////////////////////////////////////////////////////
	[[nodiscard]] constexpr bool operator>=(Time left, Time right);

////////////////////////////////////////////////////////////
/// \relates Time
/// \brief Overload of unary - operator to negate a time value
///
/// \param right Right operand (a time)
///
/// \return Opposite of the time value
///
////////////////////////////////////////////////////////////
	[[nodiscard]] constexpr Time operator-(Time right);

////////////////////////////////////////////////////////////
/// \relates Time
/// \brief Overload of binary + operator to add two time values
///
/// \param left  Left operand (a time)
/// \param right Right operand (a time)
///
/// \return Sum of the two times values
///
////////////////////////////////////////////////////////////
	[[nodiscard]] constexpr Time operator+(Time left, Time right);

////////////////////////////////////////////////////////////
/// \relates Time
/// \brief Overload of binary += operator to add/assign two time values
///
/// \param left  Left operand (a time)
/// \param right Right operand (a time)
///
/// \return Sum of the two times values
///
////////////////////////////////////////////////////////////
	constexpr Time& operator+=(Time& left, Time right);

////////////////////////////////////////////////////////////
/// \relates Time
/// \brief Overload of binary - operator to subtract two time values
///
/// \param left  Left operand (a time)
/// \param right Right operand (a time)
///
/// \return Difference of the two times values
///
////////////////////////////////////////////////////////////
	[[nodiscard]] constexpr Time operator-(Time left, Time right);

////////////////////////////////////////////////////////////
/// \relates Time
/// \brief Overload of binary -= operator to subtract/assign two time values
///
/// \param left  Left operand (a time)
/// \param right Right operand (a time)
///
/// \return Difference of the two times values
///
////////////////////////////////////////////////////////////
	constexpr Time& operator-=(Time& left, Time right);

////////////////////////////////////////////////////////////
/// \relates Time
/// \brief Overload of binary * operator to scale a time value
///
/// \param left  Left operand (a time)
/// \param right Right operand (a number)
///
/// \return \a left multiplied by \a right
///
////////////////////////////////////////////////////////////
	[[nodiscard]] constexpr Time operator*(Time left, float right);

////////////////////////////////////////////////////////////
/// \relates Time
/// \brief Overload of binary * operator to scale a time value
///
/// \param left  Left operand (a time)
/// \param right Right operand (a number)
///
/// \return \a left multiplied by \a right
///
////////////////////////////////////////////////////////////
	[[nodiscard]] constexpr Time operator*(Time left, std::int64_t right);

////////////////////////////////////////////////////////////
/// \relates Time
/// \brief Overload of binary * operator to scale a time value
///
/// \param left  Left operand (a number)
/// \param right Right operand (a time)
///
/// \return \a left multiplied by \a right
///
////////////////////////////////////////////////////////////
	[[nodiscard]] constexpr Time operator*(float left, Time right);

////////////////////////////////////////////////////////////
/// \relates Time
/// \brief Overload of binary * operator to scale a time value
///
/// \param left  Left operand (a number)
/// \param right Right operand (a time)
///
/// \return \a left multiplied by \a right
///
////////////////////////////////////////////////////////////
	[[nodiscard]] constexpr Time operator*(std::int64_t left, Time right);

////////////////////////////////////////////////////////////
/// \relates Time
/// \brief Overload of binary *= operator to scale/assign a time value
///
/// \param left  Left operand (a time)
/// \param right Right operand (a number)
///
/// \return \a left multiplied by \a right
///
////////////////////////////////////////////////////////////
	constexpr Time& operator*=(Time& left, float right);

////////////////////////////////////////////////////////////
/// \relates Time
/// \brief Overload of binary *= operator to scale/assign a time value
///
/// \param left  Left operand (a time)
/// \param right Right operand (a number)
///
/// \return \a left multiplied by \a right
///
////////////////////////////////////////////////////////////
	constexpr Time& operator*=(Time& left, std::int64_t right);

////////////////////////////////////////////////////////////
/// \relates Time
/// \brief Overload of binary / operator to scale a time value
///
/// \param left  Left operand (a time)
/// \param right Right operand (a number)
///
/// \return \a left divided by \a right
///
////////////////////////////////////////////////////////////
	[[nodiscard]] constexpr Time operator/(Time left, float right);

////////////////////////////////////////////////////////////
/// \relates Time
/// \brief Overload of binary / operator to scale a time value
///
/// \param left  Left operand (a time)
/// \param right Right operand (a number)
///
/// \return \a left divided by \a right
///
////////////////////////////////////////////////////////////
	[[nodiscard]] constexpr Time operator/(Time left, std::int64_t right);

////////////////////////////////////////////////////////////
/// \relates Time
/// \brief Overload of binary /= operator to scale/assign a time value
///
/// \param left  Left operand (a time)
/// \param right Right operand (a number)
///
/// \return \a left divided by \a right
///
////////////////////////////////////////////////////////////
	constexpr Time& operator/=(Time& left, float right);

////////////////////////////////////////////////////////////
/// \relates Time
/// \brief Overload of binary /= operator to scale/assign a time value
///
/// \param left  Left operand (a time)
/// \param right Right operand (a number)
///
/// \return \a left divided by \a right
///
////////////////////////////////////////////////////////////
	constexpr Time& operator/=(Time& left, std::int64_t right);

////////////////////////////////////////////////////////////
/// \relates Time
/// \brief Overload of binary / operator to compute the ratio of two time values
///
/// \param left  Left operand (a time)
/// \param right Right operand (a time)
///
/// \return \a left divided by \a right
///
////////////////////////////////////////////////////////////
	[[nodiscard]] constexpr float operator/(Time left, Time right);

////////////////////////////////////////////////////////////
/// \relates Time
/// \brief Overload of binary % operator to compute remainder of a time value
///
/// \param left  Left operand (a time)
/// \param right Right operand (a time)
///
/// \return \a left modulo \a right
///
////////////////////////////////////////////////////////////
	[[nodiscard]] constexpr Time operator%(Time left, Time right);

////////////////////////////////////////////////////////////
/// \relates Time
/// \brief Overload of binary %= operator to compute/assign remainder of a time value
///
/// \param left  Left operand (a time)
/// \param right Right operand (a time)
///
/// \return \a left modulo \a right
///
////////////////////////////////////////////////////////////
	constexpr Time& operator%=(Time& left, Time right);
}

#endif //UNTITLED1_GAME_CORE_TIME_H_
