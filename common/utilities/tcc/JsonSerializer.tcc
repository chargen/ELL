// JsonSerializer.tcc

#include <stdexcept>

using std::runtime_error;
using std::move;

namespace utilities
{
    template<typename KeyType, typename ValueType>
    void JsonSerializer::write(KeyType key, const ValueType& value, typename enable_if<is_class<ValueType>::value>::type* SFINAE)
    {
        try
        {
            JsonSerializer sub_serializer;
            value.Serialize(sub_serializer);
            _json_value[key] = sub_serializer._json_value;
        }
        catch (...)    // underlying json implementation may throw an exception 
        {
            throw runtime_error("jsoncpp threw an unspecified exception during write");
        }
    }

    template<typename KeyType>
    void JsonSerializer::write(KeyType key, const string& value)
    {
        try
        {
            _json_value[key] = value;
        }
        catch (...)    // underlying json implementation may throw an exception 
        {
            throw runtime_error("jsoncpp threw an unspecified exception during write");
        }
    }

    template<typename KeyType, typename ValueType>
    void JsonSerializer::write(KeyType key, const shared_ptr<ValueType>& ptr, typename enable_if<is_class<ValueType>::value>::type* SFINAE)
    {
        write(key, *ptr);
    }

    template<typename KeyType, typename ValueType>
    void JsonSerializer::write(KeyType key, const ValueType& value, typename enable_if<is_fundamental<ValueType>::value>::type* SFINAE)
    {
        try
        {
            _json_value[key] = value;
        }
        catch (...)    // underlying json implementation may throw an exception 
        {
            throw runtime_error("jsoncpp threw an unspecified exception during write");
        }
    }

    template<typename KeyType, typename ValueType>
    void JsonSerializer::write(KeyType key, const ValueType& value, typename enable_if<is_enum<ValueType>::value>::type* SFINAE)
    {
        try
        {
            _json_value[key] = (int)value;
        }
        catch (...)    // underlying json implementation may throw an exception 
        {
            throw runtime_error("jsoncpp threw an unspecified exception during write");
        }
    }

    template<typename KeyType, typename ValueType>
    void JsonSerializer::write(KeyType key, const vector<ValueType>& vec)
    {
        try
        {
            JsonSerializer sub_serializer;
            for (size_t i = 0; i < vec.size(); ++i)
            {
                sub_serializer.write((int)i, vec[i]);
            }
            _json_value[key] = sub_serializer._json_value;
        }
        catch (...)    // underlying json implementation may throw an exception 
        {
            throw runtime_error("jsoncpp threw an unspecified exception during write");
        }
    }

    template<typename KeyType, typename ValueType>
    void JsonSerializer::read(KeyType key, ValueType& value, typename enable_if<is_class<ValueType>::value>::type* SFINAE) const
    {
        try
        {    
            JsonSerializer sub_serializer;
            sub_serializer._json_value = _json_value[key];
            value.Deserialize(sub_serializer);
        }
        catch (...)    // underlying json implementation may throw an exception 
        {
            throw runtime_error("jsoncpp threw an unspecified exception during read");
        }
    }

    template<typename KeyType>
    void JsonSerializer::read(KeyType key, string& value) const
    {
        get(key, value);
    }

    template<typename KeyType, typename ValueType>
    void JsonSerializer::read(KeyType key, shared_ptr<ValueType>& ptr, typename enable_if<is_class<ValueType>::value>::type* SFINAE) const
    {
        try
        {
            JsonSerializer sub_serializer;
            sub_serializer._json_value = _json_value[key];
            Deserialize(sub_serializer, ptr);
        }
        catch (...)    // underlying json implementation may throw an exception 
        {
            throw runtime_error("jsoncpp threw an unspecified exception during read");
        }
    }

    template<typename KeyType, typename ValueType>
    void JsonSerializer::read(KeyType key, ValueType& value, typename enable_if<is_fundamental<ValueType>::value>::type* SFINAE) const
    {
        get(key, value);
    }

    template<typename ValueType, typename KeyType>
    ValueType JsonSerializer::read(KeyType key, typename enable_if<is_default_constructible<ValueType>::value>::type* SFINAE) const
    {
        ValueType val;
        get(key, val);
        return val;
    }

    template<typename KeyType, typename ValueType>
    void JsonSerializer::read(KeyType key, ValueType& value, typename enable_if<is_enum<ValueType>::value>::type* SFINAE) const
    {
        int ival;
        get(key, ival);
        value = (ValueType)ival;
    }

    template<typename ValueType, typename KeyType>
    ValueType JsonSerializer::read(KeyType key, typename enable_if<is_enum<ValueType>::value>::type* SFINAE) const
    {
        int val;
        get(key, val);
        return (ValueType)val;
    }

    template<typename KeyType, typename ValueType>
    void JsonSerializer::read(KeyType key, vector<ValueType>& vec) const
    {
        try
        {
            JsonSerializer sub_serializer;
            sub_serializer._json_value = _json_value[key];

            vec.clear();
            vec.reserve(sub_serializer._json_value.size());
            for (size_t i = 0; i < sub_serializer._json_value.size(); ++i)
            {
                ValueType val;
                sub_serializer.read((int)i, val);
                vec.push_back(move(val));
            }
        }
        catch (...)    // underlying json implementation may throw an exception 
        {
            throw runtime_error("jsoncpp threw an unspecified exception during read");
        }
    }

    template<typename KeyType>
    void JsonSerializer::get(KeyType key, bool& value) const
    {
        try
        {
            value = _json_value[key].asBool();
        }
        catch (...)    // underlying json implementation may throw an exception 
        {
            throw runtime_error("jsoncpp threw an unspecified exception during read");
        }
    }

    template<typename KeyType>
    void JsonSerializer::get(KeyType key, int& value) const
    {
        try
        {
            value = _json_value[key].asInt();
        }
        catch (...)    // underlying json implementation may throw an exception 
        {
            throw runtime_error("jsoncpp threw an unspecified exception during read");
        }
    }

    template<typename KeyType>
    void JsonSerializer::get(KeyType key, unsigned int& value) const
    {
        try
        {
            value = _json_value[key].asUInt();
        }
        catch (...)    // underlying json implementation may throw an exception 
        {
            throw runtime_error("jsoncpp threw an unspecified exception during read");
        }
    }

    template<typename KeyType>
    void JsonSerializer::get(KeyType key, float& value) const
    {
        try
        {
            value = _json_value[key].asFloat();
        }
        catch (...)    // underlying json implementation may throw an exception 
        {
            throw runtime_error("jsoncpp threw an unspecified exception during read");
        }
    }

    template<typename KeyType>
    void JsonSerializer::get(KeyType key, double& value) const
    {
        try
        {
            value = _json_value[key].asDouble();
        }
        catch (...)    // underlying json implementation may throw an exception 
        {
            throw runtime_error("jsoncpp threw an unspecified exception during read");
        }
    }

    template<typename KeyType>
    void JsonSerializer::get(KeyType key, string& value) const
    {
        try
        {
            value = _json_value[key].asString();
        }
        catch (...)    // underlying json implementation may throw an exception 
        {
            throw runtime_error("jsoncpp threw an unspecified exception during read");
        }
    }
}