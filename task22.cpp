﻿#include <iostream>
#include <cstring>
#include <cassert>

using namespace std;

class String
{
private:
    char* m_buffer;
    size_t* m_refCounter;
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
        (*m_refCounter)--;

        if(*m_refCounter == 0)
        {
            if (m_buffer)
            {
                delete[] m_buffer;
                delete[] m_refCounter;
                m_buffer = nullptr;
                m_refCounter = nullptr;
                cout << "delete[] + nullptr" << endl;
            }
        }
    }

    String& operator = (const String& rhs)
    {
        (*m_refCounter)--;
        if(*m_refCounter == 0)
        {
            delete[] m_buffer;
            delete[] m_refCounter;
            cout << "delete[]" << endl;
        }
        m_buffer = rhs.m_buffer;
        m_refCounter = rhs.m_refCounter;
        (*m_refCounter)++;
        return *this;
    }

    String& operator = (const char* value)
    {
        (*m_refCounter)--;
        if(*m_refCounter == 0)
        {
            delete[] m_buffer;
            delete[] m_refCounter;
            cout << "delete[]" << endl;
        }
        m_refCounter = new size_t(1);
        m_buffer = new char[strlen(value) + 1];
        strcpy(m_buffer, value);
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
        (*m_refCounter)--;
        if(*m_refCounter == 0)
        {
            delete[] m_buffer;
            delete[] m_refCounter;
            cout << "delete[]" << endl;
        }
        m_refCounter = new size_t(1);
        char *temp = new char[strlen(m_buffer) + 1];
        strcpy(temp, m_buffer);
        m_buffer = temp;
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
    assert(s.count()==2);
    s3.set_elem(0, 'X');
    assert(s.count()==1);
    assert(s3.count()==1);
    cout << "PASSED" << endl;
    return 0;
}