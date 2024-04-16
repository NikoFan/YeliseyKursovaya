#include <iostream>
#include <cstdlib> // для system
#include<windows.h>  
#include<unistd.h>  
#include <conio.h>
#include <map>
using namespace std;



class ShowProducts
{
    public:
        // Словрь с продуктами
        map<string, string> productsDict
        {
            pair<string, string>{"00", "Cola"}, pair<string, string>{"30", "Red Buls"},
            pair<string, string>{"01", "Schweppes"}, pair<string, string>{"31", "Dr Pepper"},
            pair<string, string>{"02", "Fanta"}, pair<string, string>{"32", "Sprite"},
            pair<string, string>{"03", "Cola Dobriy"}, pair<string, string>{"33", "Pepsi"}, 
            pair<string, string>{"04", "Cola ChernoGolovka"}, pair<string, string>{"34", "Mountain Dew"}, 
            pair<string, string>{"10", "Lays"}, pair<string, string>{"40", "7up"}, 
            pair<string, string>{"11", "Lays crab"}, pair<string, string>{"41", "Herr's"}, 
            pair<string, string>{"12", "Snacks"}, pair<string, string>{"42", "Terra"}, 
            pair<string, string>{"13", "Nuts"}, pair<string, string>{"43", "Popchips"}, 
            pair<string, string>{"14", "Water"}, pair<string, string>{"44", "Fritos"}, 
            pair<string, string>{"20", "Cold Water"}, pair<string, string>{"50", "Sandwiches"}, 
            pair<string, string>{"21", "Rollton"}, pair<string, string>{"51", "Meat Sandwiches"}, 
            pair<string, string>{"22", "Doshirak"}, pair<string, string>{"52", "Candies"}, 
            pair<string, string>{"23", "Doshirak meat"}, pair<string, string>{"53", "Skittles"}, 
            pair<string, string>{"24", "Chips"}, pair<string, string>{"54", "Beer"}, 
        };

        void show(string productNumber)
        {
            system("cls");
            char keyPress;
            cout << "\tPRODUCT\n\n";
            cout << "Product name: " << productsDict[productNumber] << endl << endl;

            cout << "Press key to go out!";
            cout << "\n>> ";
            // Приниаем нажатие пользователя
            keyPress = getch();
            cout << "Go out\n";
            sleep(2);

        }
};

class Payment
{
    public:
        int pay(string productName)
        {
            system("cls");
            ShowProducts showProductsObj;
            double userMoney;
            cout << "\tPAY\n";
            cout << "Go out: input '0'!\n";
            cout << "product:\t" << showProductsObj.productsDict[productName] << endl;
            cout << "cost   :\t100p.\n";
            cout << "money  :\t";
            cin >> userMoney;
            if (userMoney - 100 >= 0)
            {
                cout << "Good!\nBalance:\t" << userMoney - 100 << endl;
                return 1;
            } else if(userMoney == 0)
            {
                cout << "Stop Payment!\n";
                return 1;
            }
            cout << "Badly!\nPay more!\n";
            return 0;
        }
    
};

class DisplayProgram
{
    
    public:
        int checkToPayment = 0;
        int checkProductShow = 0;
        string productRows[6][5];
        int x = 0,
            y = 0; // x: Номер строки; y: Номер колонки
        string borderStroke = "------------------------";
        // Метод создания интерфейса
        void display()
        {
            system("cls");
            ShowProducts showProductsObj;
            cout << "|" << borderStroke << "|" << endl;
            cout << "|====VENDING  MACHINE====|" << endl;
            cout << "|" << borderStroke << "|" << endl;
            // Цикл для создания *интерфейса приложения*
            for(int stroke = 0; stroke < 10; stroke++) 
            {
                if (stroke <= 5)
                {
                    // Цикл для заполнения массива товаров
                    for(int productId = 0; productId < 5; productId++) 
                    {
                        // Заполнение массива товарами
                        if(stroke == y && productId == x)
                            productRows[stroke][productId] = productConverter(1,
                                stroke, productId);
                        else
                            productRows[stroke][productId] = productConverter(0,
                                stroke, productId);

                        


                        if (productId < 5)
                            cout << "-";
                        cout << productRows[stroke][productId];
                    }
                    cout << "-";
                    switch (stroke)
                    {
                        case (2):
                            cout << "/----------\\\n";
                            break;
                        case (3):
                            cout << "| "<<showProductsObj.productsDict[productRows[y][x].substr(1, 2)]<<" | "<<"\n";
                            break;
                        case (4):
                            cout << "\\----------/\n";
                            break;
                        default:
                            cout << "\n";
                            break;

                    }
                    
                } else if (stroke == 6)
                {
                    cout << "|" << borderStroke << "|" << endl;
                } else if (stroke > 6 && stroke < 9)
                {
                    cout << "|[" << "                      " << "]|\n";
                } else
                {
                    cout << "|" << borderStroke << "|" << endl;
                }

            }
            // Если была команда начать оплату
            startPayment: // Оператор goto к которому возвращаемся при омене оплаты
            if (checkToPayment != 0)
            {
                // Хранит в себе решение по оплате
                int returnPaymentAnswer;
                // Вызов класса оплаты
                Payment paymentProcess;
                // Вызов метода оплаты и передача туда названия товара
                returnPaymentAnswer = paymentProcess.pay(productRows[y][x].substr(1, 2));
                sleep(2);
                // Если оплата прошла успешно
                if (returnPaymentAnswer == 1)
                {
                    checkToPayment = 0;
                    
                }
                // Если возникла ошибка при оплате возвращаемся и делаем все заново
                else
                    goto startPayment;
            }

            if (checkProductShow != 0)
            {
                ShowProducts showProducts;
                showProducts.show(productRows[y][x].substr(1, 2));
                checkProductShow = 0;
                display();
            }
            // Вывод правил работы с программой
            actions();
        }
        // Метод конвертации чисел в строку
        string productConverter(int productType, int strokeValue, int productIdValue)
        {
            if (productType == 1)
            {
                string product = "<";
                        product += to_string(strokeValue);
                        product += to_string(productIdValue);
                        product += ">";
                return product;
            } 
            
            string product = "[";
                        product += to_string(strokeValue);
                        product += to_string(productIdValue);
                        product += "]";
            return product;
        }

        // Метод обработки действий пользователя
        void actions()
        {
            ShowProducts showProductsObj;
            char keyPress;
            cout << "\nRules\n";
            cout << "Move:\n";
            cout << " -Down Arrow\n -Up Arrow\n -Right Arrow\n -Left Arrow\n";
            cout << "Actions:\n";
            cout << " -Space : Choose\n -Backspace : Pay\n -Escape : Close application\n -Enter : View purchased products";
            cout << "\nEnter your action: ";
            // Приниаем нажатие пользователя
            keyPress = getch();

            
            switch(keyPress)
            {
                // esc
                case(27):
                    cout << "Exit\n";
                    sleep(2);
                    // Выход из программы
                    exit(0); 
                    break;
                // enter
                case(13):
                    cout << "View products\n";
                    sleep(2);
                    checkProductShow = 1;
                    break;
                // space
                case(32):
                    cout << "Product: " << showProductsObj.productsDict[productRows[y][x].substr(1, 2)] << endl;
                    sleep(2);
                    break;
                // up arrow
                case(72):
                    if (y - 1 >= 0)
                        y--;
                    break;
                // down arrow
                case(80):
                    if (y + 1 <= 5)
                        y++;
                    break;
                // left arrow
                case(75):
                    if (x - 1 >= 0)
                        x--;
                    break;
                // right arrow
                case(77):
                    if (x + 1 <= 4)
                        x++;
                    break;
                // backspace
                case(8):
                    cout << "Payment\n";
                    checkToPayment = 1;
                    sleep(2);
                    break;
                default:
                    break;
            }
            
            display();

        }
};


int main() 
{ 
    cout << "Program start" << endl;
    sleep(2);
    
    DisplayProgram displayProgram;
    displayProgram.display();
    return 0; 
}