#include "xpStackTrace.h"
#include <map>

namespace Nu {

    template<typename Type>
        struct Alpha
        {
                struct Beta
                        {
                                void func() {
                                            printStackTrace();
                                                }
                                    void func(Type) {
                                                printStackTrace();
                                                    }
                                        };
        };

    struct Gamma
    {
            template <int N>
                    void unroll(double d) {
                            unroll<N-1>(d);
                                }
    };

    template<>
        void Gamma::unroll<0>(double) {
                printStackTrace();
        }

} // namespace Nu

int main()
{
        Nu::Alpha<int>::Beta().func(42);
            Nu::Alpha<char*>::Beta().func("42");
                Nu::Alpha< Nu::Alpha< std::map<int, double> > >::Beta().func();
                    Nu::Gamma().unroll<5>(42.0);
}
