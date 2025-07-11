#ifndef MACROS_H
#define MACROS_H

#include <QObject>

#define PROPERTY_DEFINITION(_name_, _type_) \
private: \
    Q_PROPERTY(_type_ _name_ MEMBER _name_ WRITE set_##_name_ NOTIFY _name_##Changed FINAL) \
public: \
    _type_ _name_; \
    void set_##_name_(_type_ value); \
    Q_SIGNAL void _name_##Changed(_type_);

#define PROPERTY_IMPLEMENTATION(_class_, _name_, _type_) \
    void _class_::set_##_name_(_type_ __value) \
    { \
        if (_name_ != __value) { \
            _name_ = __value; \
            emit _name_##Changed(__value); \
        } \
    }

#define CONST_PROPERTY_DEFINITION(_name_, _type_) \
private: \
    Q_PROPERTY(_type_ _name_ MEMBER _name_ CONSTANT FINAL) \
public: \
    _type_ _name_;

#endif // MACROS_H