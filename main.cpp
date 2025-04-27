
#include <iostream>
#include <unknwn.h>
#include <objbase.h>
#include <cassert>

#include "interfaces.h"

using namespace std;

int main () {
    SetConsoleOutputCP(CP_UTF8);
    cout << "Hello, world!" << endl;

    HRESULT hr;

    cout << "Клиент: получить указатель на IUnknown" << endl;
    IUnknown* pIUnknown = CreateInstance();

    cout << "\nКлиент: получить указатель на IX" << endl;
    // Определяем указатель на интерфейс
    IX* pIX = NULL;
    // Запрашиваем интерфейс IX
    hr = pIUnknown->QueryInterface(IID_IX, (void**)&pIX);
    if (SUCCEEDED(hr)) {
        cout << "Клиент: указатель на IX успешно получен" << endl;
        pIX->Fx(); // Использовать интерфейс IX
    };

    cout << "\nКлиент: получить указатель на IY" << endl;
    IY* pIY = NULL;
    hr = pIUnknown->QueryInterface(IID_IY, (void**)&pIY);
    if (SUCCEEDED(hr)) {
        cout << "Клиент: указатель на IY успешно получен" << endl;
        pIY->Fy(); // Использовать интерфейс IY
    };

    cout << "\nКлиент: получил неподдерживаемый интерфейс" << endl;
    IZ* pIZ = NULL;
    hr = pIUnknown->QueryInterface(IID_IZ, (void**)&pIZ);

    if(SUCCEEDED(hr)) {
        cout << "Клиент: интерфейс IZ успешно получен" << endl;
    } else {
        cout << "Клиент: Не удается получить доступ к интерфейсу IZ" << endl;
    };

    cout << "\nКлиент: получить указатель на IY через IX" << endl;
    IY* pIYfromIX = NULL;
    hr = pIX->QueryInterface(IID_IY, (void**)&pIYfromIX);
    if(SUCCEEDED(hr)) {
        cout<< "Клиент: указатель на IY успешно получен" << endl;
        pIYfromIX->Fy();
    } else {
        cout << "Клиент: невозможно получить указатель на IY через IX" << endl;
    }
    // -------------------------------------------------------------------------------

    cout << "\n1) Вы всегда получаете один и тот же IUnknown\n" << endl;
    IUnknown* pI1 = NULL;
    IUnknown* pI2 = NULL;

    pIX->QueryInterface(IID_IUnknown1, (void**)&pI1);
    pIY->QueryInterface(IID_IUnknown1, (void**)&pI2);

    if(pI1 == pI2){
        cout<<"Это один и тот же элемент IUnknown!"<<endl;
    }
    pI1->Release();
    pI2->Release();

    cout << "\n2) Вы можете получить интерфейс снова, если смогли получить его раньше\n" << endl;
    HRESULT hr2 = pIUnknown->QueryInterface(IID_IX, (void**)&pIX);

    if (SUCCEEDED(hr2)){
        cout<<"Интерфейс IX снова успешно получен"<<endl;
    }
    pIX->Release();

    cout << "\n3) Вы можете снова получить интерфейс, который у Вас уже есть\n" << endl;
    IX* pIX2 = NULL;
    HRESULT hr3 = pIX->QueryInterface(IID_IX, (void**)&pIX2);
    assert(SUCCEEDED(hr3));

    pIX2->Release();

    cout << "\n4) Вы всегда можете вернуться туда, откуда начали\n" << endl;

    // Получить IY через IX
    hr = pIX->QueryInterface(IID_IY, (void**)&pIY);
    if (SUCCEEDED(hr)) {
        // Получить IX через IY
        hr = pIY->QueryInterface(IID_IX, (void**)&pIX2);

        assert(SUCCEEDED(hr));
    }
    pIY->Release();
    pIX2->Release();

    cout << "\n5) Если Вы смогли попасть куда-то хоть откуда-нибудь, Вы можете попасть туда откуда угодно\n" << endl;

    // Запросить IY у IX
    hr = pIX->QueryInterface(IID_IY, (void**)&pIY);

    if (SUCCEEDED(hr)) {
        pIY->Release();

        // Запросить IZ у IY
        hr = pIY->QueryInterface(IID_IZ, (void**)&pIZ);
        pIZ->Release();
        if (SUCCEEDED(hr)) {
            // Запросить IZ у IX
            hr = pIX->QueryInterface(IID_IZ, (void**)&pIZ);

            assert(SUCCEEDED(hr));
        }
    }
    // -----------------------------------------------------------------------------------

    pIX->Release();
    pIY->Release();
    pIZ->Release();
    pIX2->Release();
    pIUnknown->Release();

    return 0;
};