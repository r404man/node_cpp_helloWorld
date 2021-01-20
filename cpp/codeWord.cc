#include <napi.h>
#include <string>

class CodeWord
{
public:
    char myKey[26] = {'a', 'b', 'c', 'd', 'e', 'f', 'g',
                      'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's',
                      't', 'u', 'v', 'w', 'x', 'y', 'z'};
    Napi::String code(Napi::String word, int cryptStep);
    Napi::String decode(Napi::String word, int cryptStep);
};

Napi::String CodeWord::code(Napi::String word, int cryptStep)
{
    Napi::Env env = word.Env();

    CodeWord myCode;

    std::string mystr = word.ToString();

    std::string cryptWord = "";

    for (int i = 0; i < mystr.length(); i++)
    {
        for (int j = 0; j < 26; j++)
        {
            if (mystr[i] == myCode.myKey[j])
            {
                if ((j + cryptStep) > 26)
                {
                    cryptWord += myCode.myKey[(j + cryptStep) - 26];
                }
                else
                {
                    cryptWord += myCode.myKey[j + cryptStep];
                }
            }
            else
            {
                continue;
            }
        }
    }

    return Napi::String::New(env, cryptWord);
}

Napi::String CodeWord::decode(Napi::String word, int cryptStep)
{
    Napi::Env env = word.Env();

    CodeWord myCode;

    std::string mystr = word.ToString();
    std::string decryptWord = "";

    for (int i = 0; i < mystr.length(); i++)
    {
        for (int j = 0; j < 26; j++)
        {
            if (mystr[i] == myCode.myKey[j])
            {
                if ((j - cryptStep) < 0)
                {
                    decryptWord += myCode.myKey[(j - cryptStep) + 26];
                    break;
                }
                else
                {
                    decryptWord += myCode.myKey[j - cryptStep];
                }
            }
            else
            {
                continue;
            }
        }
    }

    return Napi::String::New(env, decryptWord);
}

Napi::Value Main(const Napi::CallbackInfo &info)
{
    Napi::Env env = info.Env();

    CodeWord myCode;

    //@desk Code params initialize
    int n;
    Napi::String myStr = Napi::String::String(env, info[0]);

    if (info.Length() < 2)
    {
        n = 2;
    }
    else
    {
        n = Napi::Number(env, info[1]);
    }

    return myCode.code(myStr, n);
}

Napi::Value Decode(const Napi::CallbackInfo &info)
{
    Napi::Env env = info.Env();

    CodeWord myCode;

    //@desk Code params initialize
    int n;
    Napi::String myStr = Napi::String::String(env, info[0]);

    if (info.Length() < 2)
    {
        n = 2;
    }
    else
    {
        n = Napi::Number(env, info[1]);
    }

    return myCode.decode(myStr, n);
}

Napi::Object Init(Napi::Env env, Napi::Object exports)
{
    exports.Set(Napi::String::New(env, "codeWord"), Napi::Function::New(env, Main));
    exports.Set(Napi::String::New(env, "decodeWord"), Napi::Function::New(env, Decode));
    return exports;
}

NODE_API_MODULE(codeWord, Init);
