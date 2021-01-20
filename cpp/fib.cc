#include <napi.h>

Napi::Value Main(const Napi::CallbackInfo &info) {
    Napi::Env env = info.Env();

    int i;
    double prev = 0, next = 1;

    // Napi::Number n = Napi::Number::New(env, info[0]);

    double n = info[0].As<Napi::Number>().Uint32Value();

    for(i = 0; i < n; i++) {
        next = next + prev;
        prev = next - prev;
    }

    Napi::Number result = Napi::Number::New(env, prev);

    return result;
}

Napi::Object Init(Napi::Env env, Napi::Object exports) {
    exports.Set(Napi::String::New(env, "fib"), Napi::Function::New(env, Main));
    return exports;
}

NODE_API_MODULE(fib, Init);