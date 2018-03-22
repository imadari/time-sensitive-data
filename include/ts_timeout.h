#ifndef TS_EXPIRE_H
#define TS_EXPIRE_H

#include <chrono>

using namespace std::chrono;

namespace tsd
{
    template <typename T>
    class Expire
    {
        public:
            /**
             * Initializes the Expire structure from ::now() with t_duration
             * @param t_duration 
             */
            Expire<T>(duration<int, T> t_duration)
            {
                Reset(t_duration);
            };

            /**
             * Resets the start time point, doesn't touch the duration
             */
            void Reset()
            {
                m_startPoint = steady_clock::now();
                m_endPoint = m_startPoint + m_duration;
            };

            /**
             * Resets the start point and the duration
             * @param timeout
             */
            void Reset(duration<int, T> t_duration)
            {
                m_duration = t_duration;
                Reset();
            };

            /**
             * If ::now()>_endPoint
             * @return true, if the endTimePoint passed
             */
            bool IsTimeout()
            {
                auto now = steady_clock::now();
                return now > m_endPoint;
            }

            steady_clock::time_point GetEndTimePoint()
            {
                return m_endPoint;
            }

            ~Expire() = default;

        private:

            // Expiration is calculated from
            steady_clock::time_point m_startPoint; 
            
            // Expires in
            duration<int, T> m_duration;

            // Expires at
            steady_clock::time_point m_endPoint;    
    };
}

#endif //TS_TIMEOUT_H