/******************************************************************************
 * QSkinny - Copyright (C) 2016 Uwe Rathmann
 * This file may be used under the terms of the QSkinny License, Version 1.0
 *****************************************************************************/

#ifndef QSK_INTERVAL_H
#define QSK_INTERVAL_H

#include "QskGlobal.h"
#include <qglobal.h>
#include <qmetatype.h>

class QSK_EXPORT QskIntervalF
{
    Q_GADGET

    Q_PROPERTY( qreal lowerBound READ lowerBound WRITE setLowerBound )
    Q_PROPERTY( qreal upperBound READ upperBound WRITE setUpperBound )
    Q_PROPERTY( qreal width READ width )

  public:
    constexpr QskIntervalF() noexcept = default;
    constexpr QskIntervalF( qreal lowerBound, qreal upperBound ) noexcept;

    void setInterval( qreal lowerBound, qreal upperBound ) noexcept;

    constexpr bool operator==( const QskIntervalF& ) const noexcept;
    constexpr bool operator!=( const QskIntervalF& ) const noexcept;

    constexpr qreal lowerBound() const noexcept;
    void setLowerBound( qreal ) noexcept;

    constexpr qreal upperBound() const noexcept;
    void setUpperBound( qreal ) noexcept;

    constexpr qreal width() const noexcept;
    void setWidth( qreal ) noexcept;

    constexpr bool contains( qreal value ) const noexcept;

    static constexpr QskIntervalF normalized( qreal value1, qreal value2 ) noexcept;

    void translate( qreal offset ) noexcept;
    constexpr QskIntervalF translated( qreal offset ) const noexcept;

    bool intersects( const QskIntervalF& ) const noexcept;
    QskIntervalF intersected( const QskIntervalF& ) const noexcept;

    void unite( const QskIntervalF& ) noexcept;
    QskIntervalF united( const QskIntervalF& ) const noexcept;

    void extend( qreal value ) noexcept;
    QskIntervalF extended( qreal value ) const noexcept;

    QskIntervalF operator|( const QskIntervalF& ) const noexcept;
    QskIntervalF operator&( const QskIntervalF& ) const noexcept;

    QskIntervalF& operator|=( const QskIntervalF& ) noexcept;
    QskIntervalF& operator&=( const QskIntervalF& ) noexcept;

    QskIntervalF operator|( qreal ) const noexcept;
    QskIntervalF& operator|=( qreal ) noexcept;

    constexpr bool isValid() const noexcept;
    constexpr bool isNull() const noexcept;

    void invalidate() noexcept;

  private:
    qreal m_lowerBound = 0.0;
    qreal m_upperBound = -1.0;
};

Q_DECLARE_TYPEINFO( QskIntervalF, Q_MOVABLE_TYPE );
Q_DECLARE_METATYPE( QskIntervalF )

QT_WARNING_PUSH
QT_WARNING_DISABLE_CLANG("-Wfloat-equal")
QT_WARNING_DISABLE_GCC("-Wfloat-equal")
QT_WARNING_DISABLE_INTEL(1572)

inline constexpr QskIntervalF::QskIntervalF( qreal lowerBound, qreal upperBound ) noexcept
    : m_lowerBound( lowerBound )
    , m_upperBound( upperBound )
{
}

inline void QskIntervalF::setInterval( qreal lowerBound, qreal upperBound ) noexcept
{
    m_lowerBound = lowerBound;
    m_upperBound = upperBound;
}

inline void QskIntervalF::setLowerBound( qreal value ) noexcept
{
    m_lowerBound = value;
}

inline void QskIntervalF::setUpperBound( qreal value ) noexcept
{
    m_upperBound = value;
}

inline constexpr qreal QskIntervalF::lowerBound() const noexcept
{
    return m_lowerBound;
}

inline constexpr qreal QskIntervalF::upperBound() const noexcept
{
    return m_upperBound;
}

inline constexpr qreal QskIntervalF::width() const noexcept
{
    return ( m_upperBound > m_lowerBound ) ? m_upperBound - m_upperBound : 0.0;
}

inline void QskIntervalF::setWidth( qreal width ) noexcept
{
    m_upperBound = m_lowerBound + width;
}

inline constexpr bool QskIntervalF::isValid() const noexcept
{
    return m_lowerBound <= m_upperBound;
}

inline constexpr bool QskIntervalF::isNull() const noexcept
{
    return m_lowerBound == m_upperBound;
}

inline void QskIntervalF::invalidate() noexcept
{
    m_lowerBound = 0.0;
    m_upperBound = -1.0;
}

inline constexpr bool QskIntervalF::contains( qreal value ) const noexcept
{
    return ( value >= m_lowerBound ) && ( value <= m_upperBound );
}

inline void QskIntervalF::translate( qreal offset ) noexcept
{
    m_lowerBound += offset;
    m_upperBound += offset;
}

inline constexpr QskIntervalF QskIntervalF::translated( qreal offset ) const noexcept
{
    return QskIntervalF( m_lowerBound + offset, m_upperBound + offset );
}

inline constexpr QskIntervalF QskIntervalF::normalized( qreal value1, qreal value2 ) noexcept
{
    return ( value1 < value2 ) ? QskIntervalF( value1, value2 ) : QskIntervalF( value2, value1 );
}

inline QskIntervalF QskIntervalF::operator&( const QskIntervalF& other ) const noexcept
{
    return intersected( other );
}

inline QskIntervalF QskIntervalF::operator|( const QskIntervalF& other ) const noexcept
{
    return united( other );
}

inline QskIntervalF& QskIntervalF::operator|=( const QskIntervalF& other ) noexcept
{
    unite( other );
    return *this;
}

inline QskIntervalF& QskIntervalF::operator&=( const QskIntervalF& other ) noexcept
{
    *this = intersected( other );
    return *this;
}

inline constexpr bool QskIntervalF::operator==( const QskIntervalF& other ) const noexcept
{
    return qFuzzyCompare( m_lowerBound, other.m_lowerBound ) &&
           qFuzzyCompare( m_upperBound, other.m_upperBound );
}

inline constexpr bool QskIntervalF::operator!=( const QskIntervalF& other ) const noexcept
{
    return ( !( *this == other ) );
}

inline QskIntervalF QskIntervalF::operator|( qreal value ) const noexcept
{
    return extended( value );
}

inline QskIntervalF& QskIntervalF::operator|=( qreal value ) noexcept
{
    *this = *this | value;
    return *this;
}

QT_WARNING_POP

#ifndef QT_NO_DEBUG_STREAM

class QDebug;
QSK_EXPORT QDebug operator<<( QDebug, const QskIntervalF& );
#endif

#endif
