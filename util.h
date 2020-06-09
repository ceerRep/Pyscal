#ifndef _UTIL_H
#define _UTIL_H

template <template <typename> typename target, typename... Args>
struct ExtractTemplateArgumentApply {
};

template <template <typename> typename target, typename first, typename... Args>
struct ExtractTemplateArgumentApply<target, first, Args...> {
    template <typename... Args1>
    static void process(Args1&&... args)
    {
        if (!target<first>()(args...))
            ExtractTemplateArgumentApply<target, Args...>::process(args...);
    }
};

template <template <typename> typename target>
struct ExtractTemplateArgumentApply<target> {
    template <typename... Args1>
    static void process(Args1&&... args) {}
};

template <typename, template <typename> typename>
struct ExtractTemplateArgument {
};

template <template <typename> typename T, typename... Args, template <typename> typename target>
struct ExtractTemplateArgument<T<Args...>, target> {
    template <typename... Args1>
    static void process(Args1&&... args)
    {
        ExtractTemplateArgumentApply<target, Args...>::process(args...);
    }
};

#endif
