#include <set>
#include <locale>
#include <iostream>

using namespace std;

struct ListItem
{
    int info;
    ListItem* next;
};

ListItem* listHead; // глобальные ссылочные переменные
ListItem* stackHead;

int CheckedInput(int begin, int end) // Ввод целочисленного значения с проверкой
{
    int choice;
    while (true)
    {
        cin >> choice;
        if (cin.fail())
        {
            cin.clear();
            cin.ignore(32767, '\n');
            cout << "Вводите данные корректно: ";
            continue;
        }
        cin.ignore(32767, '\n');
        if (choice < begin || choice > end)
        {
            cout << "Вводите данные корректно: ";
            continue;
        }
        break;
    }
    return choice;
}

int CheckedInput() // Ввод целочисленного значения с проверкой
{
    int choice;
    while (true)
    {
        cin >> choice;
        if (cin.fail())
        {
            cin.clear();
            cin.ignore(32767, '\n');
            cout << "Вводите данные корректно: ";
            continue;
        }
        cin.ignore(32767, '\n');
        break;
    }
    return choice;
}

void InitList(ListItem* head) // инициализация списка
{
    head->info = 0;
    head->next = NULL;
}

bool isEmpty(ListItem* head) // проверка списка на пустоту
{
    if (head->next == NULL)
    {
        return true;
    }
    return false;
}

void PrintList(ListItem* head) // вывод списка
{
    ListItem* current = head->next;
    while (current != NULL)
    {
        cout << current->info << " ";
        current = current->next;
    }
}

int Search(int infoToSearch) // поиск элемента по инфо-части
{
    int count = 1;
    ListItem* current = listHead->next;
    while (current != NULL)
    {
        if (current->info == infoToSearch)
        {
            return count;
        }
        current = current->next;
    }
    return -1;
}

void Add(int infoToAdd) // добавление элемента в пустой список 
{
    try
    {
        ListItem* newItem = new ListItem;
        newItem->next = NULL;
        newItem->info = infoToAdd;
        listHead->next = newItem;
    }
    catch (const std::exception&)
    {
        cout << "Список переполнен.";
    }
}

void Add(ListItem*& newItem,int infoToAdd, int indexToAdd, int whereToAdd) // добавление элемента в непустой список
{
    int count = 1;
    ListItem* previous = listHead;
    ListItem* current = listHead->next;
    while (count != indexToAdd && current != NULL)
    {
        previous = current;
        current = current->next;
        count++;
    }
    if (current == NULL)
    {
        cout << "Индекс выходит за пределы списка.";
    }
    else
    {
       ListItem* newItem = new ListItem;
       newItem->info = infoToAdd;
       if (whereToAdd == 0)
       {
           newItem->next = current;
           previous->next = newItem;
       }
       else
       {
           newItem->next = current->next;
           current->next = newItem;
       }
        
    }
}

void Delete(int indexToDelete) // удаление памяти
{
    int count = 1;
    ListItem* current = listHead->next;
    ListItem* previous = listHead;
    while (count != indexToDelete && current != NULL)
    {
        previous = current;
        current = current->next;
        count++;
    }
    if (current == NULL)
    {
        cout << "Индекс выходит за границу списка.";
    }
    else
    {
        previous->next = current->next;
        current->next = stackHead->next;
        stackHead->next = current;
    }
}

void DeleteAll(ListItem* head) // освобождение памяти
{
    ListItem* current = head;
    while (current != NULL)
    {
        current = head;
        head = head->next;
        delete current;
        current = head;
    }
}

void CallMenu() // меню
{
    bool work = true;
    int choice;
    while (work)
    {
        cout << "Выбор действия:\n1 - Вывод списка\n2 - Поиск элемента с заданной информационной частью\n3 - Добавление элемента\n";
        cout << "4 - Удаление заданного элемента\n5 - Вывод вспомогательного списка\n6 - Завершить работу\n";
        cout << "Действие: "; choice = CheckedInput(1, 6);
        switch (choice)
        {
        case 1:
            if (isEmpty(listHead))
            {
                cout << "Список пустой.";
            }
            else
            {
                cout << "Список: "; PrintList(listHead);
            }
            cout << "\n\n";
            break;
        case 2:
            int elemsIndex, elemsInfo;
            cout << "Введите информационную часть, индекс которой надо найти: "; elemsInfo = CheckedInput();
            elemsIndex = Search(elemsInfo);
            if (elemsIndex == -1)
            {
                cout << "Такого элемента в списке нет.";
            }
            else
            {
                cout << "Элемент " << elemsIndex << "-ый в списке.";
            }
            cout << "\n\n";
            break;
        case 3:
            int elemToAdd, indexToAdd, whereToAdd;
            try
            {
                ListItem* newItem = new ListItem;
                cout << "Введите элемент, который хотели бы добавить: "; elemToAdd = CheckedInput();
                if (isEmpty(listHead))
                {
                    Add(elemToAdd);
                    cout << "\n\n";
                    break;
                }
                cout << "Введите номер элемента, перед (после) которым хотели бы добавить: "; indexToAdd = CheckedInput();
                cout << "Добавление перед (0) или после (1): "; whereToAdd = CheckedInput(0, 1);
                Add(newItem,elemToAdd, indexToAdd, whereToAdd);
                cout << "\n\n";
                break;
            }
            catch (const std::exception&)
            {
                cout <<"Список заполнен. Места нет."<< "\n\n";
            }
        case 4:
            if (isEmpty(listHead))
            {
                cout << "Список пустой. Удалять нечего\n\n";
                break;
            }
            cout << "Введите индекс удаляемого элемента: "; Delete(CheckedInput());
            cout << "\n\n";
            break;
        case 5:
            if (isEmpty(stackHead))
            {
                cout << "Вспомогательный список пустой.";
            }
            else
            {
                cout << "Вспомогательный список: "; PrintList(stackHead);
            }
            cout << "\n\n";
            break;
        case 6:
            work = false;
            DeleteAll(listHead); DeleteAll(stackHead);
            break;
        default:
            break;
        }
    }
}

int main()
{
    setlocale(LC_ALL, "RUS");
    listHead = new ListItem; stackHead = new ListItem;
    InitList(listHead); InitList(stackHead);
    CallMenu();
}
