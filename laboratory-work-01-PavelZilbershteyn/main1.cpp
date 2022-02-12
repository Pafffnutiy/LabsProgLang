// TODO: зан€тьс€ тестированием и написанием main

#include "BigNumber.h"
#include <iostream>
#include <cassert>
#include <sstream>

int main()
{
    { //Test1. ѕроверка работоспособности всех конструкторов и перегрузки помещени€ в поток и из потока
        std::stringstream streamout, streamin;

        BigNumber chislo("-9876543212344566789");

        streamout << BigNumber("-00123") << ' ' << BigNumber(123456789987654321) << ' ' << BigNumber(chislo);

        std::string strokaout, strokain("123456789 -998877665544332211 0");
        std::getline(streamout, strokaout);

        streamin << strokain;

        BigNumber chislo1, chislo2, chislo3;

        streamin >> chislo1 >> chislo2 >> chislo3;

        bool correct1 = (strokaout == "-123 123456789987654321 -9876543212344566789")
                     && (chislo1 == BigNumber(123456789))
                     && (chislo2 == BigNumber("-998877665544332211"))
                     && (chislo3 == BigNumber(0));

        assert(correct1);    
    }
    
    { //Test2. ѕроверка работоспособности метода получени€ модул€ числа и перегрузки логики

        BigNumber one("-123456765456754"), two("0012321");

        bool correct2 = ( one.absol() == BigNumber("123456765456754") ) && ( two != one ) && ( one<two ) && 
                        ( one.absol() >  two )                          && ( one <= two ) && ( !(one >= two) );

        assert(correct2);    
    }

  { //Test3. ѕроверка работоспособности арифметики

        BigNumber one(1), two("-999999999999999999999999"), three("1234567");

        bool correct3p1 = ( two - one == BigNumber("-1000000000000000000000000") ) && 
                          ( two.absol()+one == BigNumber("1000000000000000000000000") ) &&
                          ( three * (two - one) / (two.absol() + one) == BigNumber(-1234567) ) &&
                          ( (three+one) % three == BigNumber("1") );

        bool correct3p2 = ( ++two == BigNumber(("-999999999999999999999998")) ) 
                       && ( three++ == BigNumber(1234567) && three == BigNumber(1234568) ) 
                       && ( --one == BigNumber(0) ) 
                       && ( one-- == BigNumber(0) && (one == BigNumber(-1)) );

        BigNumber a, b("1111111111"), c("-2222222222"), d("3333333333"), e("-4444444444"), f("5555555555"), g, i(e);

        a =  "-1010101010";
        b += c;
        c -= e;
        d /= b;
        e *= a;
        f %= i;
        g =  b;

        bool correct3p3 =  (a == BigNumber("-1010101010"))
                        && (b == BigNumber("-1111111111"))
                        && (c == BigNumber("2222222222"))
                        && (d == BigNumber(-3))
                        && (e == BigNumber("4489337821773288440"))
                        && (f == BigNumber("1111111111"))
                        && (g == BigNumber("-1111111111"));

        one = "-123456789";
        two = "11";
        BigNumber zero(0);

        bool correct3p4 = (one.power(two) == BigNumber("-101546450822483163119275021008420881536316593536032018296854662965892684042512235805234189"))
                       && (two.power(one) == BigNumber(0))
                       && (two.power(zero) == BigNumber(1));

        two = "-11111111111";
        
        bool correct3p5 = (-one == BigNumber(123456789))
                       && (-(one*two) == BigNumber("-1371742099986282579"));

        bool correct3 = correct3p1 && correct3p2 && correct3p3 && correct3p4 && correct3p5;

        assert(correct3);
  }

  { //Test4. ѕроверка работоспособности приведени€ к базовому типу и проверки числа на четность

      BigNumber chislo1("-1234567899876543210"), chislo2("998877665544332211");

      std::string NewChislo = static_cast<std::string>(chislo1) + static_cast<std::string>(chislo2);

      BigNumber res(NewChislo);

      bool correct4 = (res == BigNumber("-1234567899876543210998877665544332211"))
                   && (res.isEven() == false)
                   && (chislo1.isEven() == true);

      assert(correct4);
  }

  { //Test5. ѕроверка работоспособности сеттеров и геттеров
      
      BigNumber chislo1("111222333444555666777888999"),
                chislo2("-123456789012345678901234567890"),
                chislo3("-102030405060708090908070605040302010"),
                chislo4("100000000000000000000000000000000000000000000000000000000000000000000000000000000000000");

      chislo3.SetNumber("9999999999999999998888888888888888888888888777777777777777773333333333333312");
      chislo4.SetSign('-');

      bool correct5 = (chislo1.GetSign() == '+')
                   && (chislo2.GetNumber() == "123456789012345678901234567890")
                   && (chislo3 == BigNumber("-9999999999999999998888888888888888888888888777777777777777773333333333333312"))
                   && (chislo4 == BigNumber("-100000000000000000000000000000000000000000000000000000000000000000000000000000000000000"));
      
      assert(correct5);
  }

    return 0;
}
