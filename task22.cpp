#include <iostream>
#include <cstring>
#include <cassert>

using namespace std;

class String
{
private:
    char* m_buffer;
    size_t* m_refCounter;
    void DecrementCounter()
        {
            (*m_refCounter)--;
            if(*m_refCounter == 0)
            {
                delete []m_buffer;
                delete []m_refCounter;
                cout << "delete" << endl;
            }
        }
public:

    String() : m_buffer(nullptr), m_refCounter(new size_t(1))
    {
        cout << "String : "<< this <<endl;
    }

    String(const char* value) : m_buffer(new char[strlen(value)+1]), m_refCounter(new size_t(0))
    {
        cout << "String(St): "<< this <<endl;
        strcpy(m_buffer, value);
        (*m_refCounter)++;
    }

    String(const String& rhs) : m_buffer(rhs.m_buffer), m_refCounter(rhs.m_refCounter)
    {
        (*m_refCounter)++;
        cout << "String copy" << endl;
    }

    ~String()
    {
        cout << "~String : "<< this << endl;
        if (m_buffer)
        {
            DecrementCounter();
            m_buffer = nullptr;
            m_refCounter = nullptr;
        }
    }
// taken from the project 8 lines 60 - 89
    void swap(String& other)
    {
        std::swap(m_buffer, other.m_buffer);
        std::swap(m_refCounter, other.m_refCounter);
    }

    String& operator = (const String& rhs)
    {
        if (&rhs != this)
        {
            String tmp(rhs);
            swap(tmp);
        }
        return *this;
    }

    String& operator = (const char* value)
    {
        String(value).swap(*this);
        return *this;
    }

    const char& operator[](size_t index)
    {
        return m_buffer[index];
    }

    size_t count() const
    {
        return *m_refCounter;
    }

    void set_elem(size_t index, char value)
    {
        if (count()>1)
        {
            String tmp(m_buffer);
            std::swap(*this, tmp);
        }
        m_buffer[index] = value;
    }

    const char *GetString()const
    {
        return m_buffer;
    }
};

int main()
{
    String s("abc");
    assert(s.count()==1);
    {
        String s2 = s;
        assert(s.count()==2);
        assert(s2.count()==2);
    }
    assert(s.count()==1);
    String s3 = s;
    String s4 = "ass";
    assert(strcmp(s4.GetString(), "ass")==0);
    assert(s.count()==2);
    s3.set_elem(0, 'X');
    assert(s.count()==1);
    assert(s3.count()==1);
    assert(strcmp(s.GetString(), "abc")==0);
    assert(strcmp(s3.GetString(), "Xbc")==0);
    cout << "PASSED" << endl;
    return 0;
}