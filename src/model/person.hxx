#include<string>
#include<odb/core.hxx>

#pragma db object
class person
{
    public:
        person (const std::string& first, const std::string& last, unsigned short age);

        const std::string& first () const;
        const std::string& last () const;

        unsigned short age() const;

        void age (unsigned short);

    private:
        person() {}

        // below lines allow odb::access to access
        // private and protected members of this class
        friend class odb::access;

        #pragma db id auto
        unsigned long _id;

        std::string first_;
        std::string last_;
        unsigned short age_;
};
