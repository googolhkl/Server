#ifndef SERVER_LIB_RAND_HPP
#define SERVER_LIB_RAND_HPP

#include <random>


namespace hkl {
// random,확률 관련 클래스
class rand {
    public:
        rand() {};
        ~rand() {};
        static long long MakeRangeNum(); //임의범위 난수 하나 발생
        static long long MakeRangeNum(const long long start,const long long end); //지정범위 난수 하나 발생
        static bool TrueOrFalse(int probability); // n%확률로 true 또는 or생성
        static bool TrueOrFalse(const double probability);
        static long long NumOfSuccess(const long long obj, const int    probability) throw(int);// 성공횟수 확률
        static long long NumOfSuccess(const long long obj, const double probability);
    private:
};
}

#endif
