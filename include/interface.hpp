#pragma once

#define DECLARE_CLASS_AS_INTERFACE(ClassName)                     \
public:                                                           \
    virtual ~ClassName() {}                                       \
                                                                  \
protected:                                                        \
    ClassName() {}                                                \
    ClassName(const ClassName &) {}                               \
    ClassName &operator=(const ClassName &) { return *this; }     \
    ClassName(ClassName &&) noexcept {}                           \
    ClassName &operator=(ClassName &&) noexcept { return *this; } \
                                                                  \
private:
