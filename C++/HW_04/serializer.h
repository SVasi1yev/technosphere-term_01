#pragma once
#include <iostream>
#include <string>
#include <type_traits>

enum class Error {
    NoError,
    CorruptedArchive
};

class Serializer {
    static constexpr char Separator = ' ';
public:
    explicit Serializer(std::ostream& out)
        : out_(out) {}

    template<class T>
    Error save(T& object) {
        return object.serialize(*this);
    }

    template<class... ArgsT>
    Error operator()(ArgsT&&... args) {
        return process(std::forward<ArgsT>(args)...);
    }
private:
    std::ostream& out_;

    template<class T>
    Error print(T& elem) {
        if(std::is_same<T, bool>::value) {
            out_ << (elem ? "true" : "false") << Separator;
        } else if(std::is_same<T, uint64_t>::value) {
            out_ << elem << Separator;
        } else {
            return Error::CorruptedArchive;
        }
        return Error::NoError;
    }

    template<class T>
    Error process(T&& elem) {
        if(print(elem) == Error::CorruptedArchive) {
            return Error::CorruptedArchive;
        }
        return Error::NoError;
    }

    template<class T, class... ArgsT>
    Error process(T&& elem, ArgsT&&... args) {
        if(print(elem) == Error::CorruptedArchive) {
            return Error::CorruptedArchive;
        }
        return process(std::forward<ArgsT>(args)...);
    }
};

class Deserializer {
    static constexpr char Separator = ' ';
public:
    explicit Deserializer(std::istream& in)
        : in_(in) {}

    template<class T>
    Error load(T& object) {
        return object.serialize(*this);
    }

    template<class... ArgsT>
    Error operator()(ArgsT&&... args) {
        return process(std::forward<ArgsT>(args)...);
    }
private:
    std::istream& in_;

    template<class T>
    Error read(T& elem) {
        std::string text;
        in_ >> text;
        if(std::is_same<T, bool>::value) {
            if(text == "true" || text == "false") {
                elem = (text == "true" ? true : false);
            } else {
                return Error::CorruptedArchive;
            }
        } else if(std::is_same<T, uint64_t>::value) {
            if(text == "") { 
                return Error::CorruptedArchive; 
            }
            if(text[0] < '1' || text[0] > '9') { 
                return Error::CorruptedArchive;
            }
            for(auto c : text) {
                if(c < '0' || c > '9') {
                    return Error::CorruptedArchive;
                }
            }
            elem = atoi(text.c_str());
        } else {
            return Error::CorruptedArchive;
        }
        return Error::NoError;
    }

    template<class T>
    Error process(T&& elem) {
        if(read(elem) == Error::CorruptedArchive) {
            return Error::CorruptedArchive;
        }
        return Error::NoError;
    }

    template<class T, class... ArgsT>
    Error process(T&& elem, ArgsT&&... args) {
        if(read(elem) == Error::CorruptedArchive) {
            return Error::CorruptedArchive;
        }
        return process(std::forward<ArgsT>(args)...);
    }
};