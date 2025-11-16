#pragma execution_character_set("utf-8")

#include "rulerbar.h"
#include "qpainter.h"
#include "qtimer.h"
#include "qdebug.h"
#include <cmath> // 添加cmath头文件用于fabs和fmod

RulerBar::RulerBar(QWidget *parent) : QWidget(parent)
{
    minValue = 0.0;
    maxValue = 5.0;  // 默认范围改为0~5
    value = 0.0;

    precision = 1;   // 默认精度改为1位小数
    longStep = 1.0;  // 长步进改为1.0
    shortStep = 0.5; // 短步进改为0.5
    space = 8;

    animation = true;
    animationStep = 0.5; // 动画步长减小

    bgColorStart = QColor(100, 100, 100);
    bgColorEnd = QColor(60, 60, 60);
    lineColor = QColor(0, 0, 0);

    barBgColor = QColor(250, 250, 250);
    barColor = QColor(100, 184, 255);

    reverse = false;
    currentValue = 0.0;
    timer = new QTimer(this);
    timer->setInterval(15);
    connect(timer, SIGNAL(timeout()), this, SLOT(updateValue()));

    QFont font;
    font.setFamily("Arial");
    font.setPixelSize(12);
    setFont(font);

    setMinimumSize(60, 200); // 设置最小尺寸


}

RulerBar::~RulerBar()
{
    if (timer->isActive()) {
        timer->stop();
    }
}

void RulerBar::paintEvent(QPaintEvent *)
{
    // 绘制准备工作,启用反锯齿
    QPainter painter(this);
    painter.setRenderHints(QPainter::Antialiasing | QPainter::TextAntialiasing);

    // 绘制背景
//    drawBg(&painter);

    // 绘制柱状背景
    drawBarBg(&painter);
    // 绘制柱状
    drawBar(&painter);
    // 绘制标尺
    drawRuler(&painter);

    //启用悬浮调试
    setToolTip(tr("当前值:%1").arg(value));
    setMouseTracking(true);
}

void RulerBar::drawBg(QPainter *painter)
{
    painter->save();
   painter->setPen(Qt::NoPen);
   QLinearGradient bgGradient(QPointF(0, 0), QPointF(0, height()));
   bgGradient.setColorAt(0.0, bgColorStart);
   bgGradient.setColorAt(1.0, bgColorEnd);
   painter->setBrush(bgGradient);
   painter->drawRect(rect());
   painter->restore();
}

void RulerBar::drawRuler(QPainter *painter)
{
    painter->save();
    painter->setPen(lineColor);

    // 在量柱内部右侧绘制标尺线
    double initX = barRect.right() - 5; // 距离量柱右侧5像素
    double initY = barRect.top();
    double bottomY = barRect.bottom() - 5;

    // 绘制纵向标尺线
    painter->drawLine(QPointF(initX, initY), QPointF(initX, bottomY));

    // 计算刻度间距
    double length = barRect.height() -10;
    double increment = length / (maxValue - minValue);

    // 刻度线长度（向左延伸）
    int longLineLen = 15;
    int shortLineLen = 8;

    const double tolerance = 1e-6; // 浮点比较容差

    // 计算需要绘制的刻度数量
    int stepCount = static_cast<int>((maxValue - minValue) / shortStep) + 1;

    for (int i = 0; i <= stepCount; i++) {
        double current = minValue + i * shortStep; // 从最小值开始递增

        // 确保当前值在范围内
        if (current > maxValue + tolerance) continue;

        // 计算当前刻度对应的y坐标（从下到上递增）
        double currentY = bottomY - (current - minValue) * increment;

        // 判断是否为长刻度
        bool isLongStep = fabs(fmod(current, longStep)) < tolerance;
        if (fabs(current - minValue) < tolerance || fabs(current - maxValue) < tolerance) {
            isLongStep = true;
        }

        if (isLongStep) {
            // 绘制长刻度线（向左延伸）
            painter->drawLine(QPointF(initX, currentY), QPointF(initX - longLineLen, currentY));

            // 格式化数值显示
            QString text = QString::number(current, 'f', (fabs(current - round(current)) < tolerance) ? 0 : precision);

            // 绘制刻度值（在刻度线左侧，柱状内部）
            QRect textRect(initX - longLineLen - 32, currentY - 10, 30, 20);
            painter->drawText(textRect, Qt::AlignRight | Qt::AlignVCenter, text);
        } else {
            // 绘制短刻度线（向左延伸）
            painter->drawLine(QPointF(initX, currentY), QPointF(initX - shortLineLen, currentY));
        }
    }

    painter->restore();
}

// ... 保留原有代码直到 setShortStep 函数 ...

void RulerBar::setShortStep(double shortStep)
{
    // 确保步长不小于0.1
    double validStep = qMax(0.1, qAbs(shortStep));

    if (fabs(this->shortStep - validStep) > 1e-6) {
        this->shortStep = validStep;
        this->update();
    }
}

void RulerBar::drawBarBg(QPainter *painter)
{
    painter->save();
    painter->setPen(Qt::NoPen);
    painter->setBrush(barBgColor);

    // 柱状图位置（居中显示）
    //    double barWidth = width() * 0.6; // 柱状图宽度为控件宽度的60%
    //    double barLeft = (width() - barWidth) / 2;

        double barWidth = width() * 0.9; // 柱状图宽度为控件宽度的60%
        double barLeft = 0;
    barRect = QRectF(barLeft, space, barWidth, height() - 2 * space);

    // 绘制圆角矩形背景
    painter->drawRoundedRect(barRect, 5, 5);
    painter->restore();
}

void RulerBar::drawBar(QPainter *painter)
{
    painter->save();
    painter->setPen(Qt::NoPen);
    painter->setBrush(barColor);

    double barHeight = barRect.height();
    double increment = barHeight / (maxValue - minValue);
    double barTop = barRect.bottom() - (currentValue - minValue) * increment -5 ;

    // 绘制柱状（圆角矩形）
    QRectF bar(barRect.left(), barTop, barRect.width(), barRect.bottom() - barTop);
    painter->drawRoundedRect(bar, 5, 5);

    painter->restore();
}

double RulerBar::getMinValue() const
{
    return this->minValue;
}

double RulerBar::getMaxValue() const
{
    return this->maxValue;
}

double RulerBar::getValue() const
{
    return this->value;
}

int RulerBar::getPrecision() const
{
    return this->precision;
}

double RulerBar::getLongStep() const  // 改为double
{
    return this->longStep;
}

double RulerBar::getShortStep() const  // 改为double
{
    return this->shortStep;
}

int RulerBar::getSpace() const
{
    return this->space;
}

bool RulerBar::getAnimation() const
{
    return this->animation;
}

double RulerBar::getAnimationStep() const
{
    return this->animationStep;
}

QColor RulerBar::getBgColorStart() const
{
    return this->bgColorStart;
}

QColor RulerBar::getBgColorEnd() const
{
    return this->bgColorEnd;
}

QColor RulerBar::getLineColor() const
{
    return this->lineColor;
}

QColor RulerBar::getBarBgColor() const
{
    return this->barBgColor;
}

QColor RulerBar::getBarColor() const
{
    return this->barColor;
}

QSize RulerBar::sizeHint() const
{
    return QSize(100, 350);
}

QSize RulerBar::minimumSizeHint() const
{
    return QSize(20, 50);
}

void RulerBar::setRange(double minValue, double maxValue)
{
    // 如果最小值大于或者等于最大值则不设置
    if (minValue >= maxValue) {
        return;
    }

    this->minValue = minValue;
    this->maxValue = maxValue;

    // 如果目标值不在范围值内,则重新设置目标值
    // 值小于最小值则取最小值,大于最大值则取最大值
    if (value < minValue) {
        setValue(minValue);
    } else if (value > maxValue) {
        setValue(maxValue);
    }

    this->update();
}

void RulerBar::setRange(int minValue, int maxValue)
{
    setRange((double)minValue, (double)maxValue);
}

void RulerBar::setMinValue(double minValue)
{
    setRange(minValue, maxValue);
}

void RulerBar::setMaxValue(double maxValue)
{
    setRange(minValue, maxValue);
}

void RulerBar::setValue(double value)
{
    // 值和当前值一致则无需处理
    if (value == this->value) {
        return;
    }

    // 值小于最小值则取最小值,大于最大值则取最大值
    if (value < minValue) {
        value = minValue;
    } else if (value > maxValue) {
        value = maxValue;
    }

    if (value > this->value) {
        reverse = false;
    } else if (value < this->value) {
        reverse = true;
    }

    this->value = value;
    emit valueChanged(value);

    if (!animation) {
        currentValue = this->value;
        this->update();
    } else {
        timer->start();
    }
}

void RulerBar::setValue(int value)
{
    setValue((double)value);
}

void RulerBar::setPrecision(int precision)
{
    // 最大精确度为 3
    if (precision <= 3 && this->precision != precision) {
        this->precision = precision;
        this->update();
    }
}

void RulerBar::setLongStep(double longStep)  // 参数改为double
{
    if (fabs(this->longStep - longStep) > 1e-6) {
        this->longStep = longStep;
        this->update();
    }
}

void RulerBar::setSpace(int space)
{
    if (this->space != space) {
        this->space = space;
        this->update();
    }
}

void RulerBar::setAnimation(bool animation)
{
    if (this->animation != animation) {
        this->animation = animation;
        this->update();
    }
}

void RulerBar::setAnimationStep(double animationStep)
{
    if (fabs(this->animationStep - animationStep) > 1e-6) {
        this->animationStep = animationStep;
        this->update();
    }
}

void RulerBar::setBgColorStart(const QColor &bgColorStart)
{
    if (this->bgColorStart != bgColorStart) {
        this->bgColorStart = bgColorStart;
        this->update();
    }
}

void RulerBar::setBgColorEnd(const QColor &bgColorEnd)
{
    if (this->bgColorEnd != bgColorEnd) {
        this->bgColorEnd = bgColorEnd;
        this->update();
    }
}

void RulerBar::setLineColor(const QColor &lineColor)
{
    if (this->lineColor != lineColor) {
        this->lineColor = lineColor;
        this->update();
    }
}

void RulerBar::setBarBgColor(const QColor &barBgColor)
{
    if (this->barBgColor != barBgColor) {
        this->barBgColor = barBgColor;
        this->update();
    }
}

void RulerBar::setBarColor(const QColor &barColor)
{
    if (this->barColor != barColor) {
        this->barColor = barColor;
        this->update();
    }
}

void RulerBar::updateValue()
{
    if (!reverse) {
        if (currentValue >= value) {
            currentValue = value;
            timer->stop();
        } else {
            currentValue += animationStep;
        }
    } else {
        if (currentValue <= value) {
            currentValue = value;
            timer->stop();
        } else {
            currentValue -= animationStep;
        }
    }

    this->update();
}
