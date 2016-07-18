#ifndef RAE_ANIMATOR_HPP
#define RAE_ANIMATOR_HPP

#include <math.h>
#include <glm/glm.hpp>

#include "core/Utils.hpp"

namespace Rae
{

enum class AnimatorType
{
    SINE_IN,
    SINE_OUT,
    SINE_IN_OUT,
    CUBIC_IN,
    CUBIC_OUT,
    CUBIC_IN_OUT
};

template<typename T> inline bool isCloseEnough(const T& target, const T& value)
{
    if( target - value == static_cast<T>(0.0) ) // Maybe this doesn't work with doubles.
        return true;
    return false;
}

template<> inline bool isCloseEnough<float>(const float& target, const float& value)
{
    if( std::abs(target - value) < 0.00001f )
        return true;
    return false;
}

template<> inline bool isCloseEnough<glm::vec3>(const glm::vec3& target, const glm::vec3& value)
{
    glm::vec3 temp = target - value;
    float lengthSqr = glm::dot(temp, temp);
    //if( (target - value).lengthSqr() < 0.00001f )
    if( lengthSqr < 0.00001f )
        return true;
    return false;
}

template <typename T>
class Animator
{
public:
    
    Animator()
        : m_value(),
        m_startValue(),
        m_valueChange(),
        m_startTime(0.0f),
        m_duration(0.0f),
        m_animatorType(AnimatorType::SINE_IN_OUT)
    {
    }

    ~Animator(){}

    T sineEaseIn(float time, T startValue, T valueChange, float duration)
    {
        return -valueChange * cosf(time / duration * Math::QUARTER_TAU) + valueChange + startValue;
    }

    T sineEaseOut(float time, T startValue, T valueChange, float duration)
    {
        return valueChange * sinf(time / duration * Math::QUARTER_TAU) + startValue;
    }

    T sineEaseInOut(float time, T startValue, T valueChange, float duration)
    {
        return -valueChange / 2.0f * (cosf(Math::PI * time / duration) - 1.0f) + startValue;
    }

    T cubicEaseIn(float time, T startValue, T valueChange, float duration)
    {
        time /= duration;
        return valueChange * time * time * time + startValue;
    }

    T cubicEaseOut(float time, T startValue, T valueChange, float duration)
    {
        time = (time / duration) - 1.0f;
        return valueChange * (time * time * time + 1.0f) + startValue;
    }

    T cubicEaseInOut(float time, T startValue, T valueChange, float duration)
    {
        time /= duration / 2.0f;
        if(time < 1.0f)
            return valueChange / 2.0f * time * time * time + startValue;
        time -= 2.0f;
        return valueChange / 2.0f * (time * time * time + 2.0f) + startValue;
    }

    void init(T startValue, T targetValue, float startTime, float duration, AnimatorType setType = AnimatorType::SINE_IN_OUT )
    {
        m_value = startValue;
        m_startValue = startValue;
        m_valueChange = targetValue - startValue;
        m_startTime = startTime;
        m_duration = duration;
        if(m_duration == 0.0f)
            m_duration = 5.0f;
        m_animatorType = setType;
    }

    // A deferred init, which can be used to init without knowing the startTime. update() will finish initing.
    void init(T startValue, T targetValue, float duration, AnimatorType setType = AnimatorType::SINE_IN_OUT )
    {
        m_value = startValue;
        m_startValue = startValue;
        m_valueChange = targetValue - startValue;
        m_startTime = -5.0f; // Unknown at this point, so we set it to a magic value -5.0f.
        m_duration = duration;
        if(m_duration == 0.0f)
            m_duration = 5.0f;
        m_animatorType = setType;
    }

    // returns true if the Animator is still running.
    bool update(float currentTime)
    {
        if( m_startTime == -5.0f )
        {
            // Finalize the deferred init.
            m_startTime = currentTime;
        }

        if( m_duration == 0.0f )
            return false;

        // Clamp to targetValue if we are finished
        if( isFinished(currentTime) )
        {
            finish( targetValue() );
            return true; // Return true one more time, so that the value is updated to target.
        }
        
        switch(m_animatorType)
        {
            case AnimatorType::SINE_IN:
                m_value = sineEaseIn(currentTime - m_startTime, m_startValue, m_valueChange, m_duration);
                break;
            case AnimatorType::SINE_OUT:
                m_value = sineEaseOut(currentTime - m_startTime, m_startValue, m_valueChange, m_duration);
                break;
            default:
            case AnimatorType::SINE_IN_OUT:
                m_value = sineEaseInOut(currentTime - m_startTime, m_startValue, m_valueChange, m_duration);
                break;
            case AnimatorType::CUBIC_IN:
                m_value = cubicEaseIn(currentTime - m_startTime, m_startValue, m_valueChange, m_duration);
                break;
            case AnimatorType::CUBIC_OUT:
                m_value = cubicEaseOut(currentTime - m_startTime, m_startValue, m_valueChange, m_duration);
                break;
            case AnimatorType::CUBIC_IN_OUT:
                m_value = cubicEaseInOut(currentTime - m_startTime, m_startValue, m_valueChange, m_duration);
                break;
        }

        return true;
    }

    void finish(T set)
    {
        m_value = set;
        m_valueChange = set;
        m_duration = 0.0f;
    }
 
    bool isFinished(float currentTime)
    {
        // First check if target is reached, then check if time has ended.
        if( isCloseEnough<T>(targetValue(), m_value) )
            return true;
        return hasTimeEnded(currentTime);
    }

    bool hasTimeEnded(float currentTime)
    {
        if( currentTime > endTime() )
            return true;
        return false;
    }
    
    const T& value() { return m_value; }
    const T& startValue() { return m_startValue; }
    T targetValue() { return m_startValue + m_valueChange; }
    void  setTargetValue(T targetValue) { m_valueChange = targetValue - m_startValue; }
    const T& valueChange() { return m_valueChange; }
    float duration() { return m_duration; }
    float endTime() { return m_startTime + m_duration; }

private:
    T m_value;

    T m_startValue;
    T m_valueChange; // targetValue - startValue
    float m_startTime;
    float m_duration;

    AnimatorType m_animatorType;
};

}

#endif

