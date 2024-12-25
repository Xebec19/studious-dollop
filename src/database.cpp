// person.hxx

#include<string>

class person
{
    public:
        person(const std::string& first, const std::string& last, unsigned short age);

        const std::string& first () const;
        const std::string& last () const;

        unsigned short age() const;
        void age (unsigned short);

        // private
}
