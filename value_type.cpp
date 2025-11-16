#include "value_type.h"
#include <QtEndian>
#include <QDebug>
#include <cstring>
uint32_t bigEndianToLittleEndian_qt(uint32_t value)
{
    return qFromBigEndian(value);
}

float intToFloat(uint32_t value){
   uint32_t temp = bigEndianToLittleEndian_qt(value);
   float f;
   std::memcpy(&f, &temp, sizeof(f));
   return f;
}

QByteArray HexStringToByteArray(QString hex, bool *ok)
{
    int p;

       QByteArray ret;
       QStringList lst = hex.simplified().split(' ');//转化为字符串数组
       ret.resize(lst.count());
       for(int i = 0; i < lst.count(); i++)
       {
           p = lst[i].toInt(ok, 16);
           if(!(*ok) || p > 255 )
           {
               return 0;
           }
           ret[i] = p;
       }
       return ret;
}

QString ByteArrayToHexString(QString data)
{
    QString ret = data.toUpper();//data.toHex().toUpper());
    int len = ret.length()/2;
    //qDebug()<<data<<len;
    for(int i=1;i<len;i++)
    {
        //qDebug()<<i;
        ret.insert(2*i+i-1," ");
    }

        return ret;
}
// 重载：接受 32-bit 原始整数（0x3909064A 这种）
float bigEndianToFloat(quint32 raw)
{
    quint32 le  = qFromBigEndian(raw); // 翻转成 0x24DB304A
    float f;
    memcpy(&f, &le, sizeof(f));        // 按 float 解释

    return f;
}
