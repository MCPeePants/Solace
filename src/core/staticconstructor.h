#ifndef SLC_CORE_STATICCONSTRUCTOR_H
#define SLC_CORE_STATICCONSTRUCTOR_H

class StaticConstructor
{
    public:
    StaticConstructor(void (*f)())
    {
        f();
    }
};

#define STATIC_INIT() \
    void _static_Init(); \
    StaticConstructor _staticConstructor(_static_Init);\
    void _static_Init()

#endif
