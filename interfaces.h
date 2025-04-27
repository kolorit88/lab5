
#include <iostream>
#include <unknwn.h>
#include <objbase.h>

using namespace std;

// Предварительное объявление идентификаторов интерфейса
extern const IID IID_IX;
extern const IID IID_IY;
extern const IID IID_IZ;
extern const IID IID_IUnknown1;

// Интерфейсы
interface IX : IUnknown {
    virtual void __stdcall Fx() = 0;
};

interface IY : IUnknown {
    virtual void __stdcall Fy() = 0;
};

interface IZ : IUnknown {
    virtual void __stdcall Fz() = 0;
};

// Компонент
class CA : public IX, public IY, public IZ {
    // Реализация методов класса IUnknown

    public:
        // Конструктор
        CA();

        // Деструктор
        ~CA();

    private:
        long m_cRef;

    ULONG __stdcall AddRef() override;

    ULONG __stdcall Release() override;

    HRESULT __stdcall QueryInterface(const IID &iid, void **ppv) override;

    void __stdcall Fx() override;

    void __stdcall Fy() override;

    void __stdcall Fz() override;


};

// Функция создания компонента
IUnknown *CreateInstance();