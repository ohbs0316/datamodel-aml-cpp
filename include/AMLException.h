#ifndef AML_EXCEPTION_H_
#define AML_EXCEPTION_H_

#include <stdexcept>
#include <string>

typedef enum 
{
    AML_RESULT_OK = 0,

    AML_INVALID_PARAM = 100,
    AML_INVALID_FILE_PATH,
    AML_INVALID_SCHEMA,
    AML_INVALID_XML_STR,
    AML_INVALID_AML_FORMAT,
    AML_NOT_IMPL,               // @TODO: need to be specified more
    AML_NO_MEMORY,
    
    AML_OBJECT_INVALID_KEY,
    AML_OBJECT_KEY_DUP,

    AML_DATA_INVALID_KEY,
    AML_KEY_VALUE_NOT_MATCH,

    AML_ERROR = 255

} AMLResult;

namespace Exception 
{
    static const char NO_ERROR[]                    = "No Error";

    static const char INVALID_PARAM[]               = "Invalid Parameter";
    static const char INVALID_FILE_PATH[]           = "Invalid File Path";
    static const char INVALID_SCHEMA[]              = "Invalid AutomationML Schema File";
    static const char INVALID_XML_STR[]             = "Invalid XML Style String";
    static const char INVALID_AML_FORMAT[]          = "Invalid AML format";
    static const char NOT_IMPL[]                    = "Not Implemented";
    static const char NO_MEMORY[]                   = "No Momory";
    
    static const char OBJECT_INVALID_KEY[]          = "Invalid AMLObject Data Key";
    static const char OBJECT_KEY_DUP[]              = "Duplicated AMLObject Data Key";
    static const char DATA_INVALID_KEY[]            = "Invalid AMLData Data Key";
    static const char KEY_VALUE_NOT_MATCH[]         = "Not Matching AMLData Key and Value";

    static const char UNKNOWN_ERROR[]               = "Unknown Error";
}

class AMLException : public std::runtime_error
{
    public:
        AMLException(const std::string& msg, AMLResult reason = AML_ERROR)
        : std::runtime_error(msg), m_reason(reason) {}

        static std::string reason(const AMLResult res);

        std::string reason() const
        {
            return reason(m_reason);
        }

        AMLResult code() const
        {
            return m_reason;
        }

    private:
        AMLResult m_reason;
};

#endif // AML_EXCEPTION_H_
