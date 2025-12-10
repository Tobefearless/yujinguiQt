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

float extractFloatFromBeWordSwapped(const QByteArray &data, int offset) {
    if (offset + 4 > data.size()) {
        qWarning() << "偏移量超出数据范围:" << offset;
        return std::numeric_limits<float>::quiet_NaN();
    }

    const unsigned char *b = reinterpret_cast<const unsigned char*>(data.constData() + offset);

    // 大端序-字节交换转换：B0 B1 B2 B3 -> B1 B0 B3 B2
    quint32 wordSwappedInt = (quint32(b[1]) << 24)
                             | (quint32(b[0]) << 16)
                             | (quint32(b[3]) << 8)
                             | quint32(b[2]);

    float result;
    std::memcpy(&result, &wordSwappedInt, sizeof(result));
    return result;
}

// 主解析函数：将十六进制字符串转换为ProcessVariables结构体
ProcessVariables parseProcessVariables(const QString &hexString) {
    ProcessVariables vars{0,0,0,0,0,0};

    // 清理字符串（移除空格、换行等）
    QString cleanHex = hexString.simplified().remove(' ');

    // 验证长度：6个float × 4字节 × 2字符 = 48字符
    if (cleanHex.length() != 48) {
        qWarning() << "无效的十六进制字符串长度:" << cleanHex.length() << "应为48";
        return vars;
    }

    // 转换为字节数组
    QByteArray byteData = QByteArray::fromHex(cleanHex.toUtf8());
    if (byteData.size() != 24) {
        qWarning() << "十六进制解码失败，期望24字节，实际:" << byteData.size();
        return vars;
    }

    // 按顺序解析每个变量
    vars.pumpOutletPressure        = extractFloatFromBeWordSwapped(byteData, 0);
    vars.hydrofluoricAcidTankLevel = extractFloatFromBeWordSwapped(byteData, 4);
    vars.reactor1Temperature       = extractFloatFromBeWordSwapped(byteData, 8);
    vars.reactor2Temperature       = extractFloatFromBeWordSwapped(byteData, 12);
    vars.reactor3Temperature       = extractFloatFromBeWordSwapped(byteData, 16);
    vars.reactor4Temperature       = extractFloatFromBeWordSwapped(byteData, 20);

    return vars;
}
